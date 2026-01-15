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

/*!
 * @file Moss_Platform.h
 * @brief Core platform abstraction layer for the Moss Framework.
 *
 * The platform module provides a unified API for interacting with
 * the operating system, hardware devices, and runtime environment.
 * It ensures cross-platform consistency across Windows, Linux, macOS,
 * iOS, and Android.
 *
 * ### Primary Responsibilities:
 * - **Window Management** — Creation and control of application and popup windows.
 * - **Display & Monitor Handling** — Query and manage monitor configurations, resolutions, and refresh rates.
 * - **Input System** — Unified handling of keyboard, mouse, controller, and touch inputs.
 * - **Camera Support** — Management of active viewports, XR cameras, and display orientation.
 * - **Haptic Feedback** — Device vibration and tactile feedback support.
 * - **Timing Utilities** — High-precision timers, delta-time tracking, and performance profiling.
 * - **System Integration** — OS-level utilities such as:
 *    - Dynamic library loading/get/unloading (DLL/SO/DYLIB)
 *    - Opening URLs or external resources
 *    - Querying CPU, and memory information
 *    - Locale access
 */


#ifdef MOSS_USE_VULKAN
#include <vulkan/vulkan.h>
#endif

#include <stddef.h>
#include <stdint.h>

#include <Moss/Moss_stdinc.h>
// Keyboard
/* Alphanumeric */
#define KEY_0 0
#define KEY_1 1
#define KEY_2 2
#define KEY_3 3
#define KEY_4 4
#define KEY_5 5
#define KEY_6 6
#define KEY_7 7
#define KEY_8 8
#define KEY_9 9

#define KEY_A 10
#define KEY_B 11
#define KEY_C 12
#define KEY_D 13
#define KEY_E 14
#define KEY_F 15
#define KEY_G 16
#define KEY_H 17
#define KEY_I 18
#define KEY_J 19
#define KEY_K 20
#define KEY_L 21
#define KEY_M 22
#define KEY_N 23
#define KEY_O 24
#define KEY_P 25
#define KEY_Q 26
#define KEY_R 27
#define KEY_S 28
#define KEY_T 29
#define KEY_U 30
#define KEY_V 31
#define KEY_W 32
#define KEY_X 33
#define KEY_Y 34
#define KEY_Z 35

/* Punctuation */
#define KEY_APOSTROPHE      36
#define KEY_BACKSLASH       37
#define KEY_COMMA           38
#define KEY_EQUAL           39
#define KEY_GRAVE_ACCENT    40
#define KEY_LEFT_BRACKET    41
#define KEY_MINUS           42
#define KEY_PERIOD          43
#define KEY_RIGHT_BRACKET   44
#define KEY_SEMICOLON       45
#define KEY_SLASH           46
#define KEY_WORLD_1         47
#define KEY_WORLD_2         48

/* Control keys */
#define KEY_BACKSPACE       49
#define KEY_DELETE          50
#define KEY_END             51
#define KEY_ENTER           52
#define KEY_ESCAPE          53
#define KEY_HOME            54
#define KEY_INSERT          55
#define KEY_MENU            56
#define KEY_PAGE_DOWN       57
#define KEY_PAGE_UP         58
#define KEY_PAUSE           59
#define KEY_SPACE           60
#define KEY_TAB             61

/* Locks */
#define KEY_CAPS_LOCK       62
#define KEY_NUM_LOCK        63
#define KEY_SCROLL_LOCK     64

/* Function keys */
#define KEY_F1              65
#define KEY_F2              66
#define KEY_F3              67
#define KEY_F4              68
#define KEY_F5              69
#define KEY_F6              70
#define KEY_F7              71
#define KEY_F8              72
#define KEY_F9              73
#define KEY_F10             74
#define KEY_F11             75
#define KEY_F12             76
#define KEY_F13             77
#define KEY_F14             78
#define KEY_F15             79
#define KEY_F16             80
#define KEY_F17             81
#define KEY_F18             82
#define KEY_F19             83
#define KEY_F20             84
#define KEY_F21             85
#define KEY_F22             86
#define KEY_F23             87
#define KEY_F24             88

/* Modifiers */
#define KEY_LEFT_ALT        89
#define KEY_LEFT_CONTROL    90
#define KEY_LEFT_SHIFT      91
#define KEY_LEFT_SUPER      92
#define KEY_PRINT_SCREEN    93
#define KEY_RIGHT_ALT       94
#define KEY_RIGHT_CONTROL   95
#define KEY_RIGHT_SHIFT     96
#define KEY_RIGHT_SUPER     97

/* Arrows */
#define KEY_DOWN            98
#define KEY_LEFT            99
#define KEY_RIGHT           100
#define KEY_UP              101

/* Keypad */
#define KEY_KP_0            102
#define KEY_KP_1            103
#define KEY_KP_2            104
#define KEY_KP_3            105
#define KEY_KP_4            106
#define KEY_KP_5            107
#define KEY_KP_6            108
#define KEY_KP_7            109
#define KEY_KP_8            110
#define KEY_KP_9            111
#define KEY_KP_ADD          112
#define KEY_KP_DECIMAL      113
#define KEY_KP_DIVIDE       114
#define KEY_KP_ENTER        115
#define KEY_KP_EQUAL        116
#define KEY_KP_MULTIPLY     117
#define KEY_KP_SUBTRACT     118

#define MOSS_LAST_KEY       KEY_KP_SUBTRACT

// Mouse
#define MOUSE_LEFT               0
#define MOUSE_RIGHT              1
#define MOUSE_MIDDLE             2
#define MOUSE_BUTTON_4           3
#define MOUSE_BUTTON_5           4
#define MOUSE_BUTTON_6           5
#define MOUSE_BUTTON_7           6
#define MOUSE_BUTTON_8           7

#define MOSS_MOUSE_BUTTON_LAST   MOUSE_BUTTON_8

// Gamepad
#define GAMEPAD_BUTTON_A                0
#define GAMEPAD_BUTTON_B                1
#define GAMEPAD_BUTTON_X                2
#define GAMEPAD_BUTTON_Y                3
#define GAMEPAD_BUTTON_LEFT_BUMPER      4
#define GAMEPAD_BUTTON_RIGHT_BUMPER     5
#define GAMEPAD_BUTTON_BACK             6
#define GAMEPAD_BUTTON_START            7
#define GAMEPAD_BUTTON_GUIDE            8
#define GAMEPAD_BUTTON_LEFT_THUMB       9
#define GAMEPAD_BUTTON_RIGHT_THUMB      10
#define GAMEPAD_BUTTON_DPAD_UP          11
#define GAMEPAD_BUTTON_DPAD_RIGHT       12
#define GAMEPAD_BUTTON_DPAD_DOWN        13
#define GAMEPAD_BUTTON_DPAD_LEFT        14

#define MOSS_GAMEPAD_BUTTON_LAST        GAMEPAD_BUTTON_DPAD_LEFT

// PS naming
#define GAMEPAD_BUTTON_CROSS  = GAMEPAD_BUTTON_A
#define GAMEPAD_BUTTON_CIRCLE = GAMEPAD_BUTTON_B
#define GAMEPAD_BUTTON_SQUARE = GAMEPAD_BUTTON_X
#define GAMEPAD_BUTTON_TRIANGLE = GAMEPAD_BUTTON_Y

// Joystick axis
#define GAMEPAD_AXIS_LEFT_X          0
#define GAMEPAD_AXIS_LEFT_Y          1
#define GAMEPAD_AXIS_RIGHT_X         2
#define GAMEPAD_AXIS_RIGHT_Y         3
#define GAMEPAD_AXIS_LEFT_TRIGGER    4
#define GAMEPAD_AXIS_RIGHT_TRIGGER   5
#define GAMEPAD_AXIS_TOUCHPAD_X      6
#define GAMEPAD_AXIS_TOUCHPAD_Y      7 
#define GAMEPAD_AXIS_GYRO_X          8
#define GAMEPAD_AXIS_GYRO_Y          9
#define GAMEPAD_AXIS_GYRO_Z          10

#define MOSS_JOY_AXIS_LAST           GAMEPAD_AXIS_GYRO_Z

/*          Haptic          */
/* Effect types */
#define MOSS_HAPTIC_CONSTANT        (1u << 0)
#define MOSS_HAPTIC_SINE            (1u << 1)
#define MOSS_HAPTIC_SQUARE          (1u << 2)
#define MOSS_HAPTIC_TRIANGLE        (1u << 3)
#define MOSS_HAPTIC_SAWTOOTHUP      (1u << 4)
#define MOSS_HAPTIC_SAWTOOTHDOWN    (1u << 5)
#define MOSS_HAPTIC_RAMP            (1u << 6)
#define MOSS_HAPTIC_CUSTOM          (1u << 7)

/* Force feedback effects */
#define MOSS_HAPTIC_SPRING          (1u << 8)
#define MOSS_HAPTIC_DAMPER          (1u << 9)
#define MOSS_HAPTIC_INERTIA         (1u << 10)
#define MOSS_HAPTIC_FRICTION        (1u << 11)

/* Device control */
#define MOSS_HAPTIC_GAIN            (1u << 12)
#define MOSS_HAPTIC_AUTOCENTER      (1u << 13)
#define MOSS_HAPTIC_STATUS          (1u << 14)
#define MOSS_HAPTIC_PAUSE           (1u << 15)

/* Direction encoding */
#define MOSS_HAPTIC_POLAR           (1u << 16)
#define MOSS_HAPTIC_CARTESIAN       (1u << 17)
#define MOSS_HAPTIC_SPHERICAL       (1u << 18)

/* Device-specific */
#define MOSS_HAPTIC_LEFTRIGHT       (1u << 19)
#define MOSS_HAPTIC_STEERING_AXIS   (1u << 20)

/* Special values */
#define MOSS_HAPTIC_INFINITY        (1u << 21)

/* Reserved for future expansion */
#define MOSS_HAPTIC_RESERVED1       (1u << 22)
#define MOSS_HAPTIC_RESERVED2       (1u << 23)
#define MOSS_HAPTIC_RESERVED3       (1u << 24)


typedef uint32_t Moss_FingerID;
typedef uint32_t Moss_TouchID;
typedef uint32_t Moss_HapticID;
typedef uint32_t Moss_CameraID;


typedef uint16_t Moss_Key;
typedef uint8_t Moss_MouseButton;
typedef uint8_t Moss_JoystickAxis;
typedef uint8_t Moss_GamepadButton;

typedef uint32_t Moss_HapticFlags;

typedef struct Moss_Window;
typedef struct Moss_Monitor;
typedef struct Moss_Curser;
typedef struct Moss_GamepadBinding;


typedef struct Moss_GammaRamp { unsigned char* size; unsigned char* red; unsigned char* green; unsigned char* blue; };
typedef struct Moss_VideoMode { int width, height, redBits, greenBits, blueBits, refreshRate; };
typedef struct Moss_Image { int width; int height; unsigned char* pixels; };

typedef struct Moss_Locale {
    char* country;
    char* language;
};

struct Moss_Timer;
struct Moss_Thread;
typedef uint64 Moss_Time;

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


typedef enum Moss_WindowFlags {
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

typedef enum Moss_MessageBoxFlags {
    Moss_MessageBox_Flag_AbortEntryIgnore = 0,  // The message box contains three push buttons: Abort, Retry, and Ignore.
    Moss_MessageBox_Flag_CancelTryContinue = 1, // The message box contains three push buttons: Cancel, Try Again, Continue.
    Moss_MessageBox_Flag_Help = 3,              // Adds a Help button to the message box.
    Moss_MessageBox_Flag_Ok = 4,                // The message box contains one push button: OK. This is the default.
    Moss_MessageBox_Flag_OkCancel = 5,          // The message box contains two push buttons: OK and Cancel.
    Moss_MessageBox_Flag_RetryCancel = 6,       // The message box contains two push buttons: Retry and Cancel.
    Moss_MessageBox_Flag_YesNo = 7,             // The message box contains two push buttons: Yes and No.
    Moss_MessageBox_Flag_YesNoCancel = 8,       // The message box contains three push buttons: Yes, No, and Cancel.
} Moss_MessageBoxFlags;

typedef enum Moss_WindowMode {
    Moss_WindowMode_WINDOWED = 0,              //
    Moss_WindowMode_MINIMIZED = 1,             //
    Moss_WindowMode_MAXIMIZED = 2,             //
    Moss_WindowMode_FULLSCREEN = 3,            //
    Moss_WindowMode_EXCLUSIVE_FULLSCREEN = 4,  //
} Moss_WindowMode;

// Cursor
typedef enum Moss_CursorMode {
    Moss_CursorMode_VISIBLE = 0,             //
    Moss_CursorMode_HIDDEN = 0,              //
    Moss_CursorMode_CAPTURED = 0,            //
    Moss_CursorMode_CONFINED = 0,            //
    Moss_CursorMode_CONFINED_HIDDEN = 0,     //
    Moss_CursorMode_MAX= 0,                  //
} Moss_CursorMode;

typedef enum Moss_CursorShape {
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


// =================================================
//                 Callback Type Definitions
// =================================================

//! @brief Callback for framebuffer resize events. @param width  New framebuffer width, in pixels. @param height New framebuffer height, in pixels.
typedef void (*Moss_FramebufferResizeCallback)(int width, int height);
//! @brief Callback for logical window size changes. @param width  New window width, in screen coordinates. @param height New window height, in screen coordinates.
typedef void (*Moss_WindowSizeCallback)(int width, int height);
//! @brief Callback for window position changes on screen. @param xpos New X coordinate of the window’s top-left corner. @param ypos New Y coordinate of the window’s top-left corner.
typedef void (*Moss_WindowPositionCallback)(int xpos, int ypos);
//! @brief Callback for window focus events. @param focused True if the window gained focus; false if it lost focus.
typedef void (*Moss_WindowFocusCallback)(bool focused);
//! @brief Callback for content scale changes (e.g., HiDPI scaling). @param xscale X-axis content scale factor. @param yscale Y-axis content scale factor.
typedef void (*Moss_WindowContentScaleCallback)(float xscale, float yscale);
//! @brief Callback for general window resize notifications (platform-driven). @param width  New window width in pixels. @param height New window height in pixels.
typedef void (*Moss_WindowResizeCallback)(int width, int height);
//! @brief Callback for monitor configuration changes (e.g. hotplug events). @param monitorName Name or ID of the monitor that changed. @param connected True if the monitor was connected; false if disconnected.
typedef void (*Moss_MonitorCallback)(const char* monitorName, bool connected);
//! @brief X. @param width X. @param X. */
typedef void (MOSS_CALL* Moss_DialogFileCallback)(void *userdata, const char * const *filelist, int filter);
//! @brief X. @param width X. @param X. */
typedef bool (*Moss_DirectoryIterateFn)(const Moss_PathInfo* info, const char* path, void* user_data);



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
/*! @brief This is to call for closing a window. @param Moss_Window* window @ingroup Window */
MOSS_API void Moss_CloseWindow(Moss_Window* window);

/*            Monitor          */
/*! @brief X. @param X X @ingroup Monitor */
MOSS_API Moss_Monitor* Moss_MonitorGetPrimary();
/*! @brief X. @param X X @ingroup Monitor @returns returns monitor unless if theres not a second will return nullptr. */
MOSS_API Moss_Monitor* Moss_MonitorGetSecondary();
/*! @brief X. @param X X @ingroup Monitor */
MOSS_API void Moss_MonitorGetPhysicalSize(Moss_Monitor monitor, int* width_mm, int* height_mm);
/*! @brief X. @param X X @ingroup Monitor */
MOSS_API void Moss_MonitorGetContentScale(Moss_Monitor monitor, float* xscale, float* yscale);
/*! @brief X. @param X X @ingroup Monitor */
MOSS_API void Moss_MonitorGetPosition(Moss_Monitor monitor, int* x, int* y);
/*! @brief X. @param X X @ingroup Monitor */
MOSS_API const char* Moss_MonitorGetName(Moss_Monitor monitor);
/*! @brief X. @param X X @ingroup Monitor */
MOSS_API void Moss_MonitorSetGammaRamp(Moss_Monitor monitor, const Moss_GammaRamp* gammaRamp);
/*! @brief X. @param X X @ingroup Monitor */
MOSS_API Moss_GammaRamp* Moss_MonitorGetGammaRamp(Moss_Monitor monitor);
/*! @brief X. @param X X @ingroup Monitor */
MOSS_API void Moss_MonitorSetGamma(Moss_Monitor monitor, float gamma);


MOSS_API bool Moss_IsKeyPressed(Moss_Key key);
MOSS_API bool Moss_IsKeyJustPressed(Moss_Key key);
MOSS_API bool Moss_IsKeyJustReleased(Moss_Key key);
MOSS_API Moss_Keyboard Moss_InputGetKey();

MOSS_API bool Moss_IsMousePressed(Moss_MouseButton button);
MOSS_API bool Moss_IsMouseJustPressed(Moss_MouseButton button);
MOSS_API bool Moss_IsMouseJustReleased(Moss_MouseButton button);
MOSS_API Moss_Keyboard Moss_InputGetMouse();
MOSS_API void Moss_GetMousePosition(int* x, int* y);
MOSS_API void Moss_SetMousePosition(int x, int y);
MOSS_API void Moss_SetMouseVisible(bool visible);


// Gamepad management
MOSS_API int Moss_GetNumGamepads(void);
MOSS_API Moss_Gamepad* Moss_OpenGamepad(Moss_GamepadID id);
MOSS_API void Moss_CloseGamepad(Moss_Gamepad* gp);
MOSS_API bool Moss_GamepadConnected(Moss_Gamepad* gp);
MOSS_API void Moss_UpdateGamepads(void); // poll / refresh all gamepads

// Button & axis
MOSS_API bool Moss_IsGamepadButtonPressed(Moss_Gamepad* gp, Moss_GamepadButton button);
MOSS_API bool Moss_IsGamepadButtonJustPressed(Moss_Gamepad* gp, Moss_GamepadButton button);
MOSS_API bool Moss_IsGamepadButtonJustReleased(Moss_Gamepad* gp, Moss_GamepadButton button);
MOSS_API float Moss_GetGamepadAxis(Moss_Gamepad* gp, Moss_GamepadAxis axis);

// Rumble / LED
MOSS_API bool Moss_RumbleGamepad(Moss_Gamepad* gp, uint16_t low, uint16_t high, uint32_t duration_ms);
MOSS_API bool Moss_RumbleGamepadTriggers(Moss_Gamepad* gp, uint16_t left, uint16_t right, uint32_t duration_ms);
MOSS_API bool Moss_SetGamepadLED(Moss_Gamepad* gp, uint8_t r, uint8_t g, uint8_t b);

// Metadata
MOSS_API const char* Moss_GetGamepadName(Moss_Gamepad* gp);
MOSS_API Moss_GamepadID Moss_GetGamepadID(Moss_Gamepad* gp);
MOSS_API int Moss_GetGamepadPlayerIndex(Moss_Gamepad* gp);
MOSS_API Moss_PowerState Moss_GetGamepadPowerInfo(Moss_Gamepad* gp, int* percent);
MOSS_API int Moss_GetNumGamepadTouchpads(Moss_Gamepad* gp);
MOSS_API int Moss_GetNumGamepadTouchpadFingers(Moss_Gamepad* gp);
MOSS_API bool Moss_GetGamepadTouchpadFinger(Moss_Gamepad* gp, int pad, int finger, bool* down, float* x, float* y, float* pressure);

// Mapping & type
MOSS_API const char* Moss_GetGamepadMapping(Moss_Gamepad* gp);
MOSS_API bool Moss_SetGamepadMapping(Moss_Gamepad* gp, const char* mapping);
MOSS_API void Moss_ReloadGamepadMappings(void);

MOSS_API Moss_GamepadButton Moss_InputGetGamepadButton();
MOSS_API Moss_GamepadAxis Moss_InputGetGamepadAxis();


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

MOSS_API Moss_PenDeviceType Moss_GetPenDeviceType(Moss_PenID instance_id);
MOSS_API const char* Moss_GetTouchDeviceName(Moss_TouchID touchID);
MOSS_API Moss_TouchID* Moss_GetTouchDevices(int *count);
MOSS_API Moss_TouchDeviceType Moss_GetTouchDeviceType(Moss_TouchID touchID);
MOSS_API Moss_Finger** Moss_GetTouchFingers(Moss_TouchID touchID, int *count);

/*              CPU Info          */
// Get the number of logical CPU cores available.
MOSS_API int Moss_GetAvailableCPUCores(void);
// Determine the L1 cache line size of the CPU.
MOSS_API int Moss_GetCPUCacheLineSize(void);
// Get the amount of RAM configured in the system.
MOSS_API int Moss_GetSystemRAM(void);

/*             OS Spesific        */
/*! @brief URL to a website link. @param url URL link.*/
MOSS_API bool Moss_OpenURL(const char *url);
MOSS_API Moss_PowerState Moss_GetPowerInfo(int *seconds, int *percent);
/*! @brief Get Locale of the Operating system. @return Moss_Locale e.g. "UK" for United Kingdom and "en" for English. */
MOSS_API Moss_Locale* Moss_GetLocale();
/*! @brief */
MOSS_API Moss_PowerState Moss_GetPowerInfo(int *seconds, int *percent);
/*! @brief Detct if an executible is running. @param executable_path exe name - e.g. obs.exe. */
MOSS_API bool Moss_IsProcessRunningByName(const char* executable_path);
/*! @brief Loads a dynamic library from the given path. @param lib_path Path to the library file. @return Handle to the loaded library, or NULL on failure. @note The returned handle must be released using Moss_UnloadDynamicLibrary().*/
MOSS_API void* Moss_LoadDynamicLibrary(const char* lib_path);
/*! @brief Retrieves a symbol from a loaded library. @param handle Handle to the loaded library. @param symbol_name Name of the symbol to retrieve. @return Pointer to the symbol, or NULL if not found.  @return A pointer to the requested symbol, or NULL if not found.  @warning The returned pointer must be cast to the appropriate function or data type.*/
MOSS_API void* Moss_GetLibrarySymbol(void* handle, const char* symbol_name);
/*! @brief Unloads a previously loaded dynamic library. @param handle Handle to the library to unload. @note After unloading, the handle should not be used again. */
MOSS_API void Moss_UnloadDynamicLibrary(void* handle);

// =================================================
//              Callback Registration API
// =================================================
/*! @brief Sets the framebuffer resize callback. @param callback Pointer to a function to be invoked when framebuffer size changes. @ingroup Window */
MOSS_API void Moss_SetFramebufferResizeCallback(Moss_FramebufferResizeCallback callback);
/*! @brief Sets the window size callback. @param callback Pointer to a function invoked when the window size changes. @ingroup Window */
MOSS_API void Moss_SetWindowSizeCallback(Moss_WindowSizeCallback callback);
/*! @brief Sets the window resize callback (platform-level, e.g. minimize/maximize). @param callback Pointer to a function invoked when window resizing events occur. @ingroup Window */
MOSS_API void Moss_SetWindowResizeCallback(Moss_WindowResizeCallback callback);
/*! @brief Sets the window position callback. @param callback Pointer to a function invoked when the window position changes. @ingroup Window */
MOSS_API void Moss_SetWindowPositionCallback(Moss_WindowPositionCallback callback);
/*! @brief Sets the window focus callback. @param callback Pointer to a function invoked when the window focus changes. @ingroup Window */
MOSS_API void Moss_SetWindowFocusCallback(Moss_WindowFocusCallback callback);
/*! @brief Sets the window content scale callback (for HiDPI / Retina support). @param callback Pointer to a function invoked when the content scale changes. @ingroup Window */
MOSS_API void Moss_SetWindowContentScaleCallback(Moss_WindowContentScaleCallback callback);
/*! @brief Sets the monitor connection or configuration callback. @param callback Pointer to a function invoked when a monitor is connected or disconnected. @ingroup Monitor */
MOSS_API void Moss_SetMonitorCallback(Moss_MonitorCallback callback);



enum class Moss_CameraPermissionState { DENIED = -1, PENDING, APPROVED };
enum class Moss_CameraPosition { UNKNOWN, FRONT_FACING, BACK_FACING };

typedef struct Moss_Camera Moss_Camera; // Camera Device Dont use as the rendering camera

struct Moss_CameraSpec {
    PixelFormat format;         // Frame format
    Colorspace colorspace;      // Frame colorspace
    int width;                  // Frame width
    int height;                 // Frame height
    int framerate_numerator;    // Frame rate numerator ((num / denom) == FPS, (denom / num) == duration in seconds)
    int framerate_denominator;  // Frame rate demoninator ((num / denom) == FPS, (denom / num) == duration in seconds)
} Moss_CameraSpec;

MOSS_API Moss_CameraID* Moss_GetCameras(int* count);
/* Returned array valid until next call or shutdown */

MOSS_API const char* Moss_GetCameraName(Moss_CameraID camera_id);
MOSS_API Moss_CameraPosition Moss_GetCameraPosition(Moss_CameraID camera_id);
MOSS_API const char* Moss_GetCurrentCameraDriver(void);
MOSS_API int Moss_GetNumCameraDrivers(void);
MOSS_API const Moss_CameraSpec* Moss_GetCameraSupportedFormats(Moss_CameraID camera_id, int* count);
MOSS_API Moss_Surface* Moss_AcquireCameraFrame(Moss_Camera* camera, uint64_t* timestamp_ns);
MOSS_API void Moss_ReleaseCameraFrame(Moss_Camera* camera, Moss_Surface* frame);
MOSS_API bool Moss_GetCameraFormat(Moss_Camera* camera, Moss_CameraSpec* out_spec);
MOSS_API Moss_CameraPermissionState Moss_GetCameraPermissionState(Moss_Camera* camera);
MOSS_API Moss_PropertiesID Moss_GetCameraProperties(Moss_Camera* camera);
MOSS_API void Moss_CloseCamera(Moss_Camera *camera);
MOSS_API Moss_CameraID Moss_GetCameraID(Moss_Camera *camera);
MOSS_API Moss_PropertiesID Moss_GetCameraProperties(Moss_Camera *camera);
MOSS_API Moss_Camera * Moss_OpenCamera(Moss_CameraID instance_id, const Moss_CameraSpec *spec);


/*! @brief X. @param X X @ingroup Video Capture. */
MOSS_API Moss_VideoCapture* Moss_OpenVideoCapture(Moss_VideoCaptureID captureID);
/*! @brief X. @param X X @ingroup Video Capture. */
MOSS_API void Moss_CloseVideoCapture(Moss_VideoCapture* cap);
/*! @brief X. @param X X @ingroup Video Capture. */
MOSS_API uint8_t* Moss_VideoCaptureReadFrame(Moss_VideoCapture* cap);



MOSS_API bool Moss_CopyFile(const char* src_path, const char* dst_path, bool overwrite);
MOSS_API bool Moss_CreateDirectory(const char* path, bool recursive);
MOSS_API bool Moss_RemovePath(const char* path, bool recursive);
MOSS_API bool Moss_RenamePath(const char* old_path, const char* new_path, bool overwrite);


MOSS_API bool Moss_GetPathInfo(const char* path, Moss_PathInfo* out_info);
MOSS_API bool Moss_GetCurrentDirectory(char* out_path, int max_len);
MOSS_API bool Moss_GetBasePath(char* out_path, int max_len);


typedef enum Moss_UserFolder {
    MOSS_USER_FOLDER_HOME,
    MOSS_USER_FOLDER_DESKTOP,
    MOSS_USER_FOLDER_DOCUMENTS,
    MOSS_USER_FOLDER_DOWNLOADS,
    MOSS_USER_FOLDER_PICTURES,
    MOSS_USER_FOLDER_MUSIC,
    MOSS_USER_FOLDER_VIDEOS,
    MOSS_USER_FOLDER_APPDATA,
    MOSS_USER_FOLDER_CACHE
} Moss_UserFolder;


MOSS_API bool Moss_GetUserFolder(Moss_UserFolder folder, char* out_path, int max_len);
MOSS_API bool Moss_GetPrefPath(const char* org_name, const char* app_name, char* out_path, int max_len);
MOSS_API bool Moss_EnumerateDirectory( const char* path, bool recursive, Moss_DirectoryIterateFn callback, void* user_data);
MOSS_API bool Moss_GlobDirectory(const char* pattern, Moss_DirectoryIterateFn callback, void* user_data);


MOSS_API void Moss_ShowFileDialogWithProperties(Moss_DialogFileCallback callback, void *userdata, Moss_Window *window, const Moss_DialogFileFilter *filters, int nfilters, const char *default_location);
MOSS_API void Moss_ShowOpenFileDialog(Moss_DialogFileCallback callback, void *userdata, Moss_Window *window, const char *default_location, bool allow_many);
MOSS_API void Moss_ShowOpenFolderDialog(Moss_DialogFileCallback callback, void *userdata, Moss_Window *window, const Moss_DialogFileFilter *filters, int nfilters, const char *default_location, bool allow_many);
MOSS_API void Moss_ShowSaveFileDialog(Moss_FileDialogType type, Moss_DialogFileCallback callback, void *userdata, Moss_PropertiesID props);

MOSS_API bool Moss_CloseStorage(Moss_Storage *storage);
MOSS_API bool Moss_CopyStorageFile(Moss_Storage *storage, const char *oldpath, const char *newpath);
MOSS_API bool Moss_CreateStorageDirectory(Moss_Storage *storage, const char *path);
MOSS_API bool Moss_EnumerateStorageDirectory(Moss_Storage *storage, const char *path, Moss_EnumerateDirectoryCallback callback, void *userdata);
MOSS_API bool Moss_GetStorageFileSize(Moss_Storage *storage, const char *path, uint64 *length);
MOSS_API uint64 Moss_GetStorageSpaceRemaining(Moss_Storage *storage);
MOSS_API bool Moss_GetStoragePathInfo(Moss_Storage *storage, const char *path, Moss_PathInfo *info);
MOSS_API char** Moss_GlobStorageDirectory(Moss_Storage *storage, const char *path, const char *pattern, Moss_GlobFlags flags, int *count);
MOSS_API Moss_Storage* Moss_OpenFileStorage(const char *path);
MOSS_API Moss_Storage* Moss_OpenStorage(const Moss_Storage *iface, void *userdata);
MOSS_API Moss_Storage* Moss_OpenTitleStorage(const char *override, Moss_PropertiesID props);
MOSS_API Moss_Storage* Moss_OpenUserStorage(const char *org, const char *app, Moss_PropertiesID props);
MOSS_API bool Moss_ReadStorageFile(Moss_Storage *storage, const char *path, void *destination, uint64 length);
MOSS_API bool Moss_RemoveStoragePath(Moss_Storage *storage, const char *path);
MOSS_API bool Moss_RenameStoragePath(Moss_Storage *storage, const char *oldpath, const char *newpath);
MOSS_API bool Moss_StorageReady(Moss_Storage *storage);
MOSS_API bool Moss_WriteStorageFile(Moss_Storage *storage, const char *path, const void *source, uint64 length);


// OpenGL / OpenGL-ES
#if defined(MOSS_GRAPHICS_OPENGL) || defined(MOSS_GRAPHICS_OPENGLES)
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
#if defined(MOSS_GRAPHICS_VULKAN)
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

// Metal
#if defined(MOSS_GRAPHICS_METAL)
typedef void *Moss_MetalView;
MOSS_API Moss_MetalView Moss_Metal_CreateView(Moss_Window *window);
MOSS_API void Moss_Metal_DestroyView(Moss_MetalView view);
MOSS_API void* Moss_Metal_GetLayer(Moss_MetalView view);
MOSS_API void Moss_Metal_Resize(Moss_MetalView handle, uint32_t width, uint32_t height);

#endif // MOSS_PLATFORM_H












