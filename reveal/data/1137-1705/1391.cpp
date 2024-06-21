err_status_t srtp_protect ( srtp_ctx_t * ctx , void * rtp_hdr , int * pkt_octet_len ) {
 srtp_hdr_t * hdr = ( srtp_hdr_t * ) rtp_hdr ;
 uint32_t * enc_start ;
 uint32_t * auth_start ;
 unsigned int enc_octet_len = 0 ;
 xtd_seq_num_t est ;
 int delta ;
 uint8_t * auth_tag = NULL ;
 err_status_t status ;
 int tag_len ;
 srtp_stream_ctx_t * stream ;
 int prefix_len ;
 debug_print ( mod_srtp , "function srtp_protect" , NULL ) ;
 status = srtp_validate_rtp_header ( rtp_hdr , pkt_octet_len ) ;
 if ( status ) return status ;
 if ( * pkt_octet_len < octets_in_rtp_header ) return err_status_bad_param ;
 stream = srtp_get_stream ( ctx , hdr -> ssrc ) ;
 if ( stream == NULL ) {
 if ( ctx -> stream_template != NULL ) {
 srtp_stream_ctx_t * new_stream ;
 status = srtp_stream_clone ( ctx -> stream_template , hdr -> ssrc , & new_stream ) ;
 if ( status ) return status ;
 new_stream -> next = ctx -> stream_list ;
 ctx -> stream_list = new_stream ;
 new_stream -> direction = dir_srtp_sender ;
 stream = new_stream ;
 }
 else {
 return err_status_no_ctx ;
 }
 }
 if ( stream -> direction != dir_srtp_sender ) {
 if ( stream -> direction == dir_unknown ) {
 stream -> direction = dir_srtp_sender ;
 }
 else {
 srtp_handle_event ( ctx , stream , event_ssrc_collision ) ;
 }
 }
 if ( stream -> rtp_cipher -> algorithm == AES_128_GCM || stream -> rtp_cipher -> algorithm == AES_256_GCM ) {
 return srtp_protect_aead ( ctx , stream , rtp_hdr , ( unsigned int * ) pkt_octet_len ) ;
 }
 switch ( key_limit_update ( stream -> limit ) ) {
 case key_event_normal : break ;
 case key_event_soft_limit : srtp_handle_event ( ctx , stream , event_key_soft_limit ) ;
 break ;
 case key_event_hard_limit : srtp_handle_event ( ctx , stream , event_key_hard_limit ) ;
 return err_status_key_expired ;
 default : break ;
 }
 tag_len = auth_get_tag_length ( stream -> rtp_auth ) ;
 if ( stream -> rtp_services & sec_serv_conf ) {
 enc_start = ( uint32_t * ) hdr + uint32s_in_rtp_header + hdr -> cc ;
 if ( hdr -> x == 1 ) {
 srtp_hdr_xtnd_t * xtn_hdr = ( srtp_hdr_xtnd_t * ) enc_start ;
 enc_start += ( ntohs ( xtn_hdr -> length ) + 1 ) ;
 }
 if ( ! ( ( uint8_t * ) enc_start < ( uint8_t * ) hdr + * pkt_octet_len ) ) return err_status_parse_err ;
 enc_octet_len = ( unsigned int ) ( * pkt_octet_len - ( ( uint8_t * ) enc_start - ( uint8_t * ) hdr ) ) ;
 }
 else {
 enc_start = NULL ;
 }
 if ( stream -> rtp_services & sec_serv_auth ) {
 auth_start = ( uint32_t * ) hdr ;
 auth_tag = ( uint8_t * ) hdr + * pkt_octet_len ;
 }
 else {
 auth_start = NULL ;
 auth_tag = NULL ;
 }
 delta = rdbx_estimate_index ( & stream -> rtp_rdbx , & est , ntohs ( hdr -> seq ) ) ;
 status = rdbx_check ( & stream -> rtp_rdbx , delta ) ;
 if ( status ) {
 if ( status != err_status_replay_fail || ! stream -> allow_repeat_tx ) return status ;
 }
 else rdbx_add_index ( & stream -> rtp_rdbx , delta ) ;
 # ifdef NO_64BIT_MATH debug_print2 ( mod_srtp , "estimated packet index: %08x%08x" , high32 ( est ) , low32 ( est ) ) ;
 # else debug_print ( mod_srtp , "estimated packet index: %016llx" , est ) ;
 # endif if ( stream -> rtp_cipher -> type -> id == AES_ICM || stream -> rtp_cipher -> type -> id == AES_256_ICM ) {
 v128_t iv ;
 iv . v32 [ 0 ] = 0 ;
 iv . v32 [ 1 ] = hdr -> ssrc ;
 # ifdef NO_64BIT_MATH iv . v64 [ 1 ] = be64_to_cpu ( make64 ( ( high32 ( est ) << 16 ) | ( low32 ( est ) >> 16 ) , low32 ( est ) << 16 ) ) ;
 # else iv . v64 [ 1 ] = be64_to_cpu ( est << 16 ) ;
 # endif status = cipher_set_iv ( stream -> rtp_cipher , & iv , direction_encrypt ) ;
 }
 else {
 v128_t iv ;
 # ifdef NO_64BIT_MATH iv . v32 [ 0 ] = 0 ;
 iv . v32 [ 1 ] = 0 ;
 # else iv . v64 [ 0 ] = 0 ;
 # endif iv . v64 [ 1 ] = be64_to_cpu ( est ) ;
 status = cipher_set_iv ( stream -> rtp_cipher , & iv , direction_encrypt ) ;
 }
 if ( status ) return err_status_cipher_fail ;
 # ifdef NO_64BIT_MATH est = be64_to_cpu ( make64 ( ( high32 ( est ) << 16 ) | ( low32 ( est ) >> 16 ) , low32 ( est ) << 16 ) ) ;
 # else est = be64_to_cpu ( est << 16 ) ;
 # endif if ( auth_start ) {
 prefix_len = auth_get_prefix_length ( stream -> rtp_auth ) ;
 if ( prefix_len ) {
 status = cipher_output ( stream -> rtp_cipher , auth_tag , prefix_len ) ;
 if ( status ) return err_status_cipher_fail ;
 debug_print ( mod_srtp , "keystream prefix: %s" , octet_string_hex_string ( auth_tag , prefix_len ) ) ;
 }
 }
 if ( enc_start ) {
 status = cipher_encrypt ( stream -> rtp_cipher , ( uint8_t * ) enc_start , & enc_octet_len ) ;
 if ( status ) return err_status_cipher_fail ;
 }
 if ( auth_start ) {
 status = auth_start ( stream -> rtp_auth ) ;
 if ( status ) return status ;
 status = auth_update ( stream -> rtp_auth , ( uint8_t * ) auth_start , * pkt_octet_len ) ;
 if ( status ) return status ;
 debug_print ( mod_srtp , "estimated packet index: %016llx" , est ) ;
 status = auth_compute ( stream -> rtp_auth , ( uint8_t * ) & est , 4 , auth_tag ) ;
 debug_print ( mod_srtp , "srtp auth tag: %s" , octet_string_hex_string ( auth_tag , tag_len ) ) ;
 if ( status ) return err_status_auth_fail ;
 }
 if ( auth_tag ) {
 * pkt_octet_len += tag_len ;
 }
 return err_status_ok ;
 }