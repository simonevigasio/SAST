static void sapi_uwsgi_log_message ( char * message TSRMLS_DC ) {
 # endif uwsgi_log ( "%s\n" , message ) ;
 }