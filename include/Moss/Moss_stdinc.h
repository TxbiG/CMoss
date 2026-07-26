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

#if defined(_WIN32) || defined(_WIN64)
#  define MOSS_PLATFORM_WINDOWS
#  if defined(MOSS_SHARED_LIBRARY) && defined(MOSS_BUILD_SHARED_LIBRARY)
#    define MOSS_EXPORT __declspec(dllexport)
#  elif defined(MOSS_SHARED_LIBRARY)
#    define MOSS_EXPORT __declspec(dllimport)
#  else
#    define MOSS_EXPORT
#  endif
#elif defined(__APPLE__)
#  define MOSS_PLATFORM_APPLE
#  include <TargetConditionals.h>
#  if TARGET_OS_OSX
#    define MOSS_PLATFORM_MACOS
#  elif TARGET_OS_IPHONE
#    define MOSS_PLATFORM_IOS
#  endif
#  define MOSS_EXPORT __attribute__((visibility("default")))
#elif defined(__ANDROID__)
#  define MOSS_PLATFORM_ANDROID
#  define MOSS_EXPORT __attribute__((visibility("default")))
#elif defined(__linux__)
#  define MOSS_PLATFORM_LINUX
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
typedef Vec4 Quat;
typedef struct Plane { Vec3 normal; float distance; } Plane;
typedef struct AABB2 { Vec2 min; Vec2 max; } AABB2;
typedef struct AABB3 { Vec3 min; Vec3 max; } AABB3;
typedef struct OBB2 { Mat44 orientation; Vec2 center; Vec2 half_extents; } OBB2;
typedef struct OBB3 { Mat44 orientation; Vec3 center; Vec3 half_extents; } OBB3;
typedef struct Basis { Vec3 x, y, z; } Basis;

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
