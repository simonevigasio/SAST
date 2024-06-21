static bool gn_to_string ( identification_t * id , char * * uri ) {
 int len ;
 # ifdef USE_FUZZING chunk_t proper ;
 chunk_printable ( id -> get_encoding ( id ) , & proper , '?' ) ;
 len = asprintf ( uri , "%.*s" , ( int ) proper . len , proper . ptr ) ;
 chunk_free ( & proper ) ;
 # else len = asprintf ( uri , "%Y" , id ) ;
 # endif if ( ! len ) {
 free ( * uri ) ;
 return FALSE ;
 }
 return len > 0 ;
 }