//                        MIT License
//
//                  Copyright (c) 2026 Toby
//
#ifndef MOSS_OPENXR_H
#define MOSS_OPENXR_H

#include <Moss/Moss_stdinc.h>
#include <Moss/Moss_Renderer.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MossXR_Context MossXR_Context;
typedef struct MossXR_Session MossXR_Session;
typedef struct MossXR_Swapchain MossXR_Swapchain;
typedef struct MossXR_Space MossXR_Space;
typedef struct MossXR_Action MossXR_Action;
typedef struct MossXR_ActionSet MossXR_ActionSet;
typedef struct MossXR_Layer MossXR_Layer;
typedef struct MossXR_Anchor MossXR_Anchor;
typedef struct MossXR_Origin MossXR_Origin;
typedef struct MossXR_HandModifier MossXR_HandModifier;
typedef struct MossXR_BodyModifier MossXR_BodyModifier;
typedef struct MossXR_FaceModifier MossXR_FaceModifier;

typedef int64 MossXR_Time;

typedef enum MossXR_SessionState {
    MOSS_XR_SESSION_UNKNOWN,
    MOSS_XR_SESSION_READY,
    MOSS_XR_SESSION_SYNCHRONIZED,
    MOSS_XR_SESSION_VISIBLE,
    MOSS_XR_SESSION_FOCUSED,
    MOSS_XR_SESSION_STOPPING,
    MOSS_XR_SESSION_EXITING,
    MOSS_XR_SESSION_LOSS_PENDING
} MossXR_SessionState;

typedef enum MossXR_ActionType {
    MOSS_XR_ACTION_BOOLEAN,
    MOSS_XR_ACTION_FLOAT,
    MOSS_XR_ACTION_VEC2,
    MOSS_XR_ACTION_POSE,
    MOSS_XR_ACTION_HAPTIC
} MossXR_ActionType;

typedef enum MossXR_ViewType {
    MOSS_XR_VIEW_MONO,
    MOSS_XR_VIEW_STEREO
} MossXR_ViewType;

typedef enum MossXR_Handedness {
    MOSS_XR_HAND_LEFT,
    MOSS_XR_HAND_RIGHT
} MossXR_Handedness;

typedef enum MossXR_ImageLayout {
    MOSS_XR_IMAGE_COLOR_ATTACHMENT,
    MOSS_XR_IMAGE_SHADER_READ
} MossXR_ImageLayout;

typedef enum MossXR_EventType {
    MOSS_XR_EVENT_SESSION_STATE_CHANGED,
    MOSS_XR_EVENT_USER_PRESENCE_CHANGED,
    MOSS_XR_EVENT_REFERENCE_SPACE_CHANGED,
    MOSS_XR_EVENT_INSTANCE_LOSS_PENDING,
    MOSS_XR_EVENT_INTERACTION_PROFILE_CHANGED,
    MOSS_XR_EVENT_VISIBILITY_CHANGED
} MossXR_EventType;

typedef enum MossXR_BodyJoint {
    MOSS_XR_BODY_ROOT,
    MOSS_XR_BODY_SPINE,
    MOSS_XR_BODY_CHEST,
    MOSS_XR_BODY_NECK,
    MOSS_XR_BODY_HEAD,
    MOSS_XR_BODY_LEFT_SHOULDER,
    MOSS_XR_BODY_LEFT_ELBOW,
    MOSS_XR_BODY_LEFT_HAND,
    MOSS_XR_BODY_RIGHT_SHOULDER,
    MOSS_XR_BODY_RIGHT_ELBOW,
    MOSS_XR_BODY_RIGHT_HAND,
    MOSS_XR_BODY_LEFT_HIP,
    MOSS_XR_BODY_LEFT_KNEE,
    MOSS_XR_BODY_LEFT_FOOT,
    MOSS_XR_BODY_RIGHT_HIP,
    MOSS_XR_BODY_RIGHT_KNEE,
    MOSS_XR_BODY_RIGHT_FOOT,
    MOSS_XR_BODY_JOINT_COUNT
} MossXR_BodyJoint;

typedef enum MossXR_HandJoint {
    MOSS_XR_HAND_WRIST,
    MOSS_XR_HAND_THUMB_METACARPAL,
    MOSS_XR_HAND_THUMB_PROXIMAL,
    MOSS_XR_HAND_THUMB_DISTAL,
    MOSS_XR_HAND_THUMB_TIP,
    MOSS_XR_HAND_INDEX_METACARPAL,
    MOSS_XR_HAND_INDEX_PROXIMAL,
    MOSS_XR_HAND_INDEX_INTERMEDIATE,
    MOSS_XR_HAND_INDEX_DISTAL,
    MOSS_XR_HAND_INDEX_TIP,
    MOSS_XR_HAND_MIDDLE_METACARPAL,
    MOSS_XR_HAND_MIDDLE_PROXIMAL,
    MOSS_XR_HAND_MIDDLE_INTERMEDIATE,
    MOSS_XR_HAND_MIDDLE_DISTAL,
    MOSS_XR_HAND_MIDDLE_TIP,
    MOSS_XR_HAND_RING_METACARPAL,
    MOSS_XR_HAND_RING_PROXIMAL,
    MOSS_XR_HAND_RING_INTERMEDIATE,
    MOSS_XR_HAND_RING_DISTAL,
    MOSS_XR_HAND_RING_TIP,
    MOSS_XR_HAND_PINKY_METACARPAL,
    MOSS_XR_HAND_PINKY_PROXIMAL,
    MOSS_XR_HAND_PINKY_INTERMEDIATE,
    MOSS_XR_HAND_PINKY_DISTAL,
    MOSS_XR_HAND_PINKY_TIP,
    MOSS_XR_HAND_JOINT_COUNT
} MossXR_HandJoint;

typedef enum MossXR_RendererBackend {
    MOSS_XR_RENDERER_UNKNOWN,
    MOSS_XR_RENDERER_OPENGL,
    MOSS_XR_RENDERER_VULKAN,
    MOSS_XR_RENDERER_DIRECTX12,
    MOSS_XR_RENDERER_METAL
} MossXR_RendererBackend;

typedef struct MossXR_Pose {
    Vec3 position;
    Quat orientation;
} MossXR_Pose;

typedef struct MossXR_Fov {
    float left;
    float right;
    float up;
    float down;
} MossXR_Fov;

typedef struct MossXR_View {
    MossXR_Pose pose;
    MossXR_Fov fov;
    Mat44 view;
    Mat44 projection;
} MossXR_View;

typedef struct MossXR_Capabilities {
    uint32 view_count;
    MossXR_ViewType view_type;
    bool hand_tracking;
    bool eye_tracking;
    bool body_tracking;
    bool face_tracking;
    bool passthrough;
    bool anchors;
    bool depth_layers;
} MossXR_Capabilities;

typedef struct MossXR_InitInfo {
    MossXR_RendererBackend renderer;
    void* graphics_device;
    void* graphics_context;
} MossXR_InitInfo;

MOSS_API bool Moss_XR_Initialize(const MossXR_InitInfo* info);
MOSS_API void Moss_XR_Shutdown(void);
MOSS_API MossXR_Session* Moss_XR_CreateSession(void);
MOSS_API void Moss_XR_DestroySession(MossXR_Session* session);
MOSS_API MossXR_SessionState Moss_XR_GetSessionState(MossXR_Session* session);
MOSS_API bool Moss_XR_BeginFrame(MossXR_Session* session);
MOSS_API void Moss_XR_EndFrame(MossXR_Session* session);
MOSS_API MossXR_Time Moss_XR_GetPredictedDisplayTime(MossXR_Session* session);
MOSS_API float Moss_XR_GetDeltaSeconds(void);
MOSS_API uint32 Moss_XR_GetViewCount(MossXR_Session* session);
MOSS_API bool Moss_XR_GetView(MossXR_Session* session, uint32 index, MossXR_View* out_view);

MOSS_API MossXR_Swapchain* Moss_XR_CreateSwapchain(MossXR_Session* session, uint32 width, uint32 height, Moss_TextureFormat format);
MOSS_API void Moss_XR_DestroySwapchain(MossXR_Swapchain* swapchain);
MOSS_API void* Moss_XR_AcquireSwapchainImage(MossXR_Swapchain* swapchain, uint32* out_image_index);
MOSS_API void Moss_XR_ReleaseSwapchainImage(MossXR_Swapchain* swapchain, uint32 image_index);

MOSS_API MossXR_ActionSet* Moss_XR_CreateActionSet(const char* name);
MOSS_API void Moss_XR_DestroyActionSet(MossXR_ActionSet* set);
MOSS_API MossXR_Action* Moss_XR_CreateAction(MossXR_ActionSet* set, const char* name, MossXR_ActionType type);
MOSS_API void Moss_XR_DestroyAction(MossXR_Action* action);
MOSS_API void Moss_XR_AttachActionSet(MossXR_Session* session, MossXR_ActionSet* set);
MOSS_API void Moss_XR_SyncActions(MossXR_Session* session);
MOSS_API bool Moss_XR_GetActionBoolean(MossXR_Action* action);
MOSS_API float Moss_XR_GetActionFloat(MossXR_Action* action);
MOSS_API bool Moss_XR_GetActionPose(MossXR_Action* action, MossXR_Pose* out_pose);
MOSS_API void Moss_XR_PlayHaptic(MossXR_Action* action, float amplitude, float duration_seconds);
MOSS_API void Moss_XR_StopHaptic(MossXR_Action* action);

MOSS_API MossXR_HandModifier* Moss_XR_CreateHand(void);
MOSS_API bool Moss_XR_GetHandJointPose(MossXR_HandModifier* hand, MossXR_HandJoint joint, MossXR_Pose* out_pose);
MOSS_API void Moss_XR_DestroyHand(MossXR_HandModifier* hand);
MOSS_API bool Moss_XR_GetHandPose(MossXR_HandModifier* hand, MossXR_Pose* out_pose);
MOSS_API MossXR_BodyModifier* Moss_XR_CreateBody(void);
MOSS_API bool Moss_XR_GetBodyJointPose(MossXR_BodyModifier* body, MossXR_BodyJoint joint, MossXR_Pose* out_pose);
MOSS_API void Moss_XR_DestroyBody(MossXR_BodyModifier* body);
MOSS_API MossXR_FaceModifier* Moss_XR_CreateFace(void);
MOSS_API void Moss_XR_DestroyFace(MossXR_FaceModifier* face);
MOSS_API void Moss_XR_UpdateBodyTracking(MossXR_Session* session);
MOSS_API void Moss_XR_UpdateHandTracking(MossXR_Session* session);

MOSS_API MossXR_Anchor* Moss_XR_CreateAnchor(const MossXR_Pose* pose);
MOSS_API void Moss_XR_DestroyAnchor(MossXR_Anchor* anchor);
MOSS_API bool Moss_XR_LocateAnchor(MossXR_Anchor* anchor, MossXR_Time time, MossXR_Pose* out_pose);
MOSS_API MossXR_Layer* Moss_XR_CreateProjectionLayer(MossXR_Swapchain* swapchain);
MOSS_API MossXR_Layer* Moss_XR_CreateQuadLayer(MossXR_Swapchain* swapchain, const MossXR_Pose* pose, Vec2 size);
MOSS_API void Moss_XR_DestroyLayer(MossXR_Layer* layer);
MOSS_API void Moss_XR_SubmitLayers(MossXR_Session* session, uint32 layer_count, MossXR_Layer** layers);

MOSS_API bool Moss_XR_EnablePassthrough(bool enable);
MOSS_API bool Moss_XR_EnableFoveatedRendering(bool enable);
MOSS_API const MossXR_Capabilities* Moss_XR_GetCapabilities(void);
MOSS_API const char* Moss_XR_GetBackendName(void);
MOSS_API uint32 Moss_XR_GetBackendVersion(void);
MOSS_API void Moss_XR_BeginDebugLabel(const char* label);
MOSS_API void Moss_XR_EndDebugLabel(void);

#ifdef __cplusplus
}
#endif

#endif // MOSS_OPENXR_H
