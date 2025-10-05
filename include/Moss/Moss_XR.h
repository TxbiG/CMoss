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
#ifndef MOSS_OPENVR_H
#define MOSS_OPENVR_H

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
 * ### Supported Renderers:
 * - OpenGL
 * - Vulkan
 * - DirectX
 *
 * ---
 *
 * ### Example Usage:
 * ```cpp
 * Moss_XRInit();
 *
 * XRSession* session = Moss_CreateXRSession({
 *     .enableHandTracking = true,
 *     .enableEyeTracking  = false,
 *     .preferredRefreshRate = 90.0f
 * });
 *
 * while (Moss_XRIsRunning(session)) {
 *     Moss_XRBeginFrame(session);
 *     Moss_RenderSceneXR(renderer, session);
 *     Moss_XREndFrame(session);
 * }
 *
 * Moss_XRTerminate(session);
 * ```
 *
 * ---
 *
 * ### Extended Moss Features:
 * - **XR Camera Integration**  
 *   - `CameraXR` class synchronizes head pose and eye projections with the Moss rendering pipeline.
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
 * ### Integration Points:
 * - **Renderer:**  
 *   - Each XR eye has its own framebuffer.  
 *   - Moss_Renderer handles projection/view updates per eye.  
 *
 * - **Audio:**  
 *   - Moss_AudioListener3D automatically follows XR head position.  
 *   - Optional HRTF spatialization for realistic sound in XR.  
 *
 * - **Physics:**  
 *   - Controller poses synchronize with physics rigid bodies (grab, throw, collide).  
 *   - Supports dynamic object interaction with Moss_Physics.  
 *
 * - **Input:**  
 *   - Unified input mapping for XR controllers, mouse/keyboard, and gamepads.  
 *   - XR-specific bindings (grip, trigger, thumbstick, menu).  
 *
 * ---
 *
 * ### Design Goals:
 * - Fully modular and OpenXR-conformant.  
 * - Minimal runtime overhead — integrates directly with Moss’ job system and renderer.  
 * - Real-time, low-latency VR/AR interaction.  
 * - Plug-and-play with custom runtime layers and extensions (e.g., Varjo gaze, Meta passthrough).  
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
*/

#ifdef __cplusplus
extern "C" {
#endif

#include <Moss/Moss_stdinc.h>
#include <Moss/Moss_Platform.h>

//#if (defined(MOSS_USE_OPENXR) && defined(MOSS_PLATFORM_WINDOWS) || defined(MOSS_PLATFORM_LINUX) || defined(MOSS_PLATFORM_ANDROID))

#include <openxr/openxr.h>
#include <openxr/openxr_platform.h>


enum class ActionType : uint8 { Boolean, Float, Vector2f, Pose };
enum class InteractionProfile : uint8 { OculusTouch, ValveIndex, MicrosoftMixedReality, PICO, Pimax, Sony, Vive, Varjo, Unknown };  // Interaction profiles (add more as needed)
enum class SessionState : uint8 { Unknown, Ready, Synchronized, Visible, Focused, Stopping, Exiting, LossPending }; // XR session states (mirroring OpenXR states for convenience)

struct InputAction { XrAction action; ActionType type; std::string name;
    // State caches (simple)
    bool boolState = false;
    float floatState = 0.f;
    XrVector2f vector2fState{};
    XrPosef poseState{};
};

struct ActionSet {
    XrActionSet actionSet;
    std::string name;
    std::unordered_map<std::string, InputAction> actions;
};

// Controller state (basic buttons, triggers, thumbsticks)
struct ControllerState {
    bool isActive = false;
    bool buttonA = false;
    bool buttonB = false;
    float trigger = 0.f;
    XrVector2f thumbstick = {0.f, 0.f};
    XrPosef gripPose{};
    XrPosef aimPose{};
};

// Hand tracking state
struct HandState {
    bool isTracked = false;
    XrHandJointLocationEXT joints[XR_HAND_JOINT_COUNT_EXT];
};

// Eye gaze state
struct EyeGazeState {
    bool isValid = false;
    XrVector3f gazeDirection{};
    XrVector3f gazeOrigin{};
};

typedef struct XRAction {
    XrAction action_handle;
    // Bindings, type info, state caching
} XRAction;

typedef struct XRActionSet {
    XrActionSet action_set_handle;
    // Actions contained, state info, etc.
} XRActionSet;

typedef struct XRActionStateBoolean {
    XrAction action;
    bool current_state;
} XRActionStateBoolean;

typedef struct XRActionStateFloat {
    XrAction action;
    float current_state;
} XRActionStateFloat;

typedef struct XRActionStatePose {
    XrAction action;
    XrSpace pose_space;
    bool is_active;
} XRActionStatePose;

// Event data for session state changes and others (for event polling)
typedef struct XREventDataSessionStateChanged {
    XrStructureType type;
    void* next;
    XrSession session;
    XrSessionState state;
    XrTime time;
} XREventDataSessionStateChanged;

typedef enum XRInputEventData
{
    EVENT_LOST,
    INSTANCE_LOSS_PENDING,
    REFERENCE_SPACE_CHANGE_PENDING,
    SESSION_STATE_CHANGED
};
typedef struct XRHaptic {
    XrHapticActionInfo* hapticActionInfo;
    XrHapticBaseHeader* hapticFeedback;
    XrHapticVibration* hapticVibration;
} XRHaptic;

typedef struct XREvent {
    XrEventDataBaseHeader base;
    enum XRInputEventData type;     // One of your enum values
    // union of event-specific data if needed
} XREvent;

typedef void* XROrigin;
typedef struct XRAnchor XRAnchor;

typedef struct Moss_SwapChainImage Moss_SwapChainImage;


typedef struct XRController {
    XrPath profile_path;      // Interaction profile path
    XrActionSet action_set;   // Actions bound to this controller
    XrAction pose_action;     // Pose action
    XrAction trigger_action;  // Example analog trigger action
    // More buttons, axes, etc.

    // Current state cache (poses, buttons pressed)
    XrSpace controller_space;
    XrPosef current_pose;
    bool is_active;
} XRController;

typedef struct XRFaceModifier XRFaceModifier;           // Facial Modifier tracks facial expressions.
typedef struct XRBodyModifier XRBodyModifier;           // Body Modifier tracks body.
typedef struct XRHandModifier XRHandModifier;           // Hand Modifier tracks Hand movement.


struct [[nodiscard]] CameraXR;


void Moss_Init_XR();
void Moss_Terminate_XR();

void Moss_XRPollEvents();
void Moss_XRBeginFrame();
void Moss_XREndFrame();

void Moss_CreateSwapChainImage();
void Moss_RemoveSwapChainImage();


void Moss_Process_XRFrame(OpenXRContext* ctx);
void Moss_XR_PollEvents(OpenXRContext* ctx);

void GetInstanceProperties(OpenXRContext* ctx);

XrPath CreateXrPath(OpenXRContext* ctx, const char *path_string);

void GetInstanceProperties();
void GetSystemID();
void CreateDebugMessenger();

void DestroyDebugMessenger();

void CreateSession();

void DestroySession();

void PollSystemEvents();

void RenderCuboid(XrPosef pose, XrVector3f scale, XrVector3f color);
void CreateResources();
void DestroyResources();

void GetViewConfigurationViews()
void CreateSwapchains()
void DestroySwapchains()
void GetEnvironmentBlendModes()
void CreateReferenceSpace()
void DestroyReferenceSpace()

bool RenderLayer(RenderLayerInfo& renderLayerInfo);

void BeginFrame();
void RenderFrame();
void EndFrame();


/*          Face Modifier       */
/*          Body Modifier       */
/*          Hand Modifier       */
/*              Haptic          */

/*
XR_MAX_HAPTIC_AMPLITUDE_ENVELOPE_SAMPLES_FB
XR_MAX_HAPTIC_PCM_BUFFER_SIZE_FB
XR_MIN_HAPTIC_DURATION
*/
XRHaptic* Moss_CreateHapticFeedback() { }
Moss_RemoveHapticFeedback(XRHaptic* haptic) { }

Moss_StartHapticFeedback(XRHaptic* haptic) { xrApplyHapticFeedback(XrSession session, const XrHapticActionInfo* hapticActionInfo,const XrHapticBaseHeader* hapticFeedback); }
Moss_StopHapticFeedback(XRHaptic* haptic) { xrStopHapticFeedback(XrSession session, const XrHapticActionInfo* hapticActionInfo); }

/*          Callbacks           */


#ifdef __cplusplus
}
#endif

#endif // (defined(MOSS_USE_OPENXR) && defined(MOSS_PLATFORM_WINDOWS) || defined(MOSS_PLATFORM_LINUX) || defined(MOSS_PLATFORM_ANDROID))
#endif // MOSS_OPENVR_H

