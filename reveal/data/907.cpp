void init_logging ( const char * name , u_int32 def_syslogmask , int is_daemon ) {
 static int was_daemon ;
 char * cp ;
 const char * pname ;
 if ( INIT_NTP_SYSLOGMASK == ntp_syslogmask && != def_syslogmask ) ntp_syslogmask = def_syslogmask ;
 cp = strrchr ( name , DIR_SEP ) ;
 if ( NULL == cp ) pname = name ;
 else pname = 1 + cp ;
 progname = estrdup ( pname ) ;
 # ifdef SYS_WINNT cp = strrchr ( progname , '.' ) ;
 if ( NULL != cp && ! strcasecmp ( cp , ".exe" ) ) * cp = '\0' ;
 # endif # if ! defined ( VMS ) if ( is_daemon ) was_daemon = TRUE ;
 # ifndef LOG_DAEMON openlog ( progname , LOG_PID ) ;
 # else # ifndef LOG_NTP # define LOG_NTP LOG_DAEMON # endif openlog ( progname , LOG_PID | LOG_NDELAY , ( was_daemon ) ? LOG_NTP : 0 ) ;
 # ifdef DEBUG if ( debug ) setlogmask ( LOG_UPTO ( LOG_DEBUG ) ) ;
 else # endif setlogmask ( LOG_UPTO ( LOG_DEBUG ) ) ;
 # endif # endif }