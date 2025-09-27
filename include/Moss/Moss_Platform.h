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
#ifndef MOSS_PLATFORM_H
#define MOSS_PLATFORM_H

/*          Moss Platform
 *    Window & Popups windows
 *    Monitor
 *    Input - #define Keyboard, Mouse, Controllers
 *    Camera
 *    Haptic Feedback
 *    Time
 *    OS specific
*/

/*  TODO
 - Add functions to load in dll/libs in/out.
 - Get GPU info
 - Storage indfo.
*/

#ifdef __cplusplus
extern "C" {
#endif

#ifdef MOSS_USE_VULKAN
#include <vulkan/vulkan.h>
#endif


#include <Moss/Core/Core.h>

#define KEY_0
#define KEY_1
#define KEY_2
#define KEY_3
#define KEY_4
#define KEY_5
#define KEY_6
#define KEY_7
#define KEY_8
#define KEY_9
#define KEY_A
#define KEY_B
#define KEY_C
#define KEY_D
#define KEY_E
#define KEY_F
#define KEY_G
#define KEY_H
#define KEY_I
#define KEY_J
#define KEY_K
#define KEY_L
#define KEY_M
#define KEY_N
#define KEY_O, 
#define KEY_P, 
#define KEY_Q, 
#define KEY_R, 
#define KEY_S, 
#define KEY_T, 
#define KEY_U, 
#define KEY_V, 
#define KEY_W, 
#define KEY_X, 
#define KEY_Y, 
#define KEY_Z,
#define KEY_APOSTROPHE, 
#define KEY_BACKSLASH, 
#define KEY_COMMA, 
#define KEY_EQUAL, 
#define KEY_GRAVE_ACCENT, 
#define KEY_LEFT_BRACKET, 
#define KEY_MINUS, 
#define KEY_PERIOD, 
#define KEY_RIGHT_BRACKET, 
#define KEY_SEMICOLON, 
#define KEY_SLASH, 
#define KEY_WORLD_2,     
#define KEY_BACKSPACE, 
#define KEY_DELETE, 
#define KEY_END, 
#define KEY_ENTER, 
#define KEY_ESCAPE, 
#define KEY_HOME, 
#define KEY_INSERT, 
#define KEY_MENU, 
#define KEY_PAGE_DOWN, 
#define KEY_PAGE_UP, 
#define KEY_PAUSE, 
#define KEY_SPACE, 
#define KEY_TAB,
#define KEY_CAPS_LOCK, 
#define KEY_NUM_LOCK, 
#define KEY_SCROLL_LOCK,
#define KEY_F1, 
#define KEY_F2, 
#define KEY_F3,  
#define KEY_F4,  
#define KEY_F5,  
#define KEY_F6,  
#define KEY_F7,  
#define KEY_F8,  
#define KEY_F9, 
#define KEY_F10, 
#define KEY_F11, 
#define KEY_F12, 
#define KEY_F13, 
#define KEY_F14, 
#define KEY_F15, 
#define KEY_F16, 
#define KEY_F17, 
#define KEY_F18, 
#define KEY_F19, 
#define KEY_F20, 
#define KEY_F21, 
#define KEY_F22, 
#define KEY_F23, 
#define KEY_F24,
#define KEY_LEFT_ALT, 
#define KEY_LEFT_CONTROL, 
#define KEY_LEFT_SHIFT, 
#define KEY_LEFT_SUPER,
#define KEY_PRINT_SCREEN, 
#define KEY_RIGHT_ALT, 
#define KEY_RIGHT_CONTROL, 
#define KEY_RIGHT_SHIFT, 
#define KEY_RIGHT_SUPER, 
#define KEY_DOWN, 
#define KEY_LEFT, 
#define KEY_RIGHT, 
#define KEY_UP,
#define KEY_KP_0, 
#define KEY_KP_1, 
#define KEY_KP_2, 
#define KEY_KP_3, 
#define KEY_KP_4, 
#define KEY_KP_5, 
#define KEY_KP_6, 
#define KEY_KP_7, 
#define KEY_KP_8, 
#define KEY_KP_9, 
#define KEY_KP_ADD, 
#define KEY_KP_DECIMAL, 
#define KEY_KP_DIVIDE, 
#define KEY_KP_ENTER, 
#define KEY_KP_EQUAL, 
#define KEY_KP_MULTIPLY, 
#define KEY_KP_SUBTRACT,

#define MOUSE_LEFT,
#define MOUSE_RIGHT
#define MOUSE_MIDDLE
#define MOUSE_BUTTON_4
#define MOUSE_BUTTON_5
#define MOUSE_BUTTON_6
#define MOUSE_BUTTON_7
#define MOUSE_BUTTON_8

#define GAMEPAD_BUTTON_A
#define GAMEPAD_BUTTON_B
#define GAMEPAD_BUTTON_X
#define GAMEPAD_BUTTON_Y
#define GAMEPAD_BUTTON_LEFT_BUMPER
#define GAMEPAD_BUTTON_RIGHT_BUMPER
#define GAMEPAD_BUTTON_BACK
#define GAMEPAD_BUTTON_START
#define GAMEPAD_BUTTON_GUIDE
#define GAMEPAD_BUTTON_LEFT_THUMB
#define GAMEPAD_BUTTON_RIGHT_THUMB
#define GAMEPAD_BUTTON_DPAD_UP
#define GAMEPAD_BUTTON_DPAD_RIGHT
#define GAMEPAD_BUTTON_DPAD_DOWN
#define GAMEPAD_BUTTON_DPAD_LEFT

#define GAMEPAD_BUTTON_CROSS  = GAMEPAD_BUTTON_A
#define GAMEPAD_BUTTON_CIRCLE = GAMEPAD_BUTTON_B
#define GAMEPAD_BUTTON_SQUARE = GAMEPAD_BUTTON_X
#define GAMEPAD_BUTTON_TRIANGLE = GAMEPAD_BUTTON_Y

#define GAMEPAD_AXIS_LEFT_X,            // Left Stick X Axis
#define GAMEPAD_AXIS_LEFT_Y,            // Left Stick Y Axis
#define GAMEPAD_AXIS_RIGHT_X,           // Right Stick X Axis
#define GAMEPAD_AXIS_RIGHT_Y,           // Right Stick Y Axis
#define GAMEPAD_AXIS_LEFT_TRIGGER,      // Left Trigger
#define GAMEPAD_AXIS_RIGHT_TRIGGER,     // Right Trigger
#define GAMEPAD_AXIS_TOUCHPAD_X,        // (PS4/PS5)
#define GAMEPAD_AXIS_TOUCHPAD_Y,
#define GAMEPAD_AXIS_GYRO_X,
#define GAMEPAD_AXIS_GYRO_Y,
#define GAMEPAD_AXIS_GYRO_Z,

/*          Haptic          */
#define MOSS_HAPTIC_AUTOCENTER
#define MOSS_HAPTIC_CARTESIAN
#define MOSS_HAPTIC_CONSTANT
#define MOSS_HAPTIC_CUSTOM
#define MOSS_HAPTIC_DAMPER
#define MOSS_HAPTIC_FRICTION
#define MOSS_HAPTIC_GAIN
#define MOSS_HAPTIC_INERTIA
#define MOSS_HAPTIC_INFINITY
#define MOSS_HAPTIC_LEFTRIGHT
#define MOSS_HAPTIC_PAUSE
#define MOSS_HAPTIC_POLAR
#define MOSS_HAPTIC_RAMP
#define MOSS_HAPTIC_RESERVED1
#define MOSS_HAPTIC_RESERVED2
#define MOSS_HAPTIC_RESERVED3
#define MOSS_HAPTIC_SAWTOOTHDOWN
#define MOSS_HAPTIC_SAWTOOTHUP
#define MOSS_HAPTIC_SINE
#define MOSS_HAPTIC_SPHERICAL
#define MOSS_HAPTIC_SPRING
#define MOSS_HAPTIC_SQUARE
#define MOSS_HAPTIC_STATUS
#define MOSS_HAPTIC_STEERING_AXIS
#define MOSS_HAPTIC_TRIANGLE

enum Moss_WindowFlags {
    MOSS_WINDOW_NOTITLEBAR = 0x00000001,        // no window decoration
    FLAG_RESIZE_DISABLED = 0,
    FLAG_ALWAYS_ON_TOP = 20,
    FLAG_TRANSPARENT = 3,
    FLAG_NO_FOCUS = 4,
    FLAG_POPUP = 5,
    FLAG_EXTEND_TO_TITLE = 6,
    FLAG_MOUSE_PASSTHROUGH = 7,
    FLAG_SHARP_CORNERS = 8,
    FLAG_EXCLUDE_FROM_CAPTURE = 9,
    FLAG_MAX = 10,
    FLAG_WINDOW_OPENGL = 0x00000002,             // window usable with OpenGL context
    FLAG_WINDOW_SHOWN = 0x00000004,              // window is visible
    FLAG_WINDOW_HIDDEN = 0x00000008,             // window is not visible
    FLAG_WINDOW_BORDERLESS = 0x00000010,         // no window decoration
    FLAG_WINDOW_RESIZABLE = 0x00000020,          // window can be resized 
    FLAG_WINDOW_MINIMIZED = 0x00000040,          // window is minimized
    FLAG_WINDOW_MAXIMIZED = 0x00000080,          // window is maximized 
    FLAG_WINDOW_MOUSE_GRABBED = 0x00000100,      // window has grabbed mouse input
    FLAG_WINDOW_INPUT_FOCUS = 0x00000200,        // window has input focus
    FLAG_WINDOW_MOUSE_FOCUS = 0x00000400,        // window has mouse focus
    FLAG_WINDOW_FOREIGN = 0x00000800,            // window not created by Moss
    FLAG_WINDOW_ALLOW_HIGHDPI = 0x00002000,      // window should be created in high-DPI mode if supported. On macOS NSHighResolutionCapable must be set true in the application's Info.plist for this to have any effect.
    
    FLAG_WINDOW_ALWAYS_ON_TOP    = 0x00008000,   // window should always be above others
    FLAG_WINDOW_SKIP_TASKBAR     = 0x00010000,   // window should not be added to the taskbar
    FLAG_WINDOW_UTILITY          = 0x00020000,   // window should be treated as a utility window
    FLAG_WINDOW_TOOLTIP          = 0x00040000,   // window should be treated as a tooltip
    MOSS_WINDOW_POPUP_MENU       = 0x00080000,   // window should be treated as a popup menu
    FLAG_WINDOW_KEYBOARD_GRABBED = 0x00100000,   // window has grabbed keyboard input
    FLAG_WINDOW_VULKAN           = 0x10000000,   // window usable for Vulkan surface
    FLAG_WINDOW_METAL            = 0x20000000,   // window usable for Metal view

    FLAG_WINDOW_INPUT_GRABBED = FLAG_WINDOW_MOUSE_GRABBED // equivalent to FLAG_WINDOW_MOUSE_GRABBED for compatibility
} Moss_WindowFlags;

enum Moss_MessageBoxFlags {
    Moss_MessageBox_Flag_AbortEntryIgnore = 0,  // The message box contains three push buttons: Abort, Retry, and Ignore.
    Moss_MessageBox_Flag_CancelTryContinue = 1, // The message box contains three push buttons: Cancel, Try Again, Continue.
    Moss_MessageBox_Flag_Help = 3,              // Adds a Help button to the message box.
    Moss_MessageBox_Flag_Ok = 4,                // The message box contains one push button: OK. This is the default.
    Moss_MessageBox_Flag_OkCancel = 5,          // The message box contains two push buttons: OK and Cancel.
    Moss_MessageBox_Flag_RetryCancel = 6,       // The message box contains two push buttons: Retry and Cancel.
    Moss_MessageBox_Flag_YesNo = 7,             // The message box contains two push buttons: Yes and No.
    Moss_MessageBox_Flag_YesNoCancel = 8,       // The message box contains three push buttons: Yes, No, and Cancel.
} Moss_MessageBoxFlags;

enum Moss_WindowMode {
    Moss_WindowMode_WINDOWED = 0,              //
    Moss_WindowMode_MINIMIZED = 1,             //
    Moss_WindowMode_MAXIMIZED = 2,             //
    Moss_WindowMode_FULLSCREEN = 3,            //
    Moss_WindowMode_EXCLUSIVE_FULLSCREEN = 4,  //
} Moss_WindowMode;

// Cursor
enum Moss_CursorMode {
    Moss_CursorMode_VISIBLE = 0,             //
    Moss_CursorMode_HIDDEN = 0,              //
    Moss_CursorMode_CAPTURED = 0,            //
    Moss_CursorMode_CONFINED = 0,            //
    Moss_CursorMode_CONFINED_HIDDEN = 0,     //
    Moss_CursorMode_MAX= 0,                  //
} Moss_CursorMode;

enum Moss_CursorShape {
    Moss_CursorShape_ARROW = 0,           //
    Moss_CursorShape_IBEAM = 1,           //
    Moss_CursorShape_POINTING_HAND = 2,   //
    Moss_CursorShape_CROSS = 3,           //
    Moss_CursorShape_WAIT = 4,            //
    Moss_CursorShape_BUSY = 5,            //
    Moss_CursorShape_DRAG = 6,            //
    Moss_CursorShape_CAN_DROP = 7,        //
    Moss_CursorShape_FORBIDDEN = 8,       //
    Moss_CursorShape_VSIZE = 9,           //
    Moss_CursorShape_HSIZE = 10,          //
    Moss_CursorShape_BDIAGSIZE = 11,      //
    Moss_CursorShape_FDIAGSIZE = 12,      //
    Moss_CursorShape_MOVE = 13,           //
    Moss_CursorShape_VSPLIT = 14,         //
    Moss_CursorShape_HSPLIT = 15,         //
    Moss_CursorShape_HELP = 16            //
} Moss_CursorShape;

struct Moss_Window;
struct Moss_Monitor;
struct Moss_Curser;

struct Moss_GammaRamp { unsigned char* size; unsigned char* red; unsigned char* green; unsigned char* blue; };
struct Moss_VideoMode { int width, height, redBits, greenBits, blueBits, refreshRate; };
struct Moss_Image { int width; int height; unsigned char* pixels; };

struct Moss_Timer;
struct Moss_Thread;
typedef uint64 Moss_Time;

//enum Moss_VideoCapturePosition { CAMERA_POSITION_UNKNOWN, CAMERA_POSITION_FRONT_FACING, CAMERA_POSITION_BACK_FACING } Moss_VideoCapturePosition;
/*
enum Moss_ThreadState
{
    THREAD_UNKNOWN,     // The thread is not valid
    THREAD_ALIVE,       // The thread is currently running
    THREAD_DETACHED,    // The thread is detached and can't be waited on
    THREAD_COMPLETE     // The thread has finished and should be cleaned up with WaitThread()
} Moss_ThreadState;

enum Moss_ThreadPriority {
    Moss_Thread_Priority_Low,
    Moss_Thread_Priority_Normal,
    Moss_Thread_Priority_High,
    Moss_Thread_Priority_Critical
} Moss_ThreadPriority;
*/
enum InputEventType {
    EVENT_NONE,
    EVENT_KEYDOWN,
    EVENT_KEYUP,
    EVENT_MOUSEBUTTONDOWN,
    EVENT_MOUSEBUTTONUP,
    EVENT_MOUSEMOVE,
    EVENT_CONTROLLERBUTTONDOWN,
    EVENT_CONTROLLERBUTTONUP
};

#pragma warning(push)
#pragma warning(disable : 4820)

struct Moss_Event {
    InputEventType type;
    union {
        struct { int keycode; } keyboard;
        struct { int button; int x, y; int deltaX, deltaY; int wheelDelta;} mouse;
        struct { int button; float axisValueL; float axisValueR; } controller;
    };
};

#pragma warning(pop)


struct Moss_Locale {
    char* country;
    char* language;
};

struct Moss_HapticDirection;
struct Moss_HapticConstant;
struct Moss_HapticPeriodic;
struct Moss_HapticCondition;
struct Moss_HapticRamp;
struct Moss_HapticLeftRight;
struct Moss_HapticCustom; 
union Moss_HapticEffect;
struct Moss_Haptic;

struct Moss_VideoCapture;  // Add functions for this
struct Moss_Joystick;  // Add functions for this
struct Moss_Gamepad;   // Add functions for this
struct Moss_Touchscreen;   // Add functions for this
struct Moss_Pen;   // Add functions for this

typedef uint16 Moss_Keycode;
typedef uint16 Moss_Keymod;
typedef uint16 Moss_HapticEffectType;
typedef int Moss_HapticEffectID;

// unique IDs
typedef uint32 Moss_HapticID;
typedef uint32 Moss_MonitorID;
typedef uint32 Moss_KeyboardID;
typedef uint32 Moss_JoystickID;
typedef uint32 Moss_VideoCaptureID;

// Callbacks
static void (Moss_FramebufferSizeCallback)(int, int);
static void (Moss_WindowResizeCallback)(int, int);
static void (Moss_WindowContentScaleCallback)(int, int);
static void (Moss_WindowPositionCallback)(int, int);
static void (Moss_WindowFocusCallback)(bool focused);
static void (Moss_WindowSizeCallback)(int width, int height);


MOSS_API Moss_Monitor* Moss_GetPrimaryMonitor();
MOSS_API Moss_Monitor* Moss_GetSecondaryMonitor();

/*! @brief Initialization of Moss. Must be called before anything else. @param X X. @ingroup Moss */
//MOSS_API bool Moss_Init();
/*! @brief Terminates Moss. Must be called at the end.  @param X X. @ingroup Moss */
//MOSS_API void Moss_Terminate();


//void Moss_WindowHint(int hint, int value);

/*! @brief Creates a window.  @param X X. *  @ingroup window */
MOSS_API Moss_Window* Moss_CreateWindow(const char* title, int width, int height, Moss_Monitor* monitor, Moss_Window* share);
MOSS_API void Moss_TerminateWindow(Moss_Window* window);
/*! @brief Creates a window popup. @param X X. @ingroup window */
MOSS_API bool Moss_CreateMessageBox(const char* title, const char* message, Moss_MessageBoxFlags flags, Moss_Window* window);
/*! @brief Used in while loop if window should close. @param X X. @ingroup window */
MOSS_API bool Moss_ShouldWindowClose(Moss_Window* window);
/*! @brief Pollevents. @param X X. @ingroup window */
MOSS_API void Moss_PollEvents(void);
/*! @brief Window Input Config. Gets Input controls like Keyboard, Mouse, and Controler. @param X X @ingroup window */
//MOSS_API void setWindowInputConfig(int mode); // has no functions
/*! @brief Change Window Mode. e.g. MINAMIZED, MAXIMIZED, FULLSCREEN, BORDERLESS. @param X X. @ingroup window */
//MOSS_API void setWindowMode(int mode); // has no functions
/*! @brief Change Window Flags. @param X X. @ingroup window */
//MOSS_API void setWindowFlag(int mode); // has no functions
/*! @brief X. @param X X.*/
MOSS_API int Moss_GetWindowWidth();
/*! @brief X. @param X X.*/
MOSS_API int Moss_GetWindowHeight();

/*! @brief X. @param X X @ingroup Window */
MOSS_API void Moss_SetWindowTitle(Moss_Window* window, const char* title);
/*! @brief X. @param X X @ingroup Window */
MOSS_API void Moss_SetWindowIcon(Moss_Window* window, Moss_Image image);
/*! @brief X. @param X X @ingroup Monitor */
MOSS_API void Moss_GetMonitorPhysicalSize(Moss_Monitor monitor, int* width_mm, int* height_mm);
/*! @brief X. @param X X @ingroup Monitor */
MOSS_API void Moss_GetMonitorContentScale(Moss_Monitor monitor, float* xscale, float* yscale);
/*! @brief X. @param X X @ingroup Monitor */
MOSS_API void Moss_GetMonitorPosition(Moss_Monitor monitor, int* x, int* y);
/*! @brief X. @param X X @ingroup Monitor */
MOSS_API const char* Moss_GetMonitorName(Moss_Monitor monitor);
/*! @brief X. @param X X @ingroup Monitor */
MOSS_API void Moss_SetGammaRamp(Moss_Monitor monitor, const Moss_GammaRamp* gammaRamp);
/*! @brief X. @param X X @ingroup Monitor */
MOSS_API Moss_GammaRamp* Moss_GetGammaRamp(Moss_Monitor monitor);
/*! @brief X. @param X X @ingroup Monitor */
MOSS_API void Moss_SetGamma(Moss_Monitor monitor, float gamma);


/*          Camera          */
/*! @brief X. @param X X @ingroup Video Capture. */
MOSS_API Moss_VideoCapture* Moss_OpenVideoCapture(Moss_VideoCaptureID captureID);
/*! @brief X. @param X X @ingroup Video Capture. */
MOSS_API void Moss_CloseVideoCapture(Moss_VideoCapture* cap);
/*! @brief X. @param X X @ingroup Video Capture. */
MOSS_API unsigned char* Moss_VideoCaptureReadFrame(Moss_VideoCapture* cap);


MOSS_API inline bool IsPressed(Keyboard k);
MOSS_API inline bool IsReleased(Keyboard k);
MOSS_API inline bool IsJustPressed(Keyboard k);
MOSS_API inline bool IsJustReleased(Keyboard k);
MOSS_API inline bool IsPressed(Mouse b);
MOSS_API inline bool IsReleased(Mouse b);
MOSS_API inline bool IsJustPressed(Mouse b);
MOSS_API inline bool IsJustReleased(Mouse b);

MOSS_API inline bool IsPressed(Gamepad b);
MOSS_API inline bool IsReleased(Gamepad b);
MOSS_API inline bool IsJustPressed(Gamepad b);
MOSS_API inline bool IsJustReleased(Gamepad b);
//MOSS_API float GetJoyAxis(Joystick j);

/*            Haptic Feedback          */
/*! @brief X. @param X X.*/
MOSS_API Moss_Haptic* Moss_OpenHaptic(Moss_HapticID id);
/*! @brief X. @param X X.*/
MOSS_API void Moss_CloseHaptic(Moss_Haptic* haptic);
/*! @brief X. @param X X.*/
MOSS_API Moss_HapticID Moss_CreateHapticEffect(Moss_Haptic* haptic);
/*! @brief X. @param X X.*/
MOSS_API void Moss_DestroyHapticEffect(Moss_Haptic* haptic);
/*! @brief X. @param X X.*/
MOSS_API bool Moss_GetHapticEffectStatus(Moss_Haptic* haptic);
/*! @brief X. @param X X.*/
MOSS_API uint32 Moss_GetHapticFeatures(Moss_Haptic* haptic);
/*! @brief X. @param X X.*/
MOSS_API Moss_Haptic* Moss_GetHapticFromID(Moss_Haptic* haptic);
/*! @brief X. @param X X.*/
MOSS_API Moss_HapticID* Moss_GetHapticID(Moss_Haptic* haptic);
/*! @brief X. @param X X.*/
MOSS_API const char* Moss_GetHapticName(Moss_Haptic* haptic);
/*! @brief X. @param X X.*/
MOSS_API const char* Moss_GetHapticNameForID(Moss_Haptic* haptic);
/*! @brief X. @param X X.*/
MOSS_API Moss_HapticID* Moss_GetHaptics(Moss_Haptic* haptic);
/*! @brief X. @param X X.*/
MOSS_API int Moss_GetMaxHapticEffects(Moss_Haptic* haptic);
/*! @brief X. @param X X.*/
MOSS_API int Moss_GetMaxHapticEffectsPlaying(Moss_Haptic* haptic);
/*! @brief X. @param X X.*/
MOSS_API int Moss_GetNumHapticAxes(Moss_Haptic* haptic);
/*! @brief X. @param X X.*/
MOSS_API bool Moss_HapticEffectSupported(Moss_Haptic* haptic);
/*! @brief X. @param X X.*/
MOSS_API bool Moss_HapticRumbleSupported(Moss_Haptic* haptic);
/*! @brief X. @param X X.*/
MOSS_API bool Moss_InitHapticRumble(Moss_Haptic* joystick);
/*! @brief X. @param X X.*/
MOSS_API bool Moss_IsJoystickHaptic(Moss_Joystick);
/*! @brief X. @param X X.*/
MOSS_API bool Moss_IsMouseHaptic(void);
/*! @brief X. @param X X.*/
MOSS_API Moss_Haptic* Moss_OpenHapticFromJoystick(Moss_Joystick* joystick);
/*! @brief X. @param X X.*/
MOSS_API Moss_Haptic* Moss_OpenHapticFromMouse(void);
/*! @brief X. @param X X.*/
MOSS_API bool Moss_PauseHaptic(Moss_Haptic* haptic);
/*! @brief X. @param X X.*/
MOSS_API bool Moss_PlayHapticRumble(Moss_Haptic* haptic, float strength, uint32 length);
/*! @brief X. @param X X.*/
MOSS_API bool Moss_ResumeHaptic(Moss_Haptic* haptic);
/*! @brief X. @param X X.*/
MOSS_API bool Moss_RunHapticEffect(Moss_Haptic* haptic, uint32 iterations);
/*! @brief X. @param X X.*/
MOSS_API bool Moss_SetHapticAutocenter(Moss_Haptic* haptic, int center);
/*! @brief X. @param X X.*/
MOSS_API bool Moss_SetHapticGain(Moss_Haptic* haptic, int gain);
/*! @brief X. @param X X.*/
MOSS_API bool Moss_StopHapticEffect(Moss_Haptic* haptic, Moss_HapticEffectID effect);
MOSS_API bool Moss_StopHapticEffects(Moss_Haptic* haptic);
/*! @brief X. @param X X.*/
MOSS_API bool Moss_StopHapticRumble(Moss_Haptic* haptic);
/*! @brief X. @param X X.*/
MOSS_API bool Moss_UpdateHapticEffect(Moss_Haptic* haptic, Moss_HapticEffectID effect, const Moss_HapticEffect* data);


/*              CPU Info          */
// Get the number of logical CPU cores available.
MOSS_API int Moss_GetAvailableCPUCores(void);
// Determine the L1 cache line size of the CPU.
MOSS_API int Moss_GetCPUCacheLineSize(void);
// Get the amount of RAM configured in the system.
MOSS_API int Moss_GetSystemRAM(void);

/*            Storage Info        */


/*             OS Spesific        */

/*! @brief URL to a website link. @param url URL link.*/
MOSS_API bool Moss_OpenURL(const char *url);
/*! @brief Get Locale of the Operating system e.g. "UK" for United Kingdom and "en" for English.*/
MOSS_API Moss_Locale* Moss_GetLocale();

// OpenGL
#ifdef MOSS_USE_OPENGL
/*! @brief Sets window as current.  @param X X. @ingroup window */
MOSS_API void Moss_MakeContextCurrent(Moss_Window* window);
/*! @brief Swapbuffers used to swapbuffers for opengl. @ingroup window */
MOSS_API void Moss_SwapBuffers();
/*! @brief Swapbuffers but with a delay in seconds. @param X X. @ingroup window. */
MOSS_API void Moss_SwapBuffersInterval(int interval);
/*! @brief X. @param X X. @ingroup window. */
MOSS_API void* Moss_GetProcAddress(const char* procname);
#endif // MOSS_USE_OPENGL

// Vulkan
#ifdef MOSS_USE_VULKAN
/*! @brief Creates the window for vulkan @param X X @ingroup Vulkan. */
MOSS_API VkResult Moss_CreateWindowSurface(Moss_Window* window, VkInstance vk_instance, const VkAllocationCallbacks *allocator, VkSurfaceKHR* vk_surface);
/*! @brief X @param X X @ingroup Vulkan. */
MOSS_API int Moss_VulkanSupported(void);
/*! @brief X @param X X @ingroup Vulkan. */
//MOSS_API void Moss_InitVulkanLoader(PFN_vkGetInstanceProcAddr loader);
/*! @brief X @param X X @ingroup Vulkan. */
MOSS_API const char** Moss_GetRequiredInstanceExtensions(uint32_t* count);
/*! @brief X @param X X @ingroup Vulkan. */
MOSS_API void* Moss_GetInstanceProcAddress(VkInstance instance, const char* procname);
/*! @brief X @param X X @ingroup Vulkan. */
MOSS_API int Moss_GetPhysicalDevicePresentationSupport(Moss_Window& window, VkPhysicalDevice device, uint32_t queuefamily);
#endif // MOSS_USE_VULKAN

#if defined(MOSS_USE_XR)
bool Moss_IsXRExtensionSupported(const char* extensionName);
#endif 


// =================================================
/*                      Callbacks                 */
// =================================================

typedef void(*FramebufferResizeCallback)(int width, int height);
// Window
/*! @brief X.  @param X X @ingroup Window.*/
MOSS_API void Moss_SetFramebufferReSizeCallback(FramebufferResizeCallback callback);
/*! @brief X.  @param X X @ingroup Window.*/
MOSS_API void Moss_SetWindowSizeCallback(Moss_Window* window, int width, int height);
/*! @brief X.  @param X X @ingroup Window.*/
MOSS_API void Moss_SetWindowContentScaleCallback(Moss_Window* window, int width, int height);
/*! @brief X.  @param X X @ingroup Window.*/
MOSS_API void Moss_SetWindowSizeLimits(Moss_Window* window, int width, int height);
/*! @brief X.  @param X X @ingroup Window.*/
MOSS_API void Moss_SetWindowPositionCallback(Moss_Window* window, int x, int y);
/*! @brief X.  @param X X @ingroup Window.*/
MOSS_API void Moss_SetWindowFocusCallback(Moss_Window* window);
/*! @brief X.  @param X X @ingroup Window.*/
MOSS_API void Moss_SetWindowResizeCallback(void (*callback)(int width, int height));
/*! @brief sets the monitor configuration callback.  @param X X. @ingroup Monitor */
MOSS_API void Moss_SetMonitorCallback();

// Inputs
/*! @brief Set Key input callback. @param X X @ingroup Keyboard Input Callback. */
MOSS_API void Moss_SetKeyCallback();
/*! @brief Set mouse input callback. @param X X @ingroup Mouse Input Callback. */
MOSS_API void Moss_SetMouseButtonCallback();
/*! @brief Set mouse position callback. @param X X @ingroup Mouse Input Callback. */
MOSS_API void Moss_SetMousePositionCallback();
/*! @brief Set joystick input callback. @param X X @ingroup Joystick Input Callback. */
MOSS_API void Moss_SetJoyStickCallback();
/*! @brief Set gamepad input callback. @param X X @ingroup Gamepad Input Callback. */
MOSS_API void Moss_SetGamePadCallback();


#ifdef __cplusplus
}
#endif

#endif // MOSS_PLATFORM_H