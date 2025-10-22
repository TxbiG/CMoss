//                        MIT License
//
//                  Copyright (c) 2025 Toby
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
#ifndef MOSS_STDINC_H
#define MOSS_STDINC_H

/*!
 * @file Moss_stdinc.h
 * @brief Standard include header for the Moss Framework.
 *
 * Provides:
 * - Platform and compiler abstraction.
 * - Standardized type definitions and compile-time configuration.
 * - Utility macros, assertions, and inline helpers.
 * - Integration foundation for all other Moss subsystems.
 *
 * ---
 *
 * ### Overview:
 * `Moss_stdinc.h` acts as the foundational include for the entire Moss Framework.
 * It ensures consistent definitions across compilers, platforms, and languages.
 *
 * ---
 *
 * ### Core Responsibilities:
 * - **Platform Detection**
 *   - Identifies OS and hardware targets.
 *   - Defines portable symbols for Windows, Linux, macOS, Android, iOS, and WebAssembly.
 *
 * - **Compiler Detection**
 *   - Supports MSVC, GCC, Clang, and AppleClang.
 *   - Enables warning suppression and compiler-specific optimization attributes.
 *
 * - **Type Normalization**
 *   - Defines fixed-size integer and float types (uint8, int16, float32, etc).
 *   - Establishes Moss-specific aliases for cross-language consistency.
 *
 * - **Macros & Attributes**
 *   - Inline, constexpr, restrict, likely/unlikely, alignment, and export/import macros.
 *   - Simplifies platform-specific linkage (DLLs, shared libraries).
 *
 * - **Error Handling & Debugging**
 *   - Unified `MOSS_ASSERT`, `MOSS_LOG`, and panic/debug hooks.
 *   - Optional integration with custom logging systems or crash reporters.
 *
 * - **Namespace & Symbol Management**
 *   - Ensures consistent namespacing for C and C++.
 *   - Enables `MOSS_NAMESPACE_BEGIN` / `MOSS_NAMESPACE_END` macros.
 *
 * ---
 *
 * ### Platform Defines:
 * | Platform | Define | Notes |
 * |-----------|---------|-------|
 * | Windows   | `MOSS_PLATFORM_WINDOWS` | Desktop and UWP supported |
 * | Linux     | `MOSS_PLATFORM_LINUX` | Supports X11, Wayland, headless |
 * | macOS     | `MOSS_PLATFORM_MACOS` | Metal and OpenGL supported |
 * | iOS       | `MOSS_PLATFORM_IOS` | Metal-based rendering only |
 * | Android   | `MOSS_PLATFORM_ANDROID` | GLES / Vulkan support |
 * | Web (Emscripten) | `MOSS_PLATFORM_WEB` | WebAssembly / WebGPU support |
 *
 * ---
 *
 * ### Compiler Defines:
 * | Compiler | Define | Notes |
 * |-----------|---------|-------|
 * | MSVC      | `MOSS_COMPILER_MSVC` | Supports MSVC-specific intrinsics |
 * | GCC       | `MOSS_COMPILER_GCC` | Enables GCC attributes |
 * | Clang     | `MOSS_COMPILER_CLANG` | Unified with AppleClang |
 *
 * ---
 *
 * ### Common Macros:
 * ```cpp
 * #define MOSS_INLINE       inline __attribute__((always_inline))
 * #define MOSS_NOINLINE     __attribute__((noinline))
 * #define MOSS_ALIGN(x)     __attribute__((aligned(x)))
 * #define MOSS_LIKELY(x)    __builtin_expect(!!(x), 1)
 * #define MOSS_UNLIKELY(x)  __builtin_expect(!!(x), 0)
 *
 * #define MOSS_EXPORT       extern "C" __declspec(dllexport)
 * #define MOSS_IMPORT       extern "C" __declspec(dllimport)
 * ```
 *
 * ---
 *
 * ### Utility Macros:
 * - `MOSS_ARRAY_SIZE(arr)` — Returns the number of elements in an array.
 * - `MOSS_UNUSED(x)` — Prevents unused variable warnings.
 * - `MOSS_BIT(x)` — Shifts bitmask `(1 << x)`.
 * - `MOSS_OFFSET_OF(type, member)` — Returns byte offset of struct member.
 *
 * ---
 *
 * Ensures version compatibility between Moss Framework components and bindings.
 *
 * ---
 *
 * ### Future Roadmap:
 * - Platform-independent threading primitives (atomic, mutex, condition variable).
 * - Intrinsic wrappers for SIMD (SSE, NEON, AVX).
 * - Compile-time feature detection macros (`MOSS_HAS_VULKAN`, `MOSS_HAS_OPENXR`, etc).
 * - Static compile-time assertion and reflection utilities.
 *
 */

#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include <Moss/Core/Core.h>


// Determine platform
#if defined(MOSS_PLATFORM_BLUE)
	// Correct define already defined, this overrides everything else
#elif defined(_WIN32) || defined(_WIN64)
	#include <winapifamily.h>
	#if WINAPI_FAMILY == WINAPI_FAMILY_APP
		// Building for Universal Windows Platform
		#define MOSS_PLATFORM_WINDOWS_UWP
	#endif
	// Windows
	#define MOSS_PLATFORM_WINDOWS
#elif defined(ANDROID) || defined(__ANDROID__) 	// Android is linux too, so that's why we check it first
	#define MOSS_PLATFORM_ANDROID
	// Add Android TV
#elif (defined(linux) || defined(__linux) || defined(__linux__))
	// Linux
    #define MOSS_PLATFORM_LINUX
#elif (defined(__unix__) || defined(__unix) || defined(unix))
	// UNIX
	#define MOSS_PLATFORM_UNIX 
#elif defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__NetBSD__)
	#define MOSS_PLATFORM_BSD
#elif defined(__APPLE__)
	#include <TargetConditionals.h>
	#if defined(TARGET_OS_IPHONE) && !TARGET_OS_IPHONE
		// Apple MacOS
		#define MOSS_PLATFORM_MACOS
	#elif defined(TARGET_OS_IPHONE)
		// Apple IOS Phone
		#define MOSS_PLATFORM_IOS
	#elif defined(TARGET_OS_TV)
		// Apple TV
		#define MOSS_PLATFORM_TVOS
	#endif // TARGET_OS_IPHONE && !TARGET_OS_IPHONE
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

// #if defined(__i386__)
// Detect CPU architecture
#if defined(__x86_64__) || defined(_M_X64) || defined(__i386__) || defined(_M_IX86)
	// X86 CPU architecture
	#define MOSS_CPU_X86
	#if defined(__x86_64__) || defined(_M_X64)
		#define MOSS_CPU_ADDRESS_BITS 64
	#else
		#define MOSS_CPU_ADDRESS_BITS 32
	#endif
	#define MOSS_USE_SSE
	#define MOSS_VECTOR_ALIGNMENT 16
	#define MOSS_DVECTOR_ALIGNMENT 32

	#if defined(__AVX512F__) && defined(__AVX512VL__) && defined(__AVX512DQ__) && !defined(MOSS_USE_AVX512)
		#define MOSS_USE_AVX512
	#endif
	#if (defined(__AVX2__) || defined(MOSS_USE_AVX512)) && !defined(MOSS_USE_AVX2)
		#define MOSS_USE_AVX2
	#endif
	#if (defined(__AVX__) || defined(MOSS_USE_AVX2)) && !defined(MOSS_USE_AVX)
		#define MOSS_USE_AVX
	#endif
	#if (defined(__SSE4_2__) || defined(MOSS_USE_AVX)) && !defined(MOSS_USE_SSE4_2)
		#define MOSS_USE_SSE4_2
	#endif
	#if (defined(__SSE4_1__) || defined(MOSS_USE_SSE4_2)) && !defined(MOSS_USE_SSE4_1)
		#define MOSS_USE_SSE4_1
	#endif
	#if (defined(__F16C__) || defined(MOSS_USE_AVX2)) && !defined(MOSS_USE_F16C)
		#define MOSS_USE_F16C
	#endif
	#if (defined(__LZCNT__) || defined(MOSS_USE_AVX2)) && !defined(MOSS_USE_LZCNT)
		#define MOSS_USE_LZCNT
	#endif
	#if (defined(__BMI__) || defined(MOSS_USE_AVX2)) && !defined(MOSS_USE_TZCNT)
		#define MOSS_USE_TZCNT
	#endif
	#ifndef MOSS_CROSS_PLATFORM_DETERMINISTIC
		#if defined(MOSS_COMPILER_CLANG) || defined(MOSS_COMPILER_GCC)
			#if defined(__FMA__) && !defined(MOSSH_USE_FMADD)
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
		#define MOSS_USE_NEON
		#define MOSS_VECTOR_ALIGNMENT 16
		#define MOSS_DVECTOR_ALIGNMENT 32
	#else
		#define MOSS_CPU_ADDRESS_BITS 32
		#define MOSS_VECTOR_ALIGNMENT 8 // 32-bit ARM does not support aligning on the stack on 16 byte boundaries
		#define MOSS_DVECTOR_ALIGNMENT 8
	#endif
#elif defined(__riscv)
	// RISC-V CPU architecture
	#define MOSS_CPU_RISCV
	#if __riscv_xlen == 64
		#define MOSS_CPU_ADDRESS_BITS 64
		#define MOSS_VECTOR_ALIGNMENT 16
		#define MOSS_DVECTOR_ALIGNMENT 32
	#else
		#define MOSS_CPU_ADDRESS_BITS 32
		#define MOSS_VECTOR_ALIGNMENT 16
		#define MOSS_DVECTOR_ALIGNMENT 8
	#endif
#elif defined(MOSS_PLATFORM_WASM)
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
		#define MOSS_USE_SSE
		#define MOSS_USE_SSE4_1
		#define MOSS_USE_SSE4_2
	#endif
#elif (defined(__powerpc__) || defined(__powerpc64__))
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
	#define MOSS_VECTOR_ALIGNMENT 16
	#define MOSS_DVECTOR_ALIGNMENT 8
#elif defined(__loongarch__)
	// LoongArch CPU architecture
	#define MOSS_CPU_LOONGARCH
	#if defined(__loongarch64)
		#define MOSS_CPU_ADDRESS_BITS 64
	#else
		#define MOSS_CPU_ADDRESS_BITS 32
	#endif
	#define MOSS_VECTOR_ALIGNMENT 16
	#define MOSS_DVECTOR_ALIGNMENT 8
#elif defined(__e2k__)
	// E2K CPU architecture (MCST Elbrus 2000)
	#define MOSS_CPU_E2K
	#define MOSS_CPU_ADDRESS_BITS 64
	#define MOSS_VECTOR_ALIGNMENT 16
	#define MOSS_DVECTOR_ALIGNMENT 32

	// Compiler flags on e2k arch determine CPU features
	#if defined(__SSE__) && !defined(MOSS_USE_SSE)
		#define MOSS_USE_SSE
	#endif
#else
	#error Unsupported CPU architecture
#endif

// If this define is set, Jolt is compiled as a shared library
#ifdef MOSS_SHARED_LIBRARY
	#ifdef MOSS_BUILD_SHARED_LIBRARY
		// While building the shared library, we must export these symbols
		#if defined(MOSS_PLATFORM_WINDOWS) && !defined(MOSS_COMPILER_MINGW)
			#define MOSS_EXPORT __declspec(dllexport)
		#else
			#define MOSS_EXPORT __attribute__ ((visibility ("default")))
			#if defined(MOSS_COMPILER_GCC)
				// Prevents an issue with GCC attribute parsing (see https://gcc.gnu.org/bugzilla/show_bug.cgi?id=69585)
				#define MOSS_EXPORT_GCC_BUG_WORKAROUND [[gnu::visibility("default")]]
			#endif
		#endif
	#else
		// When linking against Jolt, we must import these symbols
		#if defined(MOSS_PLATFORM_WINDOWS) && !defined(MOSS_COMPILER_MINGW)
			#define MOSS_EXPORT __declspec(dllimport)
		#else
			#define MOSS_EXPORT __attribute__ ((visibility ("default")))
			#if defined(MOSS_COMPILER_GCC)
				// Prevents an issue with GCC attribute parsing (see https://gcc.gnu.org/bugzilla/show_bug.cgi?id=69585)
				#define MOSS_EXPORT_GCC_BUG_WORKAROUND [[gnu::visibility("default")]]
			#endif
		#endif
	#endif
#else
	// If the define is not set, we use static linking and symbols don't need to be imported or exported
	#define MOSS_EXPORT
#endif

#define MOSS_API MOSS_EXPORT

#ifndef MOSS_EXPORT_GCC_BUG_WORKAROUND
	#define MOSS_EXPORT_GCC_BUG_WORKAROUND MOSS_EXPORT
#endif

// Define inline macro
#if defined(MOSS_NO_FORCE_INLINE)
	#define MOSS_INLINE inline
#elif defined(MOSS_COMPILER_CLANG)
	#define MOSS_INLINE __inline__ __attribute__((always_inline))
#elif defined(MOSS_COMPILER_GCC)
	// On gcc 14 using always_inline in debug mode causes error: "inlining failed in call to 'always_inline' 'XXX': function not considered for inlining"
	// See: https://github.com/jrouwe/JoltPhysics/issues/1096
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

#define MOSS_FALSE   0U
#define MOSS_TRUE    1U

// Signed
#define MAX_INT8    ((int8_t)(0x7F))
#define MAX_INT16   ((int16_t)(0x7FFF))
#define MAX_INT32   ((int32_t)(0x7FFFFFFF))
#define MAX_INT64   ((int64_t)(0x7FFFFFFFFFFFFFFF))
#define MIN_INT8    ((int8_t)(~0x7F))
#define MIN_INT16   ((int16_t)(~0x7FFF))
#define MIN_INT32   ((int32_t)(~0x7FFFFFFF))
#define MIN_INT64   ((int64_t)(~0x7FFFFFFFFFFFFFFF))

// Unsigned
#define MAX_UINT8   ((uint8_t)(0xFF))
#define MAX_UINT16  ((uint16_t)(0xFFFF))
#define MAX_UINT32  ((uint32_t)(0xFFFFFFFFu))
#define MAX_UINT64  ((uint64_t)(0xFFFFFFFFFFFFFFFF))
#define MIN_UINT8   ((uint8_t)(0x00))
#define MIN_UINT16  ((uint16_t)(0x0000))
#define MIN_UINT32  ((uint32_t)(0x00000000))
#define MIN_UINT64  ((uint64_t)(0x0000000000000000))

#ifndef PI
#   define PI          3.141592653589793238462643383279502884F
#endif  // PI

#define HALF_PI        1.5707963267948966F
#define QUARTER_PI     0.7853981633974483F

#ifndef TAU
#   define TAU         PI * 2
#endif  // TAU
/*
#ifndef EPSILON
#   define FLT_EPSILON 1.1920928955078125e-07F
#endif  // EPSILON
*/
#ifndef INF
#   define INF         ((float)(1e+300 * 1e+300))
#endif  // INF

#ifndef M_E
#   define M_E        2.71828182845904523536F   // e
#endif // M_E
#ifndef M_LOG2E
#   define M_LOG2E    1.44269504088896340736F   // log2(e)
#endif // M_LOG2E
#ifndef M_LOG10E
#   define M_LOG10E   0.434294481903251827651F  // log10(e)
#endif // M_LOG10E
#ifndef M_LN2
#   define M_LN2      0.693147180559945309417F  // ln(2)
#endif // M_LN2
#ifndef M_LN10
#   define M_LN10     2.30258509299404568402F   // ln(10)
#endif // M_LN10
#ifndef M_2_SQRTPI
#   define M_2_SQRTPI 1.12837916709551257390F   // 2/sqrt(pi)
#endif // M_2_SQRTPI
#ifndef M_SQRT2
#   define M_SQRT2    1.41421356237309504880F   // sqrt(2)
#endif // M_SQRT2
#ifndef M_SQRT1_2
#   define M_SQRT1_2  0.707106781186547524401F  // 1/sqrt(2)
#endif // M_SQRT1_2

#ifndef ATAN_POLY
#   define ATAN_POLY(x)  ((x) * (0.999866 + 0.333331 * (x) * (x)))
#endif // ATAN_POLY

#define RAD(x)        ((x) * (PI / 180.0))
#define FACT(n)       ((n) <= 1 ? 1 : (n) * FACT((n) - 1))
#define SIN(x)        ((x) - ((x)*(x)*(x))/FACT(3) + ((x)*(x)*(x)*(x)*(x))/FACT(5) - ((x)*(x)*(x)*(x)*(x)*(x)*(x))/FACT(7))
#define COS(x)        (1 - ((x)*(x))/FACT(2) + ((x)*(x)*(x)*(x))/FACT(4) - ((x)*(x)*(x)*(x)*(x)*(x))/FACT(6))
#define TAN(x)        (SIN(x) / COS(x))
#define SIGN(x)       ((inV < 0)? (-1) : (1))
//#define LERP(a, b, t) ((a) + (t) * ((b) - (a)))

#define ABS(x)       ((x) < 0 ? -(x) : (x))
#define ATAN2(y, x)  ((x) > 0 ? ATAN_POLY((y) / (x)) : \ ((x) < 0 && (y) >= 0 ? ATAN_POLY((y) / (x)) + PI : \ ((x) < 0 && (y) < 0 ? ATAN_POLY((y) / (x)) - PI : \ ((x) == 0 && (y) > 0 ? HALF_PI : \ ((x) == 0 && (y) < 0 ? -HALF_PI : 0)))))
#define SQRT(x)      ({ double guess = (x) / 2; \ for (int i = 0; i < 5; i++) guess = (guess + (x) / guess) / 2; \ guess; }) // using Newton method
#define ACOS(x)      (ATAN2(SQRT(1 - (x) * (x)), (x)))
#define ASIN(x)      (ATAN2((x), SQRT(1 - (x) * (x))))
#define ATAN(x)      (ATAN2((x), 1))
#define CEIL(x)      (((x) == (int)(x)) ? (x) : (int)((x) + 1))
#define FABS(x)      ((x) < 0 ? -(x) : (x))
#define FLOOR(x)     (((x) == (int)(x)) ? (x) : (int)(x))
#define FMOD(x, y)   ((x) - ((int)((x) / (y))) * (y))

// Logarithm approximations using Taylor series
#define LOG(x)       ((x) - 1 - (((x) - 1) * ((x) - 1)) / 2 + (((x) - 1) * ((x) - 1) * ((x) - 1)) / 3)
#define LOG10(x)     (LOG(x) / LN10)
#define LOG2(x)      (LOG(x) / LN2)

// Power functions
#define EXP(x)       (1 + (x) + (x) * (x) / 2 + (x) * (x) * (x) / 6 + (x) * (x) * (x) * (x) / 24)
#define POW(b, e)    (EXP((e) * LOG(b)))
#define EXP2(x)      (POW(2, (x)))

#define ROUND(x)     ((x) < 0 ? (int)((x) - 0.5) : (int)((x) + 0.5))
#define TRUNC(x)     ((x) < 0 ? CEIL(x) : FLOOR(x))

// Hyperbolic functions
#define COSH(x)      ((EXP(x) + EXP(-(x))) / 2)
#define SINH(x)      ((EXP(x) - EXP(-(x))) / 2)
#define TANH(x)      (SINH(x) / COSH(x))

// Inverse hyperbolic functions
#define ACOSH(x)     (LOG((x) + SQRT((x) * (x) - 1)))
#define ASINH(x)     (LOG((x) + SQRT((x) * (x) + 1)))
#define ATANH(x)     (0.5 * LOG((1 + (x)) / (1 - (x))))

// Hypotenuse function
#define HYPOT(x, y)  (SQRT((x) * (x) + (y) * (y)))

#define DEG_TO_RAD(d) ((d) * (M_PI / 180.0))
#define RAD_TO_DEG(r) ((r) * (180.0 / M_PI))

#define CLAMP(x, a, b) (((x) < (a)) ? (a) : (((x) > (b)) ? (b) : (x)))

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MOSS_DIFFERENCE(x, y) ((x) < (y) ? (y) - (x) : (x) - (y))

#define SQUARE(x) (x * x)
#define CUBED(x) (x * x * x)

#define ArraySize(x) (sizeof(x)) / (sizeof((x)[0]))

typedef signed char         s8;
typedef signed short        s16;
typedef signed int          s32;
typedef signed long long    s64;

typedef unsigned char       u8;
typedef unsigned short      u16;
typedef unsigned int        u32;
typedef unsigned long long  u64;

#if (defined(MOSS_PLATFORM_WINDOWS) || defined(MOSS_PLATFORM_MACSO) || defined(MOSS_PLATFORM_LINUX))
#include <stddef.h>
typedef unsigned long long size;
#else
typedef unsigned int size;
#endif

// Signed
#define MAX_INT8    ((int8_t)(0x7F))
#define MAX_INT16   ((int16_t)(0x7FFF))
#define MAX_INT32   ((int32_t)(0x7FFFFFFF))
#define MAX_INT64   ((int64_t)(0x7FFFFFFFFFFFFFFF))
#define MIN_INT8    ((int8_t)(~0x7F))
#define MIN_INT16   ((int16_t)~0x7FFF)
#define MIN_INT32   ((int32_t)(~0x7FFFFFFF))
#define MIN_INT64   ((int64_t)(~0x7FFFFFFFFFFFFFFF))

// Unsigned
#define MAX_UINT8   ((uint8_t)(0xFF))
#define MAX_UINT16  ((uint16_t)(0xFFFF))
#define MAX_UINT32  ((uint32_t)(0xFFFFFFFFu))
#define MAX_UINT64  ((uint64_t)(0xFFFFFFFFFFFFFFFF))
#define MIN_UINT8   ((uint8_t)0x00)
#define MIN_UINT16  ((uint16_t)0x0000)
#define MIN_UINT32  ((uint32_t)0x00000000)
#define MIN_UINT64  ((uint64_t)(0x0000000000000000))


#ifndef MOSS_MALLOC
    #define MOSS_MALLOC(size)       malloc(sz)
#endif
#ifndef MOSS_CALLOC
    #define MOSS_CALLOC(nmemb, size)     calloc(n,sz)
#endif
#ifndef MOSS_REALLOC
    #define MOSS_REALLOC(ptr, size)  realloc(ptr,sz)
#endif
#ifndef MOSS_FREE
    #define MOSS_FREE(ptr)        free(ptr)
#endif
#ifndef MOSS_ALIGNED_ALLOC
    #define MOSS_ALIGNED_ALLOC(ptr, size_t alignment, size_t size) aligned_alloc(alignment, alignment*sizeof *ptr);
#endif
#ifndef MOSS_ALIGNED_FREE
    #define MOSS_ALIGNED_FREE(void *mem) aligned_free(void *mem)
#endif

typedef float DeltaTime;

#ifdef __cplusplus
extern "C" {
#endif

static inline void seed_random() { srand((unsigned int)time(NULL)); }
static inline float randf_range(float min, float max) { return min + (float)rand() / (float)RAND_MAX * (max - min); }
static inline int randi_range(int min, int max) { return min + rand() % (max - min + 1); }

#ifdef __cplusplus
}
#endif

#endif // MOSS_STDINC_H















