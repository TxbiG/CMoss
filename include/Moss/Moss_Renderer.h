//                        MIT License
//
//                  Copyright (c) 2026 Toby
//
#ifndef MOSS_RENDERER_H
#define MOSS_RENDERER_H

#include <Moss/Moss_stdinc.h>
#include <Moss/Moss_Platform.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum Moss_TextureFormat {
    MOSS_TEXTURE_FORMAT_R8,
    MOSS_TEXTURE_FORMAT_RG8,
    MOSS_TEXTURE_FORMAT_RGB8,
    MOSS_TEXTURE_FORMAT_RGBA8,
    MOSS_TEXTURE_FORMAT_R8_SNORM,
    MOSS_TEXTURE_FORMAT_RG8_SNORM,
    MOSS_TEXTURE_FORMAT_RGB8_SNORM,
    MOSS_TEXTURE_FORMAT_RGBA8_SNORM,
    MOSS_TEXTURE_FORMAT_R16F,
    MOSS_TEXTURE_FORMAT_RG16F,
    MOSS_TEXTURE_FORMAT_RGB16F,
    MOSS_TEXTURE_FORMAT_RGBA16F,
    MOSS_TEXTURE_FORMAT_R32F,
    MOSS_TEXTURE_FORMAT_RG32F,
    MOSS_TEXTURE_FORMAT_RGB32F,
    MOSS_TEXTURE_FORMAT_RGBA32F,
    MOSS_TEXTURE_FORMAT_R8UI,
    MOSS_TEXTURE_FORMAT_RG8UI,
    MOSS_TEXTURE_FORMAT_RGBA8UI,
    MOSS_TEXTURE_FORMAT_R16UI,
    MOSS_TEXTURE_FORMAT_RG16UI,
    MOSS_TEXTURE_FORMAT_RGBA16UI,
    MOSS_TEXTURE_FORMAT_R32UI,
    MOSS_TEXTURE_FORMAT_RG32UI,
    MOSS_TEXTURE_FORMAT_RGBA32UI,
    MOSS_TEXTURE_FORMAT_DEPTH16,
    MOSS_TEXTURE_FORMAT_DEPTH24,
    MOSS_TEXTURE_FORMAT_DEPTH32F,
    MOSS_TEXTURE_FORMAT_DEPTH24_STENCIL8,
    MOSS_TEXTURE_FORMAT_DEPTH32F_STENCIL8,
    MOSS_TEXTURE_FORMAT_DXT1,
    MOSS_TEXTURE_FORMAT_DXT3,
    MOSS_TEXTURE_FORMAT_DXT5,
    MOSS_TEXTURE_FORMAT_BC4,
    MOSS_TEXTURE_FORMAT_BC5,
    MOSS_TEXTURE_FORMAT_BC6H,
    MOSS_TEXTURE_FORMAT_BC7,
    MOSS_TEXTURE_FORMAT_SRGB8,
    MOSS_TEXTURE_FORMAT_SRGBA8
} Moss_TextureFormat;

typedef enum Moss_InputLayoutSemantic {
    MOSS_INPUT_POSITION,
    MOSS_INPUT_COLOR,
    MOSS_INPUT_NORMAL,
    MOSS_INPUT_TEXCOORD,
    MOSS_INPUT_INSTANCE_COLOR,
    MOSS_INPUT_INSTANCE_TRANSFORM,
    MOSS_INPUT_INSTANCE_INV_TRANSFORM
} Moss_InputLayoutSemantic;

typedef enum Moss_DrawPass { MOSS_DRAW_PASS_SHADOW, MOSS_DRAW_PASS_NORMAL, MOSS_DRAW_PASS_LIGHTING, MOSS_DRAW_PASS_TRANSPARENT } Moss_DrawPass;
typedef enum Moss_Topology { MOSS_TOPOLOGY_TRIANGLE, MOSS_TOPOLOGY_LINE, MOSS_TOPOLOGY_POINT } Moss_Topology;
typedef enum Moss_FillMode { MOSS_FILL_SOLID, MOSS_FILL_WIREFRAME } Moss_FillMode;
typedef enum Moss_DepthTest { MOSS_DEPTH_TEST_OFF, MOSS_DEPTH_TEST_ON } Moss_DepthTest;
typedef enum Moss_BlendMode { MOSS_BLEND_OPAQUE, MOSS_BLEND_ALPHA, MOSS_BLEND_ADDITIVE } Moss_BlendMode;
typedef enum Moss_CullMode { MOSS_CULL_NONE, MOSS_CULL_BACKFACE, MOSS_CULL_FRONTFACE } Moss_CullMode;

typedef struct Moss_Renderer Moss_Renderer;
typedef struct Moss_Shader Moss_Shader;
typedef struct Moss_PixelShader Moss_PixelShader;
typedef Moss_PixelShader Moss_PostProcessing;
typedef struct Moss_VertexShader Moss_VertexShader;
typedef struct Moss_ComputeShader Moss_ComputeShader;
typedef struct Moss_GeometryShader Moss_GeometryShader;
typedef struct Moss_TessellationControlShader Moss_TessellationControlShader;
typedef struct Moss_TessellationEvaluationShader Moss_TessellationEvaluationShader;
typedef struct Moss_PipelineState Moss_PipelineState;
typedef struct Moss_FogVolume Moss_FogVolume;
typedef struct Moss_SubViewport Moss_SubViewport;
typedef struct Moss_Surface Moss_Surface;
typedef struct Moss_Mesh Moss_Mesh;
typedef struct Moss_Model Moss_Model;
typedef struct Moss_SkyBox Moss_SkyBox;
typedef struct Moss_Font Moss_Font;

typedef struct Moss_Camera2D {
    Float2 position;
    Float2 offset;
    float zoom;
    float rotation;
} Moss_Camera2D;

typedef struct Moss_Camera3D {
    Float3 position;
    Float3 up;
    Float3 target;
    float speed;
    float sensitivity;
    float fov;
    float aspect_ratio;
    float near_plane;
    float far_plane;
} Moss_Camera3D;

typedef struct Moss_Material2D {
    Float3 albedo;
    Texture* albedo_map;
    Texture* normal_map;
} Moss_Material2D;

typedef struct Moss_Material3D {
    Float3 albedo;
    float metallic;
    float roughness;
    float ao;
    float specular;
    Texture* albedo_map;
    Texture* normal_map;
    Texture* roughness_map;
    Texture* metallic_map;
    Texture* ao_map;
} Moss_Material3D;

typedef struct Moss_Frustum2D { AABB2 bounds; } Moss_Frustum2D;
typedef struct Moss_Frustum3D { Plane planes[6]; } Moss_Frustum3D;

typedef struct Moss_TextureLight2D { float intensity, rotation; Texture* texture; Float2 position; Color color; } Moss_TextureLight2D;
typedef struct Moss_DirectionalLight2D { float intensity, rotation; Color color; } Moss_DirectionalLight2D;
typedef struct Moss_PointLight2D { float intensity, rotation, radius; Float2 position; Color color; } Moss_PointLight2D;
typedef struct Moss_TextureLight3D { float intensity; Texture* texture; Float3 position, rotation; Color color; } Moss_TextureLight3D;
typedef struct Moss_DirectionalLight3D { float intensity; Float3 rotation; Color color; } Moss_DirectionalLight3D;
typedef struct Moss_SpotLight3D { float intensity, radius, angle, penumbra; Float3 position, rotation; Color color; } Moss_SpotLight3D;
typedef struct Moss_OmniLight3D { float intensity, radius; Float3 position; Color color; } Moss_OmniLight3D;

typedef struct Moss_Decal { Texture* albedo; Texture* normal; Texture* orm; Texture* emission; Color color; float emission_energy; float blend_factor; Mat44 model; uint32 filter; } Moss_Decal;
typedef struct Moss_Sprite2D { Texture* texture; Moss_Surface* surface; } Moss_Sprite2D;
typedef struct Moss_Sprite3D { Texture* texture; Moss_Mesh* mesh; } Moss_Sprite3D;

typedef struct Moss_InputDescription {
    Moss_InputLayoutSemantic semantic;
    uint32 offset;
    uint32 stride;
} Moss_InputDescription;

MOSS_API Moss_Renderer* Moss_CreateRenderer(Moss_Window* window, const Color* bg_color, int virtual_res_width, int virtual_res_height);
MOSS_API void Moss_RendererBeginFrame(Moss_Renderer* renderer);
MOSS_API void Moss_RendererPresentFrame(Moss_Renderer* renderer);
MOSS_API void Moss_RendererSetBackground(Moss_Renderer* renderer, Color color);
MOSS_API void Moss_TerminateRenderer(Moss_Renderer* renderer);

MOSS_API Moss_Camera2D* Moss_CreateCamera2D(Moss_Renderer* renderer, Float2 position, Float2 offset);
MOSS_API void Moss_DestroyCamera2D(Moss_Camera2D* camera);
MOSS_API Moss_Camera3D* Moss_CreateCamera3D(Moss_Renderer* renderer, Float3 position, Float3 target);
MOSS_API void Moss_DestroyCamera3D(Moss_Camera3D* camera);

MOSS_API Moss_PixelShader* Moss_CreatePixelShader(void);
MOSS_API Moss_VertexShader* Moss_CreateVertexShader(void);
MOSS_API Moss_ComputeShader* Moss_CreateComputeShader(void);
MOSS_API void Moss_DestroyShader(Moss_Shader* shader);

MOSS_API Moss_PipelineState* Moss_CreatePipelineState(Moss_Renderer* renderer, Moss_VertexShader* vertex, const Moss_InputDescription* input_description, uint32 input_description_count, const Moss_PixelShader* pixel, Moss_DrawPass draw_pass, Moss_FillMode fill_mode, Moss_Topology topology, Moss_DepthTest depth_test, Moss_BlendMode blend_mode, Moss_CullMode cull_mode);
MOSS_API void Moss_DestroyPipelineState(Moss_Renderer* renderer, Moss_PipelineState* pipeline_state);

MOSS_API Texture* Moss_CreateTexture(Moss_Renderer* renderer, int width, int height, Moss_TextureFormat format, const void* pixels);
MOSS_API void Moss_DestroyTexture(Moss_Renderer* renderer, Texture* texture);

MOSS_API Moss_Surface* Moss_CreateSurface(Moss_Renderer* renderer, int width, int height);
MOSS_API void Moss_PresentSurface(Moss_Surface* surface);
MOSS_API void Moss_DestroySurface(Moss_Renderer* renderer, Moss_Surface* surface);
MOSS_API Moss_Surface* Moss_CreateSurfaceRectTexture(Moss_Renderer* renderer, Texture* texture, Rect rect);
MOSS_API void Moss_PresentSurfaceRectTexture(Moss_Surface* surface);
MOSS_API void Moss_DestroySurfaceRectTexture(Moss_Renderer* renderer, Moss_Surface* surface);
MOSS_API Moss_Surface* Moss_CreateSurfaceSquare(Moss_Renderer* renderer, float size);
MOSS_API Moss_Surface* Moss_CreateSurfaceCircle(Moss_Renderer* renderer, float radius, uint32 segments);

MOSS_API Moss_Mesh* Moss_CreateMesh(Moss_Renderer* renderer, const void* vertices, uint32 vertex_count, const uint32* indices, uint32 index_count);
MOSS_API void Moss_PresentMesh(Moss_Mesh* mesh);
MOSS_API void Moss_DestroyMesh(Moss_Mesh* mesh);
MOSS_API Moss_Model* Moss_CreateModel(Moss_Renderer* renderer, const char* path);
MOSS_API void Moss_PresentModel(Moss_Model* model);
MOSS_API void Moss_DestroyModel(Moss_Model* model);

MOSS_API void Moss_CreateLine2D(Float2 a, Float2 b, Color color);
MOSS_API void Moss_CreateLine3D(Float3 a, Float3 b, Color color);
MOSS_API void Moss_CreatePoint2D(Float2 point, Color color);
MOSS_API void Moss_CreatePoint3D(Float3 point, Color color);
MOSS_API void Moss_CreateCircle2D(Float2 center, float radius, Color color);
MOSS_API void Moss_CreateCircle3D(Float3 center, float radius, Color color);
MOSS_API void Moss_CreateTriangle2D(Float2 a, Float2 b, Float2 c, Color color);
MOSS_API void Moss_CreateTriangle3D(Float3 a, Float3 b, Float3 c, Color color);
MOSS_API void Moss_CreateBox2D(Rect rect, Color color);
MOSS_API void Moss_CreateBox3D(Float3 center, Float3 extents, Color color);
MOSS_API void Moss_CreateCylinder3D(Float3 center, float radius, float height, Color color);
MOSS_API void Moss_CreateCapsule3D(Float3 a, Float3 b, float radius, Color color);
MOSS_API void Moss_CreateRay2D(Float2 origin, Float2 direction, float length, Color color);
MOSS_API void Moss_CreateRay3D(Float3 origin, Float3 direction, float length, Color color);

#ifdef __cplusplus
}
#endif

#endif // MOSS_RENDERER_H
