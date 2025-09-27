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

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __cplusplus
}
#endif
