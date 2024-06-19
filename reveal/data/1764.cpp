static ulong start_timer ( void ) {
 # if defined ( __WIN__ ) return clock ( ) ;
 # else struct tms tms_tmp ;
 return times ( & tms_tmp ) ;
 # endif }