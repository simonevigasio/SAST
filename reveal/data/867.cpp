static int dissect_h245_MasterSlaveDeterminationAck ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {
 offset = dissect_per_sequence ( tvb , offset , actx , tree , hf_index , ett_h245_MasterSlaveDeterminationAck , MasterSlaveDeterminationAck_sequence ) ;
 # line 530 "../../asn1/h245/h245.cnf" if ( h245_pi != NULL ) h245_pi -> msg_type = H245_MastSlvDetAck ;
 return offset ;
 }