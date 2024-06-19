static int dissect_h245_MultiplexEntryDescriptor ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {
 # line 53 "../../asn1/h245/h245.cnf" h223_me = NULL ;
 h223_mc = 0 ;
 offset = dissect_per_sequence ( tvb , offset , actx , tree , hf_index , ett_h245_MultiplexEntryDescriptor , MultiplexEntryDescriptor_sequence ) ;
 if ( h223_set_mc_handle ) ( * h223_set_mc_handle ) ( actx -> pinfo , h223_mc , h223_me ) ;
 return offset ;
 }