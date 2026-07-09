# Platform

## Overview

The Platform module provides cross-platform abstraction for window management, input handling, monitors, and system integration.

Supported platforms: **Windows**, **Linux**, **macOS**, **FreeBSD**, **Android**, **iOS**

> [!NOTE]  
> For VR vendors or other platforms not listed, manual integration may be required.

## Platform Support Matrix

### Operating Systems
| Feature | Windows | macOS | Linux | iOS | Android |
| --- | --- | --- | --- | --- | --- |
| Window Management | ✅ | ✅ | ✅ | ✅ | ✅ |
| Keyboard/Mouse | ✅ | ✅ | ✅ | ❌ | ❌ |
| Touch Input | ❌ | ❌ | ❌ | ✅ | ✅ |
| Haptic Feedback | ✅ | ✅ | ✅ | ✅ | ✅ |
| Gamepads | ✅ | ✅ | ✅ | ❌ | ❌ |

### Input Device Support
| Device | Windows | macOS | Linux | iOS | Android |
| --- | --- | --- | --- | --- | --- |
| Keyboard | ✅ | ✅ | ✅ | ❌ | ❌ |
| Mouse | ✅ | ✅ | ✅ | ❌ | ❌ |
| Touch | ❌ | ❌ | ❌ | ✅ | ✅ |
| Stylus/Pen | ✅ | ✅ | ✅ | ✅ | ✅ |
| Xbox 360 Controller | ✅ | ✅ | ✅ | ❌ | ❌ |
| Xbox One Controller | ✅ | ✅ | ✅ | ❌ | ❌ |
| PlayStation 4 Controller | ✅ | ✅ | ✅ | ❌ | ❌ |
| PlayStation 5 Controller | ✅ | ✅ | ✅ | ❌ | ❌ |

### Haptic Feedback Support
| Feature | DualSense | Xbox Series | Mouse | iOS | Android |
| --- | --- | --- | --- | --- | --- |
| Haptic Feedback | ✅ | ✅ | ❌ | ✅ | ✅ |
| Trigger Feedback | ✅ | ✅ | ❌ | ❌ | ❌ |

### Graphics API Support
| Platform | Recommended APIs |
| --- | --- |
| Windows | DirectX 12, Vulkan, OpenGL |
| macOS | Metal, Vulkan |
| Linux | Vulkan, OpenGL |
| iOS | Metal, OpenGL ES |
| Android | Vulkan, OpenGL ES |

## Macros

```c
// Platform Detection
#define MOSS_PLATFORM_WINDOWS
#define MOSS_PLATFORM_LINUX
#define MOSS_PLATFORM_MACOS
#define MOSS_PLATFORM_IOS
#define MOSS_PLATFORM_ANDROID
#define MOSS_PLATFORM_XBOX
#define MOSS_PLATFORM_PLAYSTATION
```

## Enums

```c
enum Moss_WindowMode { WINDOWED, FULLSCREEN, BORDERLESS };
enum Moss_CursorMode { NORMAL, HIDDEN, DISABLED };
enum Moss_CursorShape { ARROW, HAND, CROSSHAIR, TEXT, WAIT };
enum InputEventType { INPUT_KEY, INPUT_MOUSE, INPUT_GAMEPAD, INPUT_TOUCH };
```

## Structs

```c
struct Moss_Window { /* opaque */ };
struct Moss_Monitor { /* opaque */ };
struct Moss_Event { InputEventType type; /* ... */ };
struct Moss_Locale {
    const char* language;   // "en", "de", etc.
    const char* country;    // "US", "DE", etc.
};
```

## Functions

### Window Management

```c
// Create a new window
Moss_Window* Moss_CreateWindow(const char* title);

// Check if window should close
bool Moss_ShouldWindowClose(Moss_Window* window);

// Check if window is currently running
bool Moss_IsWindowRunning(Moss_Window* window);

// Terminate window and clean up resources
void Moss_TerminateWindow(Moss_Window* window);

// Get window dimensions
void Moss_GetWindowSize(Moss_Window* window, int* width, int* height);

// Set window dimensions
void Moss_SetWindowSize(Moss_Window* window, int width, int height);

// Get window position on screen
void Moss_GetWindowPosition(Moss_Window* window, int* x, int* y);

// Set window title
void Moss_SetWindowTitle(Moss_Window* window, const char* title);
```

### Event Handling

```c
// Poll all pending events
void Moss_PollEvents(void);

// Get next event (blocking)
bool Moss_GetNextEvent(Moss_Event* event);

// Process event callback
typedef void (*EventCallback)(const Moss_Event* event);
void Moss_SetEventCallback(EventCallback callback);
```

### Monitor Detection

```c
// Get monitor at index
Moss_Monitor Moss_GetMonitor(int index);

// Get primary monitor
Moss_Monitor Moss_GetPrimaryMonitor(void);

// Count available monitors
int Moss_GetMonitorCount(void);

// Get monitor name
const char* Moss_GetMonitorName(Moss_Monitor monitor);

// Get monitor position in virtual space
void Moss_GetMonitorPosition(Moss_Monitor monitor, int* x, int* y);

// Get monitor dimensions in millimeters
void Moss_GetMonitorPhysicalSize(Moss_Monitor monitor, int* width_mm, int* height_mm);

// Get DPI scaling
void Moss_GetMonitorContentScale(Moss_Monitor monitor, float* xscale, float* yscale);

// Get current refresh rate
int Moss_GetMonitorRefreshRate(Moss_Monitor monitor);
```

### Input Handling

```c
// Keyboard input
bool Moss_IsKeyPressed(int key);
bool Moss_IsKeyReleased(int key);
bool Moss_IsKeyJustPressed(int key);
bool Moss_IsKeyJustReleased(int key);

// Mouse input
bool Moss_IsMouseButtonPressed(int button);
bool Moss_IsMouseButtonReleased(int button);
bool Moss_IsMouseButtonJustPressed(int button);
float Moss_GetMouseX(void);
float Moss_GetMouseY(void);
void Moss_GetMousePosition(float* x, float* y);
void Moss_SetMousePosition(float x, float y);

// Gamepad input
bool Moss_IsGamepadConnected(int gamepad_id);
bool Moss_IsGamepadButtonPressed(int gamepad_id, int button);
float Moss_GetGamepadAxis(int gamepad_id, int axis);

// Touch input (Mobile)
int Moss_GetTouchCount(void);
void Moss_GetTouchPosition(int touch_id, float* x, float* y);
float Moss_GetTouchPressure(int touch_id);
```

### Cursor Management

```c
// Set cursor mode (visible, hidden, disabled)
void Moss_SetCursorMode(Moss_CursorMode mode);

// Set cursor shape
void Moss_SetCursorShape(Moss_CursorShape shape);

// Show/hide cursor
void Moss_ShowCursor(bool show);
```

### Haptic Feedback

```c
// Play haptic feedback on a device
void Moss_PlayHapticFeedback(int device_id, float intensity, float duration);

// Set trigger feedback (Xbox/DualSense)
void Moss_SetTriggerFeedback(int device_id, float left_intensity, float right_intensity);
```

### Graphics API Specific

#### OpenGL

```c
// Make OpenGL context current
void Moss_MakeContextCurrent(Moss_Window* window);

// Swap front/back buffers
void Moss_SwapBuffers(Moss_Window* window);

// Set V-Sync interval (0 = off, 1 = on)
void Moss_SwapBuffersInterval(int interval);

// Get OpenGL function pointer
void* Moss_GetProcAddress(const char* procname);
```

#### Vulkan

```c
// Create Vulkan surface for window
VkResult Moss_CreateWindowSurface(Moss_Window* window, VkInstance instance,
                                   const VkAllocationCallbacks* allocator,
                                   VkSurfaceKHR* surface);

// Check if Vulkan is supported
int Moss_VulkanSupported(void);

// Initialize Vulkan loader
void Moss_InitVulkanLoader(PFN_vkGetInstanceProcAddr loader);

// Get required instance extensions for window surface
const char** Moss_GetRequiredInstanceExtensions(uint32_t* count);

// Get Vulkan instance function
void* Moss_GetInstanceProcAddress(VkInstance instance, const char* procname);

// Check if device can present to window
int Moss_GetPhysicalDevicePresentationSupport(Moss_Window* window,
                                              VkPhysicalDevice device,
                                              uint32_t queue_family);
```

### System Information

```c
// Get system locale
struct Moss_Locale* Moss_GetLocale(void);

// Get number of CPU cores
int Moss_GetCPUCount(void);

// Get system RAM in bytes
uint64_t Moss_GetSystemMemory(void);

// Open URL in default browser
bool Moss_OpenURL(const char* url);
```

## Examples

### Creating and Managing a Window

```c
#include <Moss.h>

int main() {
    // Initialize Moss
    if (!Moss_Init()) {
        return 1;
    }

    // Create window
    Moss_Window* window = Moss_CreateWindow("My Moss Application");
    if (!window) {
        Moss_Terminate();
        return 1;
    }

    // Main loop
    while (!Moss_ShouldWindowClose(window)) {
        // Poll events
        Moss_PollEvents();

        // Handle input
        if (Moss_IsKeyJustPressed(KEY_ESCAPE)) {
            break;  // Exit on ESC
        }

        // Update and render (your code here)
        // ...
    }

    // Cleanup
    Moss_TerminateWindow(window);
    Moss_Terminate();
    return 0;
}
```

### Handling Input Events

```c
void HandleEvents() {
    // Check keyboard
    if (Moss_IsKeyPressed(KEY_W)) {
        // Move forward
    }

    // Check mouse
    float mouse_x, mouse_y;
    Moss_GetMousePosition(&mouse_x, &mouse_y);

    if (Moss_IsMouseButtonJustPressed(MOUSE_BUTTON_LEFT)) {
        // Fire weapon at mouse_x, mouse_y
    }

    // Check gamepad
    if (Moss_IsGamepadConnected(0)) {
        float lx = Moss_GetGamepadAxis(0, GAMEPAD_AXIS_LX);
        float ly = Moss_GetGamepadAxis(0, GAMEPAD_AXIS_LY);
        // Use analog stick input
    }
}
```

### Monitor Detection

```c
void PrintMonitorInfo() {
    int count = Moss_GetMonitorCount();
    printf("Connected monitors: %d\n", count);

    for (int i = 0; i < count; i++) {
        Moss_Monitor monitor = Moss_GetMonitor(i);
        const char* name = Moss_GetMonitorName(monitor);
        int x, y;
        Moss_GetMonitorPosition(monitor, &x, &y);
        
        printf("Monitor %d: %s at (%d, %d)\n", i, name, x, y);
    }
}
```

### Haptic Feedback

```c
void PlayGamepadVibration() {
    if (Moss_IsGamepadConnected(0)) {
        // Vibrate gamepad with 80% intensity for 100ms
        Moss_PlayHapticFeedback(0, 0.8f, 0.1f);
    }
}
```
