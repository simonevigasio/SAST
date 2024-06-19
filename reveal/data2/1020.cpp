static int dissect_h245_EncryptionSync ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {
 # line 706 "../../asn1/h245/h245.cnf" void * priv_data = actx -> private_data ;
 actx -> private_data = gef_ctx_alloc ( NULL , "EncryptionSync" ) ;
 offset = dissect_per_sequence ( tvb , offset , actx , tree , hf_index , ett_h245_EncryptionSync , EncryptionSync_sequence ) ;
 # line 709 "../../asn1/h245/h245.cnf" actx -> private_data = priv_data ;
 return offset ;
 }