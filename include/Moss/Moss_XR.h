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

/*!
 * @file Moss_XR.h
 * @brief Cross-platform XR (VR/AR/MR) interface built on OpenXR 1.1 for Moss Engine.
 *
 * The Moss XR module provides a unified and extensible interface for Virtual Reality (VR),
 * Augmented Reality (AR), and Mixed Reality (MR) applications using the OpenXR standard.
 *
 * ---
 *
 * ### Core Features:
 * - **OpenXR 1.1 Integration** — Cross-platform, vendor-neutral XR standard (Oculus, SteamVR, WMR, Vive, Pico, Varjo, etc).
 * - **Session Management** — Handles initialization, frame lifecycle, and synchronization between rendering and XR runtimes.
 * - **View Configuration** — Supports both stereo (VR) and mono (AR/MR) rendering pipelines.
 * - **Input System** — Abstracted hand/controller tracking via OpenXR actions and poses.
 * - **Haptic Feedback** — Vibration, impulse, and frequency-based feedback through OpenXR haptics layer.
 * - **Tracking System** — Full 6DOF head, hand, and body tracking with prediction and smoothing.
 * - **Compositor Integration** — Direct connection to Moss Renderer for eye texture management and projection matrices.
 * - **Multi-View Rendering** — Support for multi-pass, instanced, or single-pass stereo rendering (depending on GPU/driver capabilities).
 *
 * ---
 *
 * ### Supported XR Runtimes:
 * - Meta Quest / Oculus (via OpenXR)
 * - SteamVR (Vive, Index)
 * - Windows and Windows Mixed Reality
 * - Varjo XR
 * - Pico / Lynx / WaveVR
 * - Android XR devices (via OpenXR Loader)
 * - Linux
 *
 * ---
 *
 * ### Supported Renderers: OpenGL, Vulkan, DirectX
 *
 * ---
 *
 * ### Extended Moss Features:
 * - **XR Camera Integration**  
 *   - `CameraXR` synchronizes head pose and eye projections with the Moss rendering pipeline.
 *   - Automatic clipping and stereo culling support.
 *
 * - **Hand Tracking / Gesture API**  
 *   - Access joint transforms (e.g., palm, finger tips) through `Moss_XRGetHandJointPose()`.  
 *   - Custom gestures and interaction mapping for grabbing, pointing, UI input.  
 *
 * - **Eye Tracking & Foveated Rendering** *(optional)*  
 *   - Dynamic foveation using gaze direction.  
 *   - Adaptive resolution rendering for performance optimization.  
 *
 * - **Spatial Anchors & Scene Understanding** *(AR/MR)*  
 *   - World anchors for persistent spatial references.  
 *   - Mesh reconstruction and real-world collision surfaces for physics alignment.  
 *
 * ---
 *
 * ### Supported Extensions (if available):
 * - `XR_EXT_hand_tracking`
 * - `XR_EXT_eye_gaze_interaction`
 * - `XR_FB_foveation`
 * - `XR_VARJO_quad_views`
 * - `XR_EXT_local_floor`
 * - `XR_KHR_composition_layer_depth`
 *
 * ---
 *
 * ### Future Roadmap:
 * - Mixed Reality passthrough with real-time camera streaming.
 * - Vulkan-based OpenXR layer compositor.
 * - GPU-driven foveation and reprojection.
 * - Networked multi-user XR sessions (shared space).
 * - Haptic feedback synthesis via Moss_Haptics.
 *  
 * ---
 *
 * ### Design Goals:
 * - Fully modular and OpenXR-conformant.  
 * - Minimal runtime overhead — integrates directly with Moss’ job system and renderer.  
 * - Real-time, low-latency VR/AR interaction.  
 * - Plug-and-play with custom runtime layers and extensions (e.g. Varjo gaze, Meta passthrough).  
*/


/*
MOSS_XR_VENDOR_OCULUSTOUCH - OculusTouch
MOSS_XR_VENDOR_VALVEINDEX - ValveIndex
MOSS_XR_VENDOR_MSFIXEDREALITY - MicrosoftMixedReality
MOSS_XR_VENDOR_PICO - PICO VR
MOSS_XR_VENDOR_PIMAX - Pimax
MOSS_XR_VENDOR_SONY - Sony VR
MOSS_XR_VENDOR_Varjo - Varjo VR
*/

#ifndef MOSS_OPENXR_H
#define MOSS_OPENXR_H

#include <Moss/Moss_stdinc.h>
#include <Moss/Moss_Renderer.h>

typedef struct MossXR_Context   MossXR_Context;
typedef struct Moss_XRSession   Moss_XRSession;
typedef struct Moss_XRSwapchain Moss_XRSwapchain;
typedef struct Moss_XRAction    MossXR_Action;
typedef struct Moss_XRSpace     MossXR_Space;

typedef void* Moss_XROrigin;
typedef struct Moss_XRAnchor Moss_XRAnchor;

typedef struct XRFaceModifier XRFaceModifier;           // Facial Modifier tracks facial expressions.
typedef struct XRBodyModifier XRBodyModifier;           // Body Modifier tracks body.
typedef struct XRHandModifier XRHandModifier;           // Hand Modifier tracks Hand movement.

typedef struct MossXR_ActionSet MossXR_ActionSet;
typedef struct MossXR_CompositionLayer MossXR_CompositionLayer;

typedef int64_t Moss_XRTime;

typedef enum MossXR_TextureFormat {
    MOSS_XR_FORMAT_RGBA8,
    MOSS_XR_FORMAT_RGBA16F,
    MOSS_XR_FORMAT_DEPTH24,
    MOSS_XR_FORMAT_DEPTH32F,
} MossXR_TextureFormat;

typedef enum XRBodyJoint {
    XR_BODY_ROOT,
    XR_BODY_SPINE,
    XR_BODY_CHEST,
    XR_BODY_NECK,
    XR_BODY_HEAD,
    XR_BODY_LEFT_SHOULDER,
    XR_BODY_LEFT_ELBOW,
    XR_BODY_LEFT_HAND,
    XR_BODY_RIGHT_SHOULDER,
    XR_BODY_RIGHT_ELBOW,
    XR_BODY_RIGHT_HAND,
    XR_BODY_LEFT_HIP,
    XR_BODY_LEFT_KNEE,
    XR_BODY_LEFT_FOOT,
    XR_BODY_RIGHT_HIP,
    XR_BODY_RIGHT_KNEE,
    XR_BODY_RIGHT_FOOT,
    XR_BODY_JOINT_COUNT
} XRBodyJoint;

typedef enum XRHandJoint {
    XR_HAND_WRIST,
    XR_HAND_THUMB_METACARPAL,
    XR_HAND_THUMB_PROXIMAL,
    XR_HAND_THUMB_DISTAL,
    XR_HAND_THUMB_TIP,
    XR_HAND_INDEX_METACARPAL,
    XR_HAND_INDEX_PROXIMAL,
    XR_HAND_INDEX_INTERMEDIATE,
    XR_HAND_INDEX_DISTAL,
    XR_HAND_INDEX_TIP,
    XR_HAND_MIDDLE_METACARPAL,
    XR_HAND_MIDDLE_PROXIMAL,
    XR_HAND_MIDDLE_INTERMEDIATE,
    XR_HAND_MIDDLE_DISTAL,
    XR_HAND_MIDDLE_TIP,
    XR_HAND_RING_METACARPAL,
    XR_HAND_RING_PROXIMAL,
    XR_HAND_RING_INTERMEDIATE,
    XR_HAND_RING_DISTAL,
    XR_HAND_RING_TIP,
    XR_HAND_PINKY_METACARPAL,
    XR_HAND_PINKY_PROXIMAL,
    XR_HAND_PINKY_INTERMEDIATE,
    XR_HAND_PINKY_DISTAL,
    XR_HAND_PINKY_TIP,
    XR_HAND_JOINT_COUNT
} XRHandJoint;

typedef enum Moss_XRSessionState { 
    MOSS_XR_SESSION_STATE_Unknown, 
    MOSS_XR_SESSION_STATE_Ready, 
    MOSS_XR_SESSION_STATE_Synchronized, 
    MOSS_XR_SESSION_STATE_Visible, 
    MOSS_XR_SESSION_STATE_Focused, 
    MOSS_XR_SESSION_STATE_Stopping, 
    MOSS_XR_SESSION_STATE_Exiting, 
    MOSS_XR_SESSION_STATE_LossPending 
} Moss_XRSessionState;

typedef enum Moss_XREventType {
    MOSS_XR_EVENT_SESSION_STATE_CHANGED,
    MOSS_XR_EVENT_USER_PRESENCE_CHANGED,
    MOSS_XR_EVENT_REFERENCE_SPACE_CHANGED,
    MOSS_XR_EVENT_INSTANCE_LOSS_PENDING,
};

typedef enum Moss_XRActionType {
    MOSS_XR_ACTION_BOOLEAN,
    MOSS_XR_ACTION_FLOAT,
    MOSS_XR_ACTION_VEC2,
    MOSS_XR_ACTION_POSE,
    MOSS_XR_ACTION_HAPTIC
};

typedef struct Moss_XRPose {
    Vec3 position;
    Quat orientation;
} Moss_XRPose;

typedef struct Moss_XRFov {
    float left, right, up, down;
} Moss_XRFov;

typedef struct Moss_XRCapabilities {
    uint32_t view_count;
    bool supports_stereo;
    bool supports_mono;
    bool supports_hand_tracking;
    bool supports_eye_tracking;
    bool supports_plane_detection;
    bool supports_passthrough;
    bool supports_depth_layers;
} Moss_XRCapabilities;

typedef struct Moss_XREvent {
    Moss_XREventType type;
    union {
        struct {
            Moss_XRSessionState state;
        } session;
    };
} Moss_XREvent;

typedef struct MossXR_HandState {
    bool isTracked;
    Moss_XRPose joints[25]; // e.g., 25 joints for hand
} MossXR_HandState;

typedef struct MossXR_ControllerState {
    bool isActive;
    bool buttons[16]; // generic buttons
    float triggers[2];
    Moss_XRPose gripPose;
    Moss_XRPose aimPose;
} MossXR_ControllerState;
struct Moss_XRBodyState { /* joints, pose, etc. */ };
typedef struct XRFaceState {
    bool isTracked;
    float blendShapes[64];   // 64 common facial blendshapes (can expand)
} XRFaceState;

typedef struct XRBodyState {
    bool isTracked;
    MossXR_Pose jointPoses[XR_BODY_JOINT_COUNT];
} XRBodyState;

typedef struct XRHandState {
    bool isTracked;
    MossXR_Pose jointPoses[XR_HAND_JOINT_COUNT];
} XRHandState;

struct Moss_XREyeGaze {
    bool isValid;
    Moss_XRPose gazePose;
};

typedef struct CameraXR {
    Moss_XRPose headPose;
    Moss_XRFov eyeFov[2];
    Matrix viewMatrix[2];
    Matrix projMatrix[2];
} CameraXR;

MOSS_API bool Moss_XR_Init(void);
MOSS_API void Moss_XR_Shutdown(void);

MOSS_API bool Moss_XR_CreateSession(void);
MOSS_API void Moss_XR_DestroySession(void);

MOSS_API const Moss_XRCapabilities* Moss_XR_GetCapabilities(void);
MOSS_API bool Moss_XR_PollEvents(MossXRContext* ctx);

MOSS_API bool Moss_XR_BeginFrame(void);
MOSS_API void Moss_XR_EndFrame(void);

MOSS_API uint32_t Moss_XR_GetViewCount(void);
MOSS_API void Moss_XR_GetViewPose(uint32_t viewIndex, Moss_XRPose* outPose);
MOSS_API void Moss_XR_GetViewFov(uint32_t viewIndex, Moss_XRFov* outFov);

MOSS_API Moss_XRAction* Moss_XR_CreateAction(const char* name, Moss_XRActionType type);

MOSS_API bool Moss_XR_GetActionBoolean(Moss_XRAction* action);
MOSS_API float Moss_XR_GetActionFloat(Moss_XRAction* action);
MOSS_API bool Moss_XR_GetActionPose(Moss_XRAction* action, Moss_XRPose* outPose);

MOSS_API void Moss_XR_PlayHaptic(Moss_XRAction* action, float amplitude, float durationSeconds);
MOSS_API void Moss_XR_StopHaptic(Moss_XRAction* action);
MOSS_API void Moss_XR_PlayHapticPattern(Moss_XRAction* action, const float* pattern, uint32_t sampleCount, float frequency);

MOSS_API uint32_t Moss_XR_GetSupportedTextureFormats(MossXR_TextureFormat* outFormats, uint32_t maxCount);

MOSS_API Moss_XRTime Moss_XR_GetPredictedDisplayTime(void);
MOSS_API float Moss_XR_GetFrameDeltaSeconds(void);



MOSS_API Moss_XRSwapchain* Moss_XR_CreateSwapchain(uint32_t width, uint32_t height, MossXR_TextureFormat format);
MOSS_API void Moss_XR_DestroySwapchain(Moss_XRSwapchain* swapchain);

MOSS_API void* Moss_XR_AcquireSwapchainImage(Moss_XRSwapchain* swapchain, uint32_t* outIndex);
MOSS_API void Moss_XR_ReleaseSwapchainImage(Moss_XRSwapchain* swapchain, uint32_t imageIndex);


MOSS_API Moss_XRSpace* Moss_XR_CreateReferenceSpace(Moss_XRSession* session, Moss_XRPose pose);
MOSS_API void Moss_XR_DestroyReferenceSpace(Moss_XRSpace* space);
MOSS_API bool Moss_XR_LocateSpace(Moss_XRSpace* space, Moss_XRTime time, Moss_XRPose* outPose);

MOSS_API bool Moss_XR_GetHandState(uint32_t handIndex, MossXR_HandState* outState);



MOSS_API bool Moss_XR_EnablePassthrough(bool enable);
MOSS_API bool Moss_XR_GetPassthroughTexture(MossXR_Swapchain** outSwapchain);


// Callbacks
MOSS_API bool Moss_XR_RegisterEventCallback(Moss_XREventType type, void(*callback)(Moss_XREvent*));
MOSS_API void Moss_XR_UnregisterEventCallback(Moss_XREventType type);



// Tools
/*! */
MOSS_API int Moss_OpenXRGetRequiredInstanceExtensions();
/*! */
MOSS_API const char** Moss_XRGetEnabledExtensions(uint32_t* outCount);
/*! */
MOSS_API bool Moss_IsXRExtensionSupported(const char* extensionName);
/*! */
MOSS_API const char* Moss_XR_GetBackendName(void);
/*! */
MOSS_API uint32_t Moss_XR_GetBackendVersion(void);

MOSS_API bool Moss_XR_GetControllerState(uint32_t controllerIndex, MossXR_ControllerState* outState);

MOSS_API MossXR_ActionSet* Moss_XR_CreateActionSet(const char* name);
MOSS_API void Moss_XR_DestroyActionSet(MossXR_ActionSet* actionSet);
MOSS_API void Moss_XR_AttachActionSet(Moss_XRSession* session, MossXR_ActionSet* actionSet);
MOSS_API void Moss_XR_SyncActions(Moss_XRSession* session);

MOSS_API MossXR_CompositionLayer* Moss_XR_CreateProjectionLayer(Moss_XRSwapchain* swapchain);
MOSS_API MossXR_CompositionLayer* Moss_XR_CreateQuadLayer(Moss_XRSwapchain* swapchain, Moss_XRPose pose, Vec2 size);
MOSS_API void Moss_XR_DestroyLayer(MossXR_CompositionLayer* layer);
MOSS_API void Moss_XR_SubmitLayers(uint32_t layerCount, MossXR_CompositionLayer** layers);


MOSS_API Moss_XRAnchor* Moss_XR_CreateAnchor(Moss_XRPose pose);
MOSS_API void Moss_XR_DestroyAnchor(Moss_XRAnchor* anchor);
MOSS_API bool Moss_XR_LocateAnchor(Moss_XRAnchor* anchor, Moss_XRTime time, Moss_XRPose* outPose);


MOSS_API bool Moss_XR_GetBodyState(uint32_t bodyIndex, Moss_XRBodyState* outState);
MOSS_API bool Moss_XR_GetFaceState(uint32_t faceIndex, Moss_XRFaceState* outState);


MOSS_API XRFaceModifier* XR_CreateFaceModifier(void);
MOSS_API void XR_DestroyFaceModifier(XRFaceModifier* face);
MOSS_API bool XR_UpdateFaceModifier(XRFaceModifier* face, Moss_XRTime predictedTime);
MOSS_API bool XR_GetFaceState(XRFaceModifier* face, XRFaceState* outState);

MOSS_API XRBodyModifier* XR_CreateBodyModifier(void);
MOSS_API void XR_DestroyBodyModifier(XRBodyModifier* body);
MOSS_API bool XR_UpdateBodyModifier(XRBodyModifier* body, Moss_XRTime predictedTime);
MOSS_API bool XR_GetBodyState(XRBodyModifier* body, XRBodyState* outState);

MOSS_API XRHandModifier* XR_CreateHandModifier(void);
MOSS_API void XR_DestroyHandModifier(XRHandModifier* hand);
MOSS_API bool XR_UpdateHandModifier(XRHandModifier* hand, Moss_XRTime predictedTime);
MOSS_API bool XR_GetHandState(XRHandModifier* hand, XRHandState* outState);

MOSS_API bool Moss_XR_GetEyeGaze(uint32_t eyeIndex, Moss_XREyeGaze* outGaze);
MOSS_API bool Moss_XR_EnableFoveatedRendering(bool enable);

// Utils
MOSS_API void Moss_XR_BeginDebugLabel(const char* label);
MOSS_API void Moss_XR_EndDebugLabel();
MOSS_API void Moss_XR_SetPerfLevel(uint32_t domain, uint32_t level);
MOSS_API Matrix Moss_XR_PoseToMatrix(Moss_XRPose pose);
MOSS_API Moss_XRPose Moss_XR_MatrixToPose(Matrix m);

#endif // MOSS_OPENXR_H