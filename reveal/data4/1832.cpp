inline const OldUChar * toOldUCharPtr ( const char16_t * p ) {
 # ifdef U_ALIASING_BARRIER U_ALIASING_BARRIER ( p ) ;
 # endif return reinterpret_cast < const OldUChar * > ( p ) ;
 }