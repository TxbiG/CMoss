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

#ifdef MOSS_USE_OPENGL
#include <Moss/Renderer/GL/FontGL.h>
//#include <Moss/Renderer/GL/MeshGL.h>
#include <Moss/Renderer/GL/ShaderGL.h>
#include <Moss/Renderer/GL/SubViewportGL.h>
#include <Moss/Renderer/GL/SurfaceGL.h>
#include <Moss/Renderer/GL/TextureGL.h>
#include <Moss/Renderer/GL/ShaderGL.h>
#endif
#ifdef MOSS_USE_VULKAN
#include <vulkan/vulkan.h>
#include <Moss/Renderer/VK/Renderer_VK.h>
#elif MOSS_USE_DIRECTX
#include <Moss/Renderer/DX12/Renderer_DX12.h>
#elif MOSS_USE_METAL
#include <Moss/Renderer/MTL/Renderer_MTL.h>
#include <Metal/Metal.hpp>
#endif // MOSS_USE_METAL


enum class AntiAliasing {
    None = 0,
    MSAA,
    TAA,
    FXAA,
    SMAA,
    SSAA
};

#include <chrono>

class [[nodiscard]] DeltaTime {
public:
    DeltaTime() : lastTime(std::chrono::steady_clock::now()), deltaTime(0.0f), elapsedTime(0.0f), frameCount(0), fps(0) { }

    void StartFrame() {
        auto now = std::chrono::steady_clock::now();
        deltaTime = std::chrono::duration<float>(now - lastTime).count();
        lastTime = now;

        frameCount++;
        elapsedTime += deltaTime;
        if (elapsedTime >= 1.0f) {
            fps = frameCount;
            frameCount = 0;
            elapsedTime = 0.0f;
        }
    }

    float GetDeltaTime() const { return deltaTime; }
    int GetFPS() const { return fps; }

private:
    std::chrono::steady_clock::time_point lastTime;
    float deltaTime = 0.0f;
    float elapsedTime = 0.0f;
    int frameCount = 120;
    int fps;
};

// Todo: 
// Instance / batching Rendering
// Bindless Textures
// Texture compression
// Mesh compression
// Animation Optimization
// Rigging and Skinning Optimization
// Allow Material Baking
// Add pooling for textures, materials, etc.

// TODO: 
// DebugMode: Solid, WireFrame, Lighting etc. Cast Shadows. show collisions
// Sampler: Take Screenshots and videos. Input and output
// deltaTime & Frames

/* #define MAX_LIGHTING 50
typedef enum AntiAliasing { None, FXAA, TAA, MSAA } AntiAliasing;*/

// ==========================================
//          Forward declorations
// ==========================================
static int TEMPW;
static int TEMPH;
// Forward declarations
struct PostProcessingPipeline;
struct PostProcess;

/*              Renderer lifecycle          */
/*
void Canvas() {
    Mat44 view = Mat44::sIdentity();
    Mat44 proj = ortho(0.0f, screenWidth, 0.0f, screenHeight, -1.0f, 1.0f);
    Mat44 viewProj = proj * view;
}
*/

/*! @brief X. @param X X. @ingroup Renderer. */
//Surface SubViewport(int x, int y, int width, int height);

//bool Moss_FramePerSecond();
/*                 Callbacks                */
// Renderer Configs
/*
typedef void (Moss_RendererSetVSync)              (bool enable);
typedef void (Moss_RendererSetFPS)                (int value);
typedef void (Moss_RendererSetOcclusionCulling)   (bool enable);
typedef void (Moss_RendererSetAntiAliasing)       ();

// Cameras
typedef void (Moss_RendererGetCamera2D)  (Camera2 camera);
typedef void (Moss_RendererGetCamera3D)  (Camera3 camera);

// PostProcessing
//typedef void (Moss_RendererSetPostProcessing)    (Shader shader);
// Compositors
//typedef void (Moss_RendererSetCompositors)       (Shader shader);


#if defined(MOSS_USE_OPENGL) || defined(MOSS_USE_OPENGLES)
void Moss_GLCreateComputeShader();
void Moss_GLCreateVertexComputeShader();
void Moss_GLCreateFragmentComputeShader();
void Moss_GLCreateTessControlComputeShader();
void Moss_GLCreateTessEvaluationComputeShader();
void Moss_GLCreateGeometryComputeShader();
*/

#ifdef __cplusplus
}
#endif

#endif // MOSS_RENDERER_H