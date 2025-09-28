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
#include <d3d12.h>
#elif MOSS_GRAPHICS_METAL
#include <Metal/Metal.hpp>
#endif // MOSS_USE_METAL

enum TextureFormat {
    // Unsigned normalized color formats
    R8, 
    RG8, 
    RGB8, 
    RGBA8,
    
    // Signed normalized formats
    R8_SNORM, 
    RG8_SNORM, 
    RGB8_SNORM, 
    RGBA8_SNORM,
    
    // Floating-point formats
    R16F, 
    RG16F, 
    RGB16F, 
    RGBA16F,
    R32F, 
    RG32F, 
    RGB32F, 
    RGBA32F,
    
    // Integer formats
    R8UI, 
    RG8UI, 
    RGBA8UI, 
    R16UI, 
    RG16UI,
    RGBA16UI, 
    R32UI, 
    RG32UI, 
    RGBA32UI,
    
    // Depth formats
    Depth16, 
    Depth24, 
    Depth32F, 
    Depth24Stencil8, 
    Depth32FStencil8,
    
    // Compressed (optional support)
    DXT1, 
    DXT3, 
    DXT5, 
    BC4, 
    BC5, 
    BC6H, 
    BC7,
    
    // sRGB formats
    SRGB8, 
    SRGBA8
};

enum InputLayoutDescription {
		Position,						///< 3 float position
		Color,							///< 4 uint8 color
		Normal,							///< 3 float normal
		TexCoord,						///< 2 float texture coordinate
		InstanceColor,					///< 4 uint8 per instance color
		InstanceTransform,				///< 4x4 float per instance transform
		InstanceInvTransform,			///< 4x4 float per instance inverse transform
	};
enum class DrawPass { Shadow = 0U, Normal = 1U, Lighting = 2U, Transparent = 3U }; // In which draw pass to use this pipeline state
enum class Topology { Triangle = 0U, Line = 1U, Point = 2U };					            // The type of topology to emit
enum class FillMode { Solid = 0U, Wireframe = 1U };						                    // Fill mode of the triangles (<-Should be in Renderer Settings)
enum class DepthTest { Off = 0U, On = 1U };								                        // If depth write / depth test is on
enum class BlendMode { Opaque = 0U, Alpha = 1U, Additive = 2U };			              // How to blend the pixel from the shader in the back buffer
enum class CullMode { None = 0U, Backface = 1U, FrontFace = 2U };				          // How to cull triangles

struct Moss_Renderer;
struct Camera2D;
struct Camera3D;
struct Pipelinestate;
struct Texture;
struct PixelShader;
struct VertexShader;
struct ComputeShader;
struct Surface;
struct FogVolume;
struct SubViewport;
struct Mesh;
struct Model;
struct SkyBox;
struct Font;
struct Frustum2D;
struct Frustum3D;


struct TextureLight2D     { float intensity, rotation; Ref<Texture> texture; Float2 position; Color color; }; // TextureLight2 is a Light that uses a texture as its emission
struct DirectionalLight2D { float intensity, rotation; Color color; LightMask filter; };									 // DirectionalLight2
struct PointLight2D       { float intensity, rotation, radius; Float2 position; Color color; };			 // PointLight2

struct TextureLight2D     { float intensity, rotation; Ref<Texture> texture; Float2 position; Color color; }; // TextureLight2 is a Light that uses a texture as its emission
struct DirectionalLight2D { float intensity, rotation; Color color; };									 // DirectionalLight2
struct PointLight2D       { float intensity, rotation, radius; Float2 position; Color color; };			 // PointLight2
struct TextureLight3D 	 { float intensity; Ref<Texture> texture; Float3 position, rotation; Color color; };	//
struct DirectionalLight3D { float intensity; Float3 rotation; Color color; };														//
struct SpotLight3D 		 { float intensity, radius, angle, penumbra; Float3 position, rotation; Color color; };	//
struct OmniLight3D 		 { float intensity, radius; Float3 position; Color color; };							//

/*              Renderer lifecycle          */
/*! @brief Initalise Renderer. @param Moss_Window window. @ingroup Renderer. */
MOSS_API Moss_Renderer* Moss_CreateRenderer(Moss_Window* window);
/*! @brief Begin Frame Clears the renderer ready to capture the next frame. @param Moss_Renderer renderer. @ingroup Renderer. */
MOSS_API void Moss_RendererBeginFrame(Moss_Renderer* renderer);
/*! @brief End Frame calls to present frame. @param Moss_Renderer renderer. @ingroup Renderer. */
MOSS_API void Moss_RendererPresentFrame(Moss_Renderer* renderer);
/*! @brief Free renderer. @param Moss_Renderer renderer. @ingroup Renderer. */
MOSS_API void Moss_TerminateRenderer(Moss_Renderer* renderer);

MOSS_API Camera2* Moss_CreateCamera2(Moss_Renderer* renderer, );
MOSS_API void Moss_DestoryCamera2(Moss_Renderer* renderer, );

MOSS_API Camera3* Moss_CreateCamera3(Moss_Renderer* renderer, );
MOSS_API void  Moss_DestoryCamera3(Moss_Renderer* renderer, );

MOSS_API Moss_CreatePipelinestate(Moss_Renderer* renderer, VertexShader* vertex, const InputDescription* inputDescription, uint inputDescriptionCount, 
      const PixelShaderVK* pixel, DrawPass drawPass, FillMode fillMode, Topology topology, 
      EDepthTest inDepthTest, EBlendMode inBlendMode, ECullMode inCullMode);

MOSS_API Moss_DestoryPipelinestate(Moss_Renderer* renderer, );

MOSS_API Moss_CreateTexture(Moss_Renderer* renderer, );
MOSS_API void Moss_DestoryTexture(Moss_Renderer* renderer, );

MOSS_API Moss_CreateSurface(Moss_Renderer* renderer, );
MOSS_API void Moss_DestorySurface(Moss_Renderer* renderer, );

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





