#ifdef SPLATFORM_X86

//32-bit definitions
#if defined (INT16_MIN) && defined (INT16_MAX)
#    define SINT_16_MAX INT16_MAX
#    define SINT_16_MIN INT16_MIN
typedef std::int16_t INT16;
typedef std::uint16_t UINT16;
#else
#    define SINT_16_MIN INT32_MIN
#    define SINT_16_MAX INT32_MAX
typedef std::int32_t INT16;
typedef std::uint32_t UINT16;
#endif

typedef std::uint32_t UINT32;
typedef std::uint64_t UINT64;
typedef std::int32_t  INT32;
typedef std::int64_t  INT64;
typedef float         SFLOAT;
typedef float         SDOUBLE;

#endif
