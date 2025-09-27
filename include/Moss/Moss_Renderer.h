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
#ifndef MOSS_RENDERER_H
#define MOSS_RENDERER_H


#ifdef __cplusplus
extern "C" {
#endif

#ifdef MOSS_GRAPHICS_OPENGL
#include <Moss/Renderer/GL/FontGL.h>
//#include <Moss/Renderer/GL/MeshGL.h>
#include <Moss/Renderer/GL/ShaderGL.h>
#include <Moss/Renderer/GL/SubViewportGL.h>
#include <Moss/Renderer/GL/SurfaceGL.h>
#include <Moss/Renderer/GL/TextureGL.h>
#include <Moss/Renderer/GL/ShaderGL.h>
#endif
#ifdef MOSS_GRAPHICS_VULKAN
#include <vulkan/vulkan.h>
#elif MOSS_GRAPHICS_DIRECTX
#include <Moss/Renderer/DX12/Renderer_DX12.h>
#elif MOSS_GRAPHICS_METAL
#include <Metal/Metal.hpp>
#endif // MOSS_USE_METAL



// Graphics Specific
#ifdef MOSS_GRAPHICS_OPENGL
#endif

#ifdef MOSS_GRAPHICS_VULKAN
#endif

#ifdef MOSS_GRAPHICS_DIRECTX
#endif

#ifdef MOSS_GRAPHICS_METAL
#endif

#ifdef __cplusplus
}
#endif


#endif // MOSS_RENDERER_H
