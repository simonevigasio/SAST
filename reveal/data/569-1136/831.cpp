static void useSndTimeout ( socket_handle_t sock ) {
 # ifdef _WIN32 const DWORD socket_timeout = SOCKET_RW_TIMEOUT_MS ;
 setsockopt ( sock , SOL_SOCKET , SO_SNDTIMEO , ( const char * ) & socket_timeout , sizeof ( socket_timeout ) ) ;
 # else const struct timeval socket_timeout = {
 . tv_sec = SOCKET_RW_TIMEOUT_MS / 1000 , . tv_usec = ( SOCKET_RW_TIMEOUT_MS % 1000 ) * 1000 }
 ;
 setsockopt ( sock , SOL_SOCKET , SO_SNDTIMEO , & socket_timeout , sizeof ( socket_timeout ) ) ;
 # endif }