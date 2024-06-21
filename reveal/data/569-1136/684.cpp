static inline void * alloc_code_gen_buffer ( void ) {
 int flags = MAP_PRIVATE | MAP_ANONYMOUS ;
 uintptr_t start = 0 ;
 void * buf ;
 # if defined ( __PIE__ ) || defined ( __PIC__ ) # elif defined ( __x86_64__ ) && defined ( MAP_32BIT ) flags |= MAP_32BIT ;
 if ( tcg_ctx . code_gen_buffer_size > 800u * 1024 * 1024 ) {
 tcg_ctx . code_gen_buffer_size = 800u * 1024 * 1024 ;
 }
 # elif defined ( __sparc__ ) start = 0x40000000ul ;
 # elif defined ( __s390x__ ) start = 0x90000000ul ;
 # endif buf = mmap ( ( void * ) start , tcg_ctx . code_gen_buffer_size , PROT_WRITE | PROT_READ | PROT_EXEC , flags , - 1 , 0 ) ;
 return buf == MAP_FAILED ? NULL : buf ;
 }