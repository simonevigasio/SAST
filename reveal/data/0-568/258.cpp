static void qemuMonitorJSONHandleIOError ( qemuMonitorPtr mon , virJSONValuePtr data ) {
 const char * device ;
 const char * action ;
 const char * reason ;
 int actionID ;
 if ( ( action = virJSONValueObjectGetString ( data , "action" ) ) == NULL ) {
 VIR_WARN ( "Missing action in disk io error event" ) ;
 action = "ignore" ;
 }
 if ( ( device = virJSONValueObjectGetString ( data , "device" ) ) == NULL ) {
 VIR_WARN ( "missing device in disk io error event" ) ;
 }
 # if 0 if ( ( reason = virJSONValueObjectGetString ( data , "reason" ) ) == NULL ) {
 VIR_WARN ( "missing reason in disk io error event" ) ;
 reason = "" ;
 }
 # else reason = "" ;
 # endif if ( ( actionID = qemuMonitorIOErrorActionTypeFromString ( action ) ) < 0 ) {
 VIR_WARN ( "unknown disk io error action '%s'" , action ) ;
 actionID = VIR_DOMAIN_EVENT_IO_ERROR_NONE ;
 }
 qemuMonitorEmitIOError ( mon , device , actionID , reason ) ;
 }