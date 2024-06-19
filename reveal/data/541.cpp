static int dissect_h245_GenericInformation ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {
 # line 656 "../../asn1/h245/h245.cnf" void * priv_data = actx -> private_data ;
 actx -> private_data = gef_ctx_alloc ( NULL , "GenericInformation" ) ;
 offset = dissect_h245_GenericMessage ( tvb , offset , actx , tree , hf_index ) ;
 # line 659 "../../asn1/h245/h245.cnf" actx -> private_data = priv_data ;
 return offset ;
 }