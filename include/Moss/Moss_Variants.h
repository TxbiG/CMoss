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


struct Vec2;
struct Vec3;
struct Vec4;
struct iVec2;
struct iVec3;
struct iVec4;
struct dVec2;
struct dVec3;
struct dVec4;
struct Float2   { float x, y; };
struct Float3   { float x, y, z; };
struct Float4   { float x, y, z, w; };
struct Int2     { int x, y; };
struct Int3     { int x, y, z; };
struct Int4     { int x, y, z, w; };
struct Double2  { double x, y; };
struct Double3  { double x, y, z; };
struct Double4  { double x, y, z, w; };
struct Mat2x3;
struct Mat2x4;
struct Mat2;
struct Mat3x2;
struct Mat3x4;
struct Mat3;
struct Mat4x2;
struct Mat4x3;
struct Mat4;
struct Color    { float r, g, b, a; };
struct Rect     { float x, y, width, height; };
struct iRect    { int x, y, width, height; };
struct Quat;
struct Basis;
struct AABB2;
struct AABB3;
struct OBB2;
struct OBB3;


MOSS_API bool Moss_OBB2_Overlaps(const AABB2& inBox, float inEpsilon = 1.0e-6f);
MOSS_API bool Moss_OBB2_Overlaps(const OBB2& inBox, float inEpsilon = 1.0e-6f);
MOSS_API bool Moss_OBB3_Overlaps(const AABB3& inBox, float inEpsilon = 1.0e-6f);
MOSS_API bool Moss_OBB3_Overlaps(const OBB3& inBox, float inEpsilon = 1.0e-6f);



static inline Mat44 Moss_Ortho(float left, float right, float bottom, float top, float near, float far);
static inline Mat44 Moss_Perspective(float fovY, float aspect, float near, float far);
static inline Mat44 Moss_LookAt(Vec3 position, Vec3 target, Vec3 up);

static inline Vec3 Moss_Vec2_Lerp(Vec2 a, float b, float t);
static inline Vec3 Moss_Vec3_Clamp(Vec2 value, Vec2 min, Vec2 max);

#ifdef __cplusplus
}
#endif
