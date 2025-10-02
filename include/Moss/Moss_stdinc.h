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


#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include <Moss/Core/Core.h>

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


void * Moss_calloc(size_t nmemb, size_t size);
void * Moss_realloc(void *mem, size_t size);
void * Moss_malloc(size_t size);
void Moss_free(void *mem);

void * Moss_aligned_alloc(size_t alignment, size_t size);
void Moss_aligned_free(void *mem);

static inline void seed_random() { srand((unsigned int)time(NULL)); }
static inline float randf_range(float min, float max) { return min + (float)rand() / (float)RAND_MAX * (max - min); }
static inline int randi_range(int min, int max) { return min + rand() % (max - min + 1); }

#ifdef __cplusplus
}
#endif

#endif // MOSS_STDINC_H









