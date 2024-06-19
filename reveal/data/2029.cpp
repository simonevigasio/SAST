static int dissect_h245_NonStandardParameter ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {
 # line 979 "../../asn1/h245/h245.cnf" nsp_handle = NULL ;
 offset = dissect_per_sequence ( tvb , offset , actx , tree , hf_index , ett_h245_NonStandardParameter , NonStandardParameter_sequence ) ;
 return offset ;
 }