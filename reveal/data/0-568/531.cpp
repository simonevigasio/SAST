static __inline__ void __swab16s ( __u16 * p ) {
 # ifdef __arch_swab16s __arch_swab16s ( p ) ;
 # else * p = __swab16p ( p ) ;
 # endif }