int vp9_get_raw_frame ( VP9Decoder * pbi , YV12_BUFFER_CONFIG * sd , vp9_ppflags_t * flags ) {
 VP9_COMMON * const cm = & pbi -> common ;
 int ret = - 1 ;
 # if ! CONFIG_VP9_POSTPROC ( void ) * flags ;
 # endif if ( pbi -> ready_for_new_data == 1 ) return ret ;
 if ( ! cm -> show_frame ) return ret ;
 pbi -> ready_for_new_data = 1 ;
 # if CONFIG_VP9_POSTPROC if ( ! cm -> show_existing_frame ) {
 ret = vp9_post_proc_frame ( cm , sd , flags ) ;
 }
 else {
 * sd = * cm -> frame_to_show ;
 ret = 0 ;
 }
 # else * sd = * cm -> frame_to_show ;
 ret = 0 ;
 # endif vp9_clear_system_state ( ) ;
 return ret ;
 }