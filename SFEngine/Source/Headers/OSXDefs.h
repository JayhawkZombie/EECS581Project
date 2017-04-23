#ifdef SPLATFORM_OSX

#  ifndef __SPLATFORM_OSX_H
#  define __SPLATFORM_OSX_H

#  if defined ( __i386__ ) || defined ( __ppc__ )
#       define SARCH_X86
#  elif defined ( __x86_64__ ) || defined ( __ppc64__ )
#       define SARCH_X64
#  endif

#  ifdef __BIG_ENDIAN__
#       define SARCH_BIG_ENDIAN
#  elif __LITTLE_ENDIAN__
#       define SARCH_LITTLE_ENDIAN
#  endif

#  endif

#endif
