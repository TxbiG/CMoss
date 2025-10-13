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

/*!
 * @file Moss_Renderer.h
 * @brief Core rendering interface for the Moss Framework.
 *
 * The renderer module provides the abstraction layer for all 2D and 3D graphics
 * operations. It serves as a unified, API-agnostic rendering backend capable of
 * targeting multiple graphics APIs (Vulkan, OpenGL, Metal, and DirectX 12).
 *
 * ### Primary Responsibilities:
 * - **2D and 3D Rendering** — Handles scene rendering for both worlds and UI layers.
 * - **Debug Visualization** — Supports drawing collision bounds, gizmos, and profiling overlays.
 * - **Lighting & Shadows** — Manages dynamic and baked lighting, real-time shadow mapping, and reflections.
 * - **Post-Processing Pipeline** — Provides a customizable chain for effects such as bloom, tone mapping, FXAA/TAA, and color grading.
 * - **Particle Systems** — Unified particle framework for both 2D and 3D effects.
 * - **Reflection Probes & Global Illumination** — Enables environment-based lighting and reflections.
 * - **Compositor (Planned)** — Future abstraction for multi-pass rendering and post-fx composition.
 * 
 *
 * ### Graphics Rendering
 * - **OpenGL** - Compatibility & Mobile
 * - **Vulkan** - Forward+ & Mobile
 * - **DirectX 12** - Forward+
 * - **Metal** - Forward+ & Mobile
 *
 * ### Secondary Systems:
 * - **Scene Graph / Hierarchy** — Entity rendering order, transform propagation, and culling organization.
 * - **Animation Support** — Skeletal and morph target animation for characters, props, and environment elements.
 *
 * ### Planned Features / TODO:
 * - **Graphics API Abstraction Layers** — Full separation of renderer logic from API-specific backends.
 * - **Level of Detail (LOD) System** — Mesh simplification and distance-based swapping.
 * - **Occlusion & View Culling** — Reduce draw calls via frustum and depth testing.
 * - **Multithreaded Render Submission** — Asynchronous job-based rendering pipeline (future optimization).
 *
 * The renderer acts as the core visual subsystem of the Moss engine, directly
 * integrated with scene management, physics visualization, and UI rendering layers.
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef MOSS_GRAPHICS_OPENGL
#include <Moss/Moss_GL.h>
#elif MOSS_GRAPHICS_VULKAN
#include <vulkan/vulkan.h>
#elif MOSS_GRAPHICS_DIRECTX
#include <d3d12.h>
#elif MOSS_GRAPHICS_METAL
#include <Metal/Metal.hpp>
#endif // MOSS_USE_METAL

#define VIRTUAL_RESOLUTION_WIDTH 1920
#define VIRTUAL_RESOLUTION_HEIGHT 1080

#define MAX_DECALS 200
#define MAX_LIGHTS2D 200
#define MAX_LIGHTS3D 200

typedef enum TextureFormat {
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

typedef enum InputLayoutDescription {
		Position,						///< 3 float position
		Color,							///< 4 uint8 color
		Normal,							///< 3 float normal
		TexCoord,						///< 2 float texture coordinate
		InstanceColor,					///< 4 uint8 per instance color
		InstanceTransform,				///< 4x4 float per instance transform
		InstanceInvTransform,			///< 4x4 float per instance inverse transform
	};
typedef enum class DrawPass { Shadow = 0U, Normal = 1U, Lighting = 2U, Transparent = 3U }; // In which draw pass to use this pipeline state
typedef enum class Topology { Triangle = 0U, Line = 1U, Point = 2U };					            // The type of topology to emit
typedef enum class FillMode { Solid = 0U, Wireframe = 1U };						                    // Fill mode of the triangles (<-Should be in Renderer Settings)
typedef enum class DepthTest { Off = 0U, On = 1U };								                        // If depth write / depth test is on
typedef enum class BlendMode { Opaque = 0U, Alpha = 1U, Additive = 2U };			              // How to blend the pixel from the shader in the back buffer
typedef enum class CullMode { None = 0U, Backface = 1U, FrontFace = 2U };				          // How to cull triangles

typedef struct Moss_Renderer;
typedef struct Camera2D { Float2 position, offset; float zoom = 1.0f, float rotation = 0.0f; };
typedef struct Camera3D {
	Float3 position;
	Float3 up;    // Y is up
    Float3 target;
    float speed = 0.1f;
    float sensitivity = 100;
    float fov = 45.0f;          // Field of view (degrees)
    float aspectRatio;          // avoid divide-by-zero
    float nearPlane = 0.1f;
    float farPlane = 1000.0f; 
};
typedef struct Shader;
typedef struct ShaderPixel;
typedef ShaderPixel PostProcessing;
typedef struct ShaderVertex;
typedef struct ShaderComputing;
typedef struct Pipelinestate;
typedef struct Texture;
typedef Texture Texture2D;
typedef Texture NoiseTexture2D;
typedef struct Surface;
typedef struct FogVolume;
typedef struct SubViewport;
typedef struct Mesh;
typedef struct Model;
typedef struct SkyBox;
typedef struct Font;
typedef struct Frustum2D;
typedef struct Frustum3D;


typedef struct TextureLight2D     { float intensity, rotation; Ref<Texture> texture; Float2 position; Color color; }; // TextureLight2 is a Light that uses a texture as its emission
typedef struct DirectionalLight2D { float intensity, rotation; Color color; };									 // DirectionalLight2
typedef struct PointLight2D       { float intensity, rotation, radius; Float2 position; Color color; };			 // PointLight2
typedef struct TextureLight3D 	 { float intensity; Ref<Texture> texture; Float3 position, rotation; Color color; };	//
typedef struct DirectionalLight3D { float intensity; Float3 rotation; Color color; };														//
typedef struct SpotLight3D 		 { float intensity, radius, angle, penumbra; Float3 position, rotation; Color color; };	//
typedef struct OmniLight3D 		 { float intensity, radius; Float3 position; Color color; };							//

/*              Renderer lifecycle          */
/*! @brief Initalise Renderer. @param Moss_Window window. @ingroup Renderer. */
MOSS_API Moss_Renderer* Moss_CreateRenderer(Moss_Window* window);
/*! @brief Begin Frame Clears the renderer ready to capture the next frame. @param Moss_Renderer renderer. @ingroup Renderer. */
MOSS_API void Moss_RendererBeginFrame(Moss_Renderer* renderer);
/*! @brief End Frame calls to present frame. @param Moss_Renderer renderer. @ingroup Renderer. */
MOSS_API void Moss_RendererPresentFrame(Moss_Renderer* renderer);
/*! @brief Background color each frame by default its set to a grey color. @param Moss_Renderer renderer. @param Color color@ingroup Renderer. */
MOSS_API void Moss_RendererSetBackground(Moss_Renderer* renderer, Color color);
/*! @brief Free renderer. @param Moss_Renderer renderer. @ingroup Renderer. */
MOSS_API void Moss_TerminateRenderer(Moss_Renderer* renderer);

MOSS_API Camera2D* Moss_CreateCamera2D(Moss_Renderer* renderer, Float2 position, Float2 offset);
MOSS_API void Moss_DestroyCamera2D(Camera2D* camera);

MOSS_API Camera3D* Moss_CreateCamera3D(Moss_Renderer* renderer, Float3 position, Float3 target);
MOSS_API void Moss_DestroyCamera3D(Camera3D* camera);

MOSS_API ShaderPixel* Moss_Create_ShaderPixel()
MOSS_API ShaderVertex* Moss_Create_ShaderVertex()
MOSS_API ShaderComputing* Moss_Create_ShaderComputing()
MOSS_API void Moss_Destroy_Shader();

MOSS_API Pipelinestate* Moss_CreatePipelinestate(Moss_Renderer* renderer, VertexShader* vertex, const InputDescription* inputDescription, uint inputDescriptionCount, 
      const PixelShaderVK* pixel, DrawPass drawPass, FillMode fillMode, Topology topology, 
      EDepthTest inDepthTest, EBlendMode inBlendMode, ECullMode inCullMode);

MOSS_API void Moss_DestoryPipelinestate(Moss_Renderer* renderer, );

MOSS_API Texture* Moss_CreateTexture(Moss_Renderer* renderer, );
MOSS_API void Moss_DestoryTexture(Moss_Renderer* renderer, );

MOSS_API Surface* Moss_CreateSurface(Moss_Renderer* renderer, );
MOSS_API void Moss_PresentSurface(Surface* surface);
MOSS_API void Moss_DestorySurface(Moss_Renderer* renderer, );

MOSS_API Surface* Moss_CreateSurfaceRectTexture(Moss_Renderer* renderer, );
MOSS_API void Moss_PresentSurfaceRectTexture(Surface* surface);
MOSS_API void Moss_DestorySurfaceRectTexture(Moss_Renderer* renderer, );

MOSS_API Surface* Moss_CreateSurfaceSquare(Moss_Renderer* renderer, );
MOSS_API Surface* Moss_CreateSurfaceCircle(Moss_Renderer* renderer, );

MOSS_API Mesh* Moss_CreateMesh(Moss_Renderer* renderer, );
MOSS_API void Moss_PresentMesh(Mesh* mesh);
MOSS_API void Moss_DestoryMesh();
MOSS_API Model* Moss_CreateModel(Moss_Renderer* renderer, );
MOSS_API void Moss_PresentMesh(Model* model);
MOSS_API void Moss_DestoryMesh();


// Utils
MOSS_API void Moss_CreateLine2D();
MOSS_API void Moss_CreateLine3D();
MOSS_API void Moss_CreatePoint2D();
MOSS_API void Moss_CreatePoint3D();
MOSS_API void Moss_CreateCricle2D();
MOSS_API void Moss_CreateCricle3D();
MOSS_API void Moss_CreateTriangle2D();
MOSS_API void Moss_CreateTriangle3D();
MOSS_API void Moss_CreateBox2D();
MOSS_API void Moss_CreateBox3D();
MOSS_API void Moss_CreateCylinder2D();
MOSS_API void Moss_CreateCylinder3D();
MOSS_API void Moss_CreateCapsule2D();
MOSS_API void Moss_CreateCapsule3D();
MOSS_API void Moss_CreateRay2D();
MOSS_API void Moss_CreateRay3D();

// Graphics Specific
#ifdef MOSS_GRAPHICS_OPENGL
#endif

#ifdef MOSS_GRAPHICS_VULKAN
MOSS_API VkDevice						GetDevice(Moss_Renderer* renderer);
MOSS_API VkDescriptorPool				GetDescriptorPool(Moss_Renderer* renderer);
MOSS_API VkDescriptorSetLayout			GetDescriptorSetLayoutTexture(Moss_Renderer* renderer);
MOSS_API VkSampler						GetTextureSamplerRepeat(Moss_Renderer* renderer);
MOSS_API VkSampler						GetTextureSamplerShadow(Moss_Renderer* renderer);
MOSS_API VkRenderPass					GetRenderPassShadow(Moss_Renderer* renderer);
MOSS_API VkRenderPass					GetRenderPass(Moss_Renderer* renderer);
MOSS_API VkPipelineLayout				GetPipelineLayout(Moss_Renderer* renderer);
MOSS_API VkCommandBuffer				GetCommandBuffer(Moss_Renderer* renderer);
MOSS_API VkCommandBuffer				StartTempCommandBuffer(Moss_Renderer* renderer);
MOSS_API void							EndTempCommandBuffer(Moss_Renderer* renderer, VkCommandBuffer inCommandBuffer);
MOSS_API void							AllocateMemory(Moss_Renderer* renderer, VkDeviceSize inSize, uint32 inMemoryTypeBits, VkMemoryPropertyFlags inProperties, VkDeviceMemory &outMemory);
MOSS_API void							FreeMemory(Moss_Renderer* renderer, VkDeviceMemory inMemory, VkDeviceSize inSize);
MOSS_API void							CreateBuffer(Moss_Renderer* renderer, VkDeviceSize inSize, VkBufferUsageFlags inUsage, VkMemoryPropertyFlags inProperties, BufferVK &outBuffer);
MOSS_API void							CopyBuffer(Moss_Renderer* renderer, VkBuffer inSrc, VkBuffer inDst, VkDeviceSize inSize);
MOSS_API void							CreateDeviceLocalBuffer(Moss_Renderer* renderer, const void *inData, VkDeviceSize inSize, VkBufferUsageFlags inUsage, BufferVK &outBuffer);
MOSS_API void							FreeBuffer(Moss_Renderer* renderer, BufferVK &ioBuffer);
MOSS_API unique_ptr<ConstantBufferVK>	CreateConstantBuffer(Moss_Renderer* renderer, VkDeviceSize inBufferSize);
MOSS_API void							CreateImage(Moss_Renderer* renderer, uint32 inWidth, uint32 inHeight, VkFormat inFormat, VkImageTiling inTiling, VkImageUsageFlags inUsage, VkMemoryPropertyFlags inProperties, VkImage &outImage, VkDeviceMemory &outMemory);
MOSS_API void							DestroyImage(Moss_Renderer* renderer, VkImage inImage, VkDeviceMemory inMemory);
MOSS_API VkImageView					CreateImageView(Moss_Renderer* renderer, VkImage inImage, VkFormat inFormat, VkImageAspectFlags inAspectFlags);
MOSS_API VkFormat						FindDepthFormat(Moss_Renderer* renderer);
#endif

#ifdef MOSS_GRAPHICS_DIRECTX
MOSS_API ID3D12Device*					GetDevice(Moss_Renderer* renderer);
MOSS_API ID3D12RootSignature*			GetRootSignature(Moss_Renderer* renderer);
MOSS_API ID3D12GraphicsCommandList*		GetCommandList(Moss_Renderer* renderer);
MOSS_API CommandQueueDX12&				GetUploadQueue(Moss_Renderer* renderer);
MOSS_API DescriptorHeapDX12&			GetDSVHeap(Moss_Renderer* renderer);
MOSS_API DescriptorHeapDX12&			GetSRVHeap(Moss_Renderer* renderer);
#endif

#ifdef MOSS_GRAPHICS_METAL
MOSS_API MTKView*						GetView(Moss_Renderer* renderer);
MOSS_API id<MTLDevice>					GetDevice(Moss_Renderer* renderer);
MOSS_API id<MTLRenderCommandEncoder>	GetRenderEncoder(Moss_Renderer* renderer);
#endif

#ifdef __cplusplus
}
#endif


#endif // MOSS_RENDERER_H




