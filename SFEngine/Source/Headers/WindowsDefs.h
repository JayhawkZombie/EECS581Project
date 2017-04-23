#ifdef SPLATFORM_WINDOWS

#ifndef  __SPLATFORM_WINDOWS_H
#define  __SPLATFORM_WINDOWS_H

#    if defined ( _M_x64 ) || defined ( _M_ARM64 ) || defined ( _WIN64 )
#         define SARCH_X64
#    elif defined ( _X_Ix86 ) || defined ( _WIN32 )
#         define SARCH_X86
#    endif

#    include <windows.h>
#      if REG_DWORD == REG_DWORD_LITTLE_ENDIAN
#           define SARCH_LITTLE_ENDIAN
#           define LE_TO_HOST_ULONG(ULONGVAL) ULONGVAL
#           define BE_TO_HOST_ULONG(ULONGVAL) _byteswap_ulong(ULONGVAL)
#           define LE_TO_HOST_USHORT(USHORTVAL) USHORTVAL
#           define BE_TO_HOST_USHORT(USHORTVAL) _byteswap_ushort(USHORTVAL)
#           define LE_TO_HOST_UINT64(UINT64VAL) UINT64VAL
#           define BE_TO_HOST_UINT64(UINT64VAL) _byteswap_uint64(UINT64VAL)
#      elif REG_DWORD = REG_DWORD_BIG_ENDIAN
#           define SARCH_BIG_ENDIAN
#           define LE_TO_HOST_ULONG(ULONGVAL) _byteswap_ulong(ULONGVAL)
#           define BE_TO_HOST_ULONG(ULONGVAL) ULONGVAL
#           define LE_TO_HOST_USHORT(USHORTVAL) _byteswap_ushort(USHORTVAL)
#           define BE_TO_HOST_USHORT(USHORTVAL) USHORTVAL
#           define LE_TO_HOST_UINT64(UINT64VAL) _byteswap_uint64(UINT64VAL)
#           define BE_TO_HOST_UINT64(UINT64VAL) UINT64VAL
#      endif

#      if defined( _M_X64 ) || defined ( _M_ARM64 ) || defined ( _WIN64 )
#           define SPLATFORM_X64
#      elif defined ( _M_IX86 ) || defined ( _WIN32 )
#           define SPLATFORM_X86
#endif


#endif // __SPLATFORM_WINDOWS_H
#endif //SPLATFORM_WINDOWS
