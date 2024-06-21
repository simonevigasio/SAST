static void save_caller_context ( char * * argv ) {
 struct passwd * pw = NULL ;
 # ifndef USE_PAM # ifdef SU_ACCESS const char * password = NULL ;
 # endif # endif Prog = Basename ( argv [ 0 ] ) ;
 caller_uid = getuid ( ) ;
 caller_is_root = ( caller_uid == 0 ) ;
 caller_tty = ttyname ( 0 ) ;
 if ( ( isatty ( 0 ) != 0 ) && ( NULL != caller_tty ) ) {
 # ifndef USE_PAM caller_on_console = console ( caller_tty ) ;
 # endif }
 else {
 if ( ! caller_is_root ) {
 fprintf ( stderr , _ ( "%s: must be run from a terminal\n" ) , Prog ) ;
 exit ( 1 ) ;
 }
 caller_tty = "???" ;
 }
 pw = get_my_pwent ( ) ;
 if ( NULL == pw ) {
 fprintf ( stderr , _ ( "%s: Cannot determine your user name.\n" ) , Prog ) ;
 SYSLOG ( ( LOG_WARN , "Cannot determine the user name of the caller (UID %lu)" , ( unsigned long ) caller_uid ) ) ;
 su_failure ( caller_tty , true ) ;
 }
 STRFCPY ( caller_name , pw -> pw_name ) ;
 # ifndef USE_PAM # ifdef SU_ACCESS password = pw -> pw_passwd ;
 if ( strcmp ( pw -> pw_passwd , SHADOW_PASSWD_STRING ) == 0 ) {
 const struct spwd * spwd = getspnam ( caller_name ) ;
 if ( NULL != spwd ) {
 password = spwd -> sp_pwdp ;
 }
 }
 free ( caller_pass ) ;
 caller_pass = xstrdup ( password ) ;
 # endif # endif pw_free ( pw ) ;
 }