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
////////////////////////////////////////////////////////////////////////////
/*                              Moss_XR.h

                Moss XR handles all XR using OpenXR version 1.1.
*/
///////////////////////////////////////////////////////////////////////////

// Supportd Platforms: Windows, Linux, and Android
// Supported Graphics: OpenGL, Vulkan, and DirectX

#ifndef MOSS_OPENVR_H
#define MOSS_OPENVR_H

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
