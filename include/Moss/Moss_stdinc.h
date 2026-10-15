//                        MIT License
//
//                  Copyright (c) 2026 Toby
//
#ifndef MOSS_STDINC_H
#define MOSS_STDINC_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Determine platform
#if defined(MOSS_PLATFORM_BLUE)
	// Correct define already defined, this overrides everything else
	#define MOSS_PLATFORM_EMBEDDED
#elif defined(__EMSCRIPTEN__)
	#define MOSS_PLATFORM_WASM
#elif defined(_WIN32) || defined(_WIN64)
	#include <winapifamily.h>

	// Windows
	#define MOSS_PLATFORM_WINDOWS

	#if (WINAPI_FAMILY == WINAPI_FAMILY_APP)
        #define MOSS_PLATFORM_WINDOWS_UWP
    #endif

	/* Xbox (GDK covers Xbox One + Series) */
    #if defined(_GAMING_XBOX)
        #define MOSS_PLATFORM_GDK
        #if defined(_GAMING_XBOX_X)
            #define MOSS_PLATFORM_XBOXSERIES
			#define MOSS_PLATFORM_EMBEDDED
        #else
            #define MOSS_PLATFORM_XBOXONE
			#define MOSS_PLATFORM_EMBEDDED
        #endif
    #endif
#elif defined(__APPLE__)
    #include <TargetConditionals.h>
    #define MOSS_PLATFORM_APPLE

    #if TARGET_OS_OSX
        #define MOSS_PLATFORM_MACOS
    #elif TARGET_OS_IPHONE
        #define MOSS_PLATFORM_IOS
		#define MOSS_PLATFORM_EMBEDDED
    #elif TARGET_OS_TV
        #define MOSS_PLATFORM_TVOS
		#define MOSS_PLATFORM_EMBEDDED
    #elif TARGET_OS_VISION
        #define MOSS_PLATFORM_VISIONOS
    #endif
#elif defined(ANDROID) || defined(__ANDROID__) 	// Android is linux too, so that's why we check it first
	#define MOSS_PLATFORM_ANDROID
	#define MOSS_PLATFORM_EMBEDDED
	// Add Android TV
#elif defined(linux) || defined(__linux) || defined(__linux__)
	// Linux
    #define MOSS_PLATFORM_LINUX
#elif defined(__FreeBSD__)
    #define MOSS_PLATFORM_FREEBSD
#elif defined(__OpenBSD__)
    #define MOSS_PLATFORM_OPENBSD
#elif defined(__NetBSD__)
    #define MOSS_PLATFORM_NETBSD
#elif defined(__bsdi__)
    #define MOSS_PLATFORM_BSDI
#elif defined(__sun)
    #define MOSS_PLATFORM_SOLARIS
#elif defined(_AIX)
    #define MOSS_PLATFORM_AIX
#elif defined(__hpux)
    #define MOSS_PLATFORM_HPUX
#elif defined(__HAIKU__)
    #define MOSS_PLATFORM_HAIKU
#elif defined(__GNU__)
    #define MOSS_PLATFORM_HURD
#elif defined(__sgi)
    #define MOSS_PLATFORM_IRIX
#elif defined(__QNX__)
    #define MOSS_PLATFORM_QNXNTO
#elif defined(__riscos__)
    #define MOSS_PLATFORM_RISCOS
#elif defined(__osf__)
    #define MOSS_PLATFORM_OSF
#elif defined(__unix__) || defined(__unix)
    #define MOSS_PLATFORM_UNIX
#elif defined(__3DS__)
    #define MOSS_PLATFORM_3DS
#elif defined(__NGAGE__)
    #define MOSS_PLATFORM_NGAGE
#elif defined(__psp__)
    #define MOSS_PLATFORM_PSP
#elif defined(__vita__)
    #define MOSS_PLATFORM_VITA
#elif defined(__ps2__)
    #define MOSS_PLATFORM_PS2
#elif defined(__CYGWIN__)
    #define MOSS_PLATFORM_CYGWIN
#elif defined(__OS2__)
    #define MOSS_PLATFORM_OS2
#elif defined(__EMSCRIPTEN__)
	#define MOSS_PLATFORM_WASM
#endif

// Platform helper macros
#ifdef MOSS_PLATFORM_ANDROID
	#define MOSS_IF_NOT_ANDROID(x)
#else
	#define MOSS_IF_NOT_ANDROID(x) x
#endif

// Determine compiler
#if defined(__clang__)
	#define MOSS_COMPILER_CLANG
#elif defined(__GNUC__)
	#define MOSS_COMPILER_GCC
#elif defined(_MSC_VER)
	#define MOSS_COMPILER_MSVC 1943
#endif

#if (defined(__MINGW64__) || defined(__MINGW32__))
	#define MOSS_COMPILER_MINGW
#endif


// Detect CPU architecture
#if defined(__x86_64__) || defined(_M_X64) || defined(__i386__) || defined(_M_IX86)
	#include <immintrin.h> // Pulls in SSE, AVX, AVX2, TZCNT, LZCNT
	// X86 CPU architecture
	#define MOSS_CPU_X86
	#if defined(__x86_64__) || defined(_M_X64)
		#define MOSS_CPU_ADDRESS_BITS 64
	#else
		#define MOSS_CPU_ADDRESS_BITS 32
	#endif
	#define MOSS_SIMD_SSE
	#define MOSS_VECTOR_ALIGNMENT 16
	#define MOSS_DVECTOR_ALIGNMENT 32

	#if defined(__AVX512F__) && defined(__AVX512VL__) && defined(__AVX512DQ__) && !defined(MOSS_SIMD_AVX512)
		#define MOSS_SIMD_AVX512
		#undef MOSS_DVECTOR_ALIGNMENT
		#define MOSS_DVECTOR_ALIGNMENT 64 // Optimize double-precision vectors for AVX-512 ZMM registers
	#endif
	#if (defined(__AVX2__) || defined(MOSS_SIMD_AVX512)) && !defined(MOSS_SIMD_AVX2)
		#define MOSS_SIMD_AVX2
	#endif
	#if (defined(__AVX__) || defined(MOSS_SIMD_AVX2)) && !defined(MOSS_SIMD_AVX)
		#define MOSS_SIMD_AVX
	#endif
	#if (defined(__SSE4_2__) || defined(MOSS_SIMD_AVX)) && !defined(MOSS_SIMD_SSE4_2)
		#define MOSS_SIMD_SSE4_2
	#endif
	#if (defined(__SSE4_1__) || defined(MOSS_SIMD_SSE4_2)) && !defined(MOSS_SIMD_SSE4_1)
		#define MOSS_SIMD_SSE4_1
	#endif
	#if (defined(__F16C__) || defined(MOSS_SIMD_AVX2)) && !defined(MOSS_SIMD_F16C)
		#define MOSS_SIMD_F16C
	#endif
	#if (defined(__LZCNT__) || defined(MOSS_SIMD_AVX2)) && !defined(MOSS_SIMD_LZCNT)
		#define MOSS_SIMD_LZCNT
	#endif
	#if (defined(__BMI__) || defined(MOSS_SIMD_AVX2)) && !defined(MOSS_SIMD_TZCNT)
		#define MOSS_SIMD_TZCNT
	#endif
	#ifndef MOSS_CROSS_PLATFORM_DETERMINISTIC
		#if defined(MOSS_COMPILER_CLANG) || defined(MOSS_COMPILER_GCC)
			#if defined(__FMA__) && !defined(MOSS_USE_FMADD)
				#define MOSS_USE_FMADD
			#endif
		#elif defined(MOSS_COMPILER_MSVC)
			#if defined(__AVX2__) && !defined(MOSS_USE_FMADD) // AVX2 also enables fused multiply add
				#define MOSS_USE_FMADD
			#endif
		#else
			#error Undefined compiler
		#endif
	#endif // MOSS_CROSS_PLATFORM_DETERMINISTIC
#elif (defined(__aarch64__) || defined(_M_ARM64) || defined(__arm__) || defined(_M_ARM))
	// ARM CPU architecture
	#define MOSS_CPU_ARM
	#if defined(__aarch64__) || defined(_M_ARM64)
		#define MOSS_CPU_ADDRESS_BITS 64
		#define MOSS_SIMD_NEON
		#define MOSS_VECTOR_ALIGNMENT 16
		#define MOSS_DVECTOR_ALIGNMENT 32
		#if defined(__ARM_FEATURE_FMA) && !defined(MOSS_CROSS_PLATFORM_DETERMINISTIC)
			#define MOSS_USE_FMADD
		#endif
		#if defined(__ARM_FEATURE_SVE)
			#define MOSS_SIMD_SVE
		#endif
	#else
		#define MOSS_CPU_ADDRESS_BITS 32
		#define MOSS_VECTOR_ALIGNMENT 8 // 32-bit ARM does not support aligning on the stack on 16 byte boundaries
		#define MOSS_DVECTOR_ALIGNMENT 8
		#if defined(__ARM_NEON)
			#include <arm_neon.h>
			#define MOSS_SIMD_NEON
		#else
			#include <immintrin.h>
		#endif
	#endif // __aarch64__ || _M_ARM64
#elif defined(__riscv)
	// RISC-V CPU architecture
	#define MOSS_CPU_RISCV
	#if __riscv_xlen == 64
		#define MOSS_CPU_ADDRESS_BITS 64
	#else
		#define MOSS_CPU_ADDRESS_BITS 32
	#endif

	// RISC-V Vector (RVV) Standard Detection
	#if defined(__riscv_vector) || defined(__riscv_v_intrinsic)
		#define MOSS_SIMD_RISCV_VECTOR
		#define MOSS_VECTOR_ALIGNMENT 32   // Align high for VLA structures
		#define MOSS_DVECTOR_ALIGNMENT 64
	#else
		#define MOSS_VECTOR_ALIGNMENT 16
		#define MOSS_DVECTOR_ALIGNMENT 32
	#endif

	// Fused Multiply-Add is built inherently into standard single/double float extensions (F/D)
	#if (defined(__riscv_flen) && __riscv_flen >= 32) && !defined(MOSS_CROSS_PLATFORM_DETERMINISTIC)
		#define MOSS_USE_FMADD
	#endif
#elif defined(__wasm_simd128__)
	#define MOSS_PLATFORM_WASM
	// WebAssembly CPU architecture
	#define MOSS_CPU_WASM
	#if defined(__wasm64__)
		#define MOSS_CPU_ADDRESS_BITS 64
	#else
		#define MOSS_CPU_ADDRESS_BITS 32
	#endif
	#define MOSS_VECTOR_ALIGNMENT 16
	#define MOSS_DVECTOR_ALIGNMENT 32
	#ifdef __wasm_simd128__
		#define MOSS_SIMD_SSE
		#define MOSS_SIMD_SSE4_1
		#define MOSS_SIMD_SSE4_2
		#define MOSS_SIMD_WASM128
	#endif
#elif (defined(__powerpc__) || defined(__powerpc64__) || defined(__ppc64__))
	// PowerPC CPU architecture
	#define MOSS_CPU_PPC
	#if defined(__powerpc64__)
		#define MOSS_CPU_ADDRESS_BITS 64
	#else
		#define MOSS_CPU_ADDRESS_BITS 32
	#endif
	#ifdef _BIG_ENDIAN
		#define MOSS_CPU_BIG_ENDIAN
	#endif

	// Map PowerPC Vector Engine tiers
	#if defined(__VSX__)
		#define MOSS_SIMD_VSX
		#define MOSS_SIMD_ALTIVEC
		#define MOSS_VECTOR_ALIGNMENT 16
		#define MOSS_DVECTOR_ALIGNMENT 32
		#ifndef MOSS_CROSS_PLATFORM_DETERMINISTIC
			#define MOSS_USE_FMADD // VSX introduces hardware float FMA
		#endif
	#elif defined(__ALTIVEC__)
		#define MOSS_SIMD_ALTIVEC
		#define MOSS_VECTOR_ALIGNMENT 16
		#define MOSS_DVECTOR_ALIGNMENT 16
	#endif
#elif defined(__loongarch__)
	// LoongArch CPU architecture
	#define MOSS_CPU_LOONGARCH
	#if defined(__loongarch64)
		#define MOSS_CPU_ADDRESS_BITS 64
	#else
		#define MOSS_CPU_ADDRESS_BITS 32
	#endif

	// Map Loongson Vector Extensions
	#if defined(__loongarch_asx)
		#define MOSS_SIMD_LASX
		#define MOSS_SIMD_LSX
		#define MOSS_VECTOR_ALIGNMENT 32 // 256-bit alignment for LASX
		#define MOSS_DVECTOR_ALIGNMENT 32
	#elif defined(__loongarch_sx)
		#define MOSS_SIMD_LSX
		#define MOSS_VECTOR_ALIGNMENT 16 // 128-bit alignment for LSX
		#define MOSS_DVECTOR_ALIGNMENT 16
	#endif
	#if (defined(__loongarch_sx) || defined(__loongarch_asx)) && !defined(MOSS_CROSS_PLATFORM_DETERMINISTIC)
		#define MOSS_USE_FMADD
	#endif

#elif defined(__e2k__)
	// E2K CPU architecture (MCST Elbrus 2000)
	#define MOSS_CPU_E2K
	#define MOSS_CPU_ADDRESS_BITS 64
	#define MOSS_VECTOR_ALIGNMENT 16
	#define MOSS_DVECTOR_ALIGNMENT 32

	// Compiler flags on e2k arch determine CPU features
	#if defined(__SSE__) && !defined(MOSS_SIMD_SSE)
		#define MOSS_SIMD_SSE
	#endif
#else
	#error Unsupported CPU architecture
#endif

#ifdef MOSS_SHARED_LIBRARY
#  define MOSS_EXPORT __attribute__((visibility("default")))
#else
#  define MOSS_EXPORT
#endif

#ifdef __cplusplus
#  define MOSS_API extern "C" MOSS_EXPORT
#else
#  define MOSS_API extern MOSS_EXPORT
#endif

#ifndef MOSS_CALL
#  if defined(_WIN32)
#    define MOSS_CALL __cdecl
#  else
#    define MOSS_CALL
#  endif
#endif

// Define inline macro
#if defined(MOSS_NO_FORCE_INLINE)
	#define MOSS_INLINE inline
#elif defined(MOSS_COMPILER_CLANG)
	#define MOSS_INLINE __inline__ __attribute__((always_inline))
#elif defined(MOSS_COMPILER_GCC)
	// On gcc 14 using always_inline in debug mode causes error: "inlining failed in call to 'always_inline' 'XXX': function not considered for inlining"
	#if __GNUC__ >= 14 && defined(MOSS_DEBUG)
		#define MOSS_INLINE inline
	#else
		#define MOSS_INLINE __inline__ __attribute__((always_inline))
	#endif
#elif defined(MOSS_COMPILER_MSVC)
	#define MOSS_INLINE __forceinline
#else
	#error Undefined
#endif

#define MOSS_NOINLINE     __attribute__((noinline))
#define MOSS_ALIGN(x)     __attribute__((aligned(x)))
#if defined(MOSS_COMPILER_GCC) || defined(MOSS_COMPILER_CLANG)
#define MOSS_LIKELY(x)    __builtin_expect((x), U1)
#define MOSS_UNLIKELY(x)  __builtin_expect((x), U0)
#else
#define MOSS_LIKELY(x) (x)
#define MOSS_UNLIKELY(x) (x)
#endif 


#ifdef MOSS_DEBUG
#include <stdio.h>
#include <stdarg.h>
#include <cstdint>

// Core logging function
static inline void Moss_Log(const char* prefix, const char* msg, const char* color, ...) {
    char formatBuffer[8192];
    snprintf(formatBuffer, sizeof(formatBuffer), "%s%s%s\x1b[0m\n", color, prefix, msg);

    va_list args;
    va_start(args, color);
    vprintf(formatBuffer, args);
    va_end(args);
}

#define MOSS_TRACE(msg, ...) Moss_Log("TRACE: ", msg, "\x1b[37m", ##__VA_ARGS__); // White
#define MOSS_INFO(msg, ...)  Moss_Log("INFO:  ", msg, "\x1b[32m", ##__VA_ARGS__); // Green
#define MOSS_WARN(msg, ...)  Moss_Log("WARN:  ", msg, "\x1b[33m", ##__VA_ARGS__); // Yellow
#define MOSS_ERROR(msg, ...) Moss_Log("ERROR: ", msg, "\x1b[31m", ##__VA_ARGS__); // Red
#define MOSS_FATAL(msg, ...) Moss_Log("FATAL: ", msg, "\x1b[35m", ##__VA_ARGS__); // Magenta

#if defined(_WIN32)
    #define DEBUG_BREAK() __debugbreak()
#elif defined(__linux__) || defined(__APPLE__)
    #define DEBUG_BREAK() __builtin_trap()
#else
    #error Unsupported OS
#endif
#else
	#define MOSS_TRACE(msg, ...)  		((void)0)
	#define MOSS_DEBUG(msg, ...)  		((void)0)
	#define MOSS_INFO(msg, ...)  		((void)0)
	#define MOSS_WARN(msg, ...)  		((void)0)
	#define MOSS_ERROR(msg, ...)  		((void)0)
	#define MOSS_FATAL(msg, ...)  		((void)0)
	#define MOSS_CHECK(x, msg, ...)  	((void)0)
	#define MOSS_ASSERT(...)  			((void)0)

	#define MOSS_IF_ENABLE_ASSERTS(...)
    #define DEBUG_BREAK() ((void)0)
#endif

#define MOSS_FALSE 0U
#define MOSS_TRUE 1U
#define MOSS_BIT(x) (1u << (x))
#define MOSS_ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#define MOSS_UNUSED(x) ((void)(x))

#ifndef PI
#  define PI 3.14159265358979323846f
#endif
#define HALF_PI 1.57079632679489661923f
#define TAU (PI * 2.0f)
#define DEG_TO_RAD(d) ((d) * (PI / 180.0f))
#define RAD_TO_DEG(r) ((r) * (180.0f / PI))
#define CLAMP(x, a, b) (((x) < (a)) ? (a) : (((x) > (b)) ? (b) : (x)))

#define MAX_INT8 INT8_MAX
#define MAX_INT16 INT16_MAX
#define MAX_INT32 INT32_MAX
#define MAX_INT64 INT64_MAX
#define MIN_INT8 INT8_MIN
#define MIN_INT16 INT16_MIN
#define MIN_INT32 INT32_MIN
#define MIN_INT64 INT64_MIN
#define MAX_UINT8 UINT8_MAX
#define MAX_UINT16 UINT16_MAX
#define MAX_UINT32 UINT32_MAX
#define MAX_UINT64 UINT64_MAX
#define MIN_UINT8 0u
#define MIN_UINT16 0u
#define MIN_UINT32 0u
#define MIN_UINT64 0ull

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;
typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef signed long long s64;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef float float32;
typedef double float64;
typedef float DeltaTime;
typedef float Moss_Time;
typedef float Moss_Timer;

typedef struct Vec2 { float x, y; } Vec2;
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Vec4 { float x, y, z, w; } Vec4;
typedef struct iVec2 { int x, y; } iVec2;
typedef struct iVec3 { int x, y, z; } iVec3;
typedef struct iVec4 { int x, y, z, w; } iVec4;
typedef struct dVec2 { double x, y; } dVec2;
typedef struct dVec3 { double x, y, z; } dVec3;
typedef struct dVec4 { double x, y, z, w; } dVec4;

typedef Vec2 Float2;
typedef Vec3 Float3;
typedef Vec4 Float4;
typedef iVec2 Int2;
typedef iVec3 Int3;
typedef iVec4 Int4;
typedef dVec2 Double2;
typedef dVec3 Double3;
typedef dVec4 Double4;

typedef struct Mat2 { float m[2][2]; } Mat2;
typedef struct Mat2x3 { float m[2][3]; } Mat2x3;
typedef struct Mat2x4 { float m[2][4]; } Mat2x4;
typedef struct Mat3 { float m[3][3]; } Mat3;
typedef struct Mat3x2 { float m[3][2]; } Mat3x2;
typedef struct Mat3x4 { float m[3][4]; } Mat3x4;
typedef struct Mat4 { float m[4][4]; } Mat4;
typedef struct Mat4x2 { float m[4][2]; } Mat4x2;
typedef struct Mat4x3 { float m[4][3]; } Mat4x3;
typedef Mat4 Mat44;

typedef struct Color { uint8 r, g, b, a; } Color;
typedef struct Rect { float x, y, width, height; } Rect;
typedef struct iRect { int x, y, width, height; } iRect;
typedef struct Quat { float x, y, z, w } Quat;
typedef struct Plane { Vec3 normal; float distance; } Plane;
typedef struct AABB2 { Vec2 min; Vec2 max; } AABB2;
typedef struct AABB3 { Vec3 min; Vec3 max; } AABB3;
typedef struct OBB2 { Mat44 orientation; Vec2 center; Vec2 half_extents; } OBB2;
typedef struct OBB3 { Mat44 orientation; Vec3 center; Vec3 half_extents; } OBB3;
typedef struct Basis { Vec3 x, y, z; } Basis;

typedef struct Moss_Json;
typedef struct Moss_PCK;
typedef struct Moss_Config;
typedef struct Moss_ObjectStream;

#ifdef MOSS_DOUBLE_PRECISION
typedef dVec2 RVec2;
typedef dVec3 RVec3;
typedef dVec4 RVec4;
#else
typedef Vec2 RVec2;
typedef Vec3 RVec3;
typedef Vec4 RVec4;
#endif

#ifdef MOSS_USE_OBB
typedef OBB2 AABox2;
typedef OBB3 AABox3;
#else
typedef AABB2 AABox2;
typedef AABB3 AABox3;
#endif

typedef struct Texture {
    unsigned int id;
    int width;
    int height;
    int mipmaps;
    int format;
} Texture;
typedef Texture Texture2D;
typedef Texture Texture3D;
typedef Texture TextureCubemap;

static inline float Moss_Min(float a, float b) { return a < b ? a : b; }
static inline float Moss_Max(float a, float b) { return a > b ? a : b; }
static inline float Moss_Abs(float v) { return v < 0.0f ? -v : v; }
static inline float Moss_Sqrt(float v) { return sqrtf(v); }
static inline float Moss_Ceil(float v) { return ceilf(v); }
static inline float Moss_Floor(float v) { return floorf(v); }
static inline float Moss_Trunc(float v) { return truncf(v); }
static inline float Moss_Round(float v) { return roundf(v); }
static inline float Moss_Fmod(float a, float b) { return fmodf(a, b); }
static inline bool Moss_IsFinite(float v) { return isfinite(v) != 0; }
static inline bool Moss_IsNaN(float v) { return isnan(v) != 0; }
static inline float Moss_Clamp(float v, float minv, float maxv) { return CLAMP(v, minv, maxv); }
static inline float Moss_Lerp(float a, float b, float t) { return a + t * (b - a); }
static inline void seed_random(void) { srand((unsigned int)time(NULL)); }
static inline float randf_range(float min, float max) { return min + (float)rand() / (float)RAND_MAX * (max - min); }
static inline int randi_range(int min, int max) { return min + rand() % (max - min + 1); }

MOSS_API float Moss_Cos(float v);
MOSS_API float Moss_Sin(float v);
MOSS_API float Moss_Tan(float v);
MOSS_API bool Moss_AABB2_Overlaps(const AABB2* box, float epsilon);
MOSS_API bool Moss_OBB2_Overlaps(const OBB2* box, float epsilon);
MOSS_API bool Moss_AABB3_Overlaps(const AABB3* box, float epsilon);
MOSS_API bool Moss_OBB3_Overlaps(const OBB3* box, float epsilon);
MOSS_API Mat44 Moss_Ortho(float left, float right, float bottom, float top, float near_plane, float far_plane);
MOSS_API Mat44 Moss_Perspective(float fov_y, float aspect, float near_plane, float far_plane);
MOSS_API Mat44 Moss_LookAt(Vec3 position, Vec3 target, Vec3 up);
MOSS_API Vec2 Moss_Vec2_Lerp(Vec2 a, Vec2 b, float t);
MOSS_API Vec2 Moss_Vec2_Clamp(Vec2 value, Vec2 min_value, Vec2 max_value);
MOSS_API Vec3 Moss_Vec3_Lerp(Vec3 a, Vec3 b, float t);
MOSS_API Vec3 Moss_Vec3_Clamp(Vec3 value, Vec3 min_value, Vec3 max_value);

#endif // MOSS_STDINC_H
