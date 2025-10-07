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


typedef struct Vec2;
typedef struct Vec3;
typedef struct Vec4;
typedef struct iVec2;
typedef struct iVec3;
typedef struct iVec4;
typedef struct dVec2;
typedef struct dVec3;
typedef struct dVec4;
typedef struct Float2   { float x, y; };
typedef struct Float3   { float x, y, z; };
typedef struct Float4   { float x, y, z, w; };
typedef struct Int2     { int x, y; };
typedef struct Int3     { int x, y, z; };
typedef struct Int4     { int x, y, z, w; };
typedef struct Double2  { double x, y; };
typedef struct Double3  { double x, y, z; };
typedef struct Double4  { double x, y, z, w; };
typedef struct Mat2x3;
typedef struct Mat2x4;
typedef struct Mat2;
typedef struct Mat3x2;
typedef struct Mat3x4;
typedef struct Mat3;
typedef struct Mat4x2;
typedef struct Mat4x3;
typedef struct Mat4;
typedef struct Color    { unsigned char r, g, b, a; };
typedef struct Rect     { float x, y, width, height; };
typedef struct iRect    { int x, y, width, height; };
typedef struct Quat;
typedef struct Basis;

MOSS_API bool Moss_OBB2_Overlaps(const AABB2& inBox, float inEpsilon = 1.0e-6f);
MOSS_API bool Moss_OBB2_Overlaps(const OBB2& inBox, float inEpsilon = 1.0e-6f);
MOSS_API bool Moss_OBB3_Overlaps(const AABB3& inBox, float inEpsilon = 1.0e-6f);
MOSS_API bool Moss_OBB3_Overlaps(const OBB3& inBox, float inEpsilon = 1.0e-6f);



static inline Mat44 Moss_Ortho(float left, float right, float bottom, float top, float near, float far);
static inline Mat44 Moss_Perspective(float fovY, float aspect, float near, float far);
static inline Mat44 Moss_LookAt(Vec3 position, Vec3 target, Vec3 up);

static inline Vec3 Moss_Vec2_Lerp(Vec2 a, Vec2 b, float t);
static inline Vec3 Moss_Vec2_Clamp(Vec2 value, Vec2 min, Vec2 max);

static inline Vec3 Moss_Vec3_Lerp(Vec3 a, Vec3 b, float t);
static inline Vec3 Moss_Vec3_Clamp(Vec3 value, Vec3 min, Vec3 max);
#ifdef __cplusplus
}
#endif
