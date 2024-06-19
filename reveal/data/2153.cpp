int evbuffer_write ( struct evbuffer * buffer , int fd ) {
 int n ;
 # ifndef WIN32 n = write ( fd , buffer -> buffer , buffer -> off ) ;
 # else n = send ( fd , buffer -> buffer , buffer -> off , 0 ) ;
 # endif if ( n == - 1 ) return ( - 1 ) ;
 if ( n == 0 ) return ( 0 ) ;
 evbuffer_drain ( buffer , n ) ;
 return ( n ) ;
 }