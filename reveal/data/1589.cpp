void hb_font_funcs_destroy ( hb_font_funcs_t * ffuncs ) {
 if ( ! hb_object_destroy ( ffuncs ) ) return ;
 # define HB_FONT_FUNC_IMPLEMENT ( name ) if ( ffuncs -> destroy . name ) ffuncs -> destroy . name ( ffuncs -> user_data . name ) ;
 HB_FONT_FUNCS_IMPLEMENT_CALLBACKS # undef HB_FONT_FUNC_IMPLEMENT free ( ffuncs ) ;
 }