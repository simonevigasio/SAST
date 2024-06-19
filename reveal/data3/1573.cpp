static int tcg_cpu_exec ( CPUArchState * env ) {
 int ret ;
 # ifdef CONFIG_PROFILER int64_t ti ;
 # endif # ifdef CONFIG_PROFILER ti = profile_getclock ( ) ;
 # endif if ( use_icount ) {
 int64_t count ;
 int decr ;
 qemu_icount -= ( env -> icount_decr . u16 . low + env -> icount_extra ) ;
 env -> icount_decr . u16 . low = 0 ;
 env -> icount_extra = 0 ;
 count = qemu_icount_round ( qemu_clock_deadline ( vm_clock ) ) ;
 qemu_icount += count ;
 decr = ( count > 0xffff ) ? 0xffff : count ;
 count -= decr ;
 env -> icount_decr . u16 . low = decr ;
 env -> icount_extra = count ;
 }
 ret = cpu_exec ( env ) ;
 # ifdef CONFIG_PROFILER qemu_time += profile_getclock ( ) - ti ;
 # endif if ( use_icount ) {
 qemu_icount -= ( env -> icount_decr . u16 . low + env -> icount_extra ) ;
 env -> icount_decr . u32 = 0 ;
 env -> icount_extra = 0 ;
 }
 return ret ;
 }