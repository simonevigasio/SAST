MULTIPROCESS_TEST_MAIN ( CrashingChildProcess ) {
 WaitToDie ( ProcessUtilTest : : GetSignalFilePath ( kSignalFileCrash ) . c_str ( ) ) ;
 # if defined ( OS_POSIX ) : : signal ( SIGSEGV , SIG_DFL ) ;
 # endif volatile int * oops = NULL ;
 * oops = 0xDEAD ;
 return 1 ;
 }