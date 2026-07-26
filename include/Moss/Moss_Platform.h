//                        MIT License
//
//                  Copyright (c) 2026 Toby
//
#ifndef MOSS_PLATFORM_H
#define MOSS_PLATFORM_H

#include <Moss/Moss_stdinc.h>

#if defined(MOSS_USE_VULKAN) || defined(MOSS_GRAPHICS_VULKAN)
#include <vulkan/vulkan.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef uint16 Moss_Key;
typedef uint8 Moss_MouseButton;
typedef uint8 Moss_JoystickAxis;
typedef uint8 Moss_GamepadAxis;
typedef uint8 Moss_GamepadButton;
typedef uint16 Moss_Keycode;
typedef uint16 Moss_Keymod;
typedef uint16 Moss_HapticEffectType;
typedef int Moss_HapticEffectID;
typedef uint32 Moss_FingerID;
typedef uint32 Moss_TouchID;
typedef uint32 Moss_HapticID;
typedef uint32 Moss_CameraID;
typedef uint32 Moss_MonitorID;
typedef uint32 Moss_KeyboardID;
typedef uint32 Moss_JoystickID;
typedef uint32 Moss_GamepadID;
typedef uint32 Moss_VideoCaptureID;
typedef uint64 Moss_Time;
typedef uint64 Moss_PropertiesID;

typedef struct Moss_Window Moss_Window;
typedef struct Moss_Monitor Moss_Monitor;
typedef struct Moss_Cursor Moss_Cursor;
typedef struct Moss_GamepadBinding Moss_GamepadBinding;
typedef struct Moss_Gamepad Moss_Gamepad;
typedef struct Moss_Joystick Moss_Joystick;
typedef struct Moss_Haptic Moss_Haptic;
typedef struct Moss_VideoCapture Moss_VideoCapture;
typedef struct Moss_Touchscreen Moss_Touchscreen;
typedef struct Moss_Pen Moss_Pen;
typedef struct Moss_Camera Moss_Camera;
typedef struct Moss_Surface Moss_Surface;
typedef struct Moss_Storage Moss_Storage;

typedef struct Moss_GammaRamp { int size; uint16* red; uint16* green; uint16* blue; } Moss_GammaRamp;
typedef struct Moss_VideoMode { int width, height, redBits, greenBits, blueBits, refreshRate; } Moss_VideoMode;
typedef struct Moss_Image { int width; int height; unsigned char* pixels; } Moss_Image;
typedef struct Moss_Locale { char* country; char* language; } Moss_Locale;

typedef enum Moss_WindowFlags {
    MOSS_WINDOW_NONE = 0,
    MOSS_WINDOW_NOTITLEBAR = 0x00000001,
    MOSS_WINDOW_OPENGL = 0x00000002,
    MOSS_WINDOW_SHOWN = 0x00000004,
    MOSS_WINDOW_HIDDEN = 0x00000008,
    MOSS_WINDOW_BORDERLESS = 0x00000010,
    MOSS_WINDOW_RESIZABLE = 0x00000020,
    MOSS_WINDOW_MINIMIZED = 0x00000040,
    MOSS_WINDOW_MAXIMIZED = 0x00000080,
    MOSS_WINDOW_MOUSE_GRABBED = 0x00000100,
    MOSS_WINDOW_INPUT_FOCUS = 0x00000200,
    MOSS_WINDOW_MOUSE_FOCUS = 0x00000400,
    MOSS_WINDOW_FOREIGN = 0x00000800,
    MOSS_WINDOW_ALLOW_HIGHDPI = 0x00002000,
    MOSS_WINDOW_ALWAYS_ON_TOP = 0x00008000,
    MOSS_WINDOW_SKIP_TASKBAR = 0x00010000,
    MOSS_WINDOW_UTILITY = 0x00020000,
    MOSS_WINDOW_TOOLTIP = 0x00040000,
    MOSS_WINDOW_POPUP_MENU = 0x00080000,
    MOSS_WINDOW_KEYBOARD_GRABBED = 0x00100000,
    MOSS_WINDOW_VULKAN = 0x10000000,
    MOSS_WINDOW_METAL = 0x20000000,
    MOSS_WINDOW_INPUT_GRABBED = MOSS_WINDOW_MOUSE_GRABBED
} Moss_WindowFlags;

typedef enum Moss_MessageBoxFlags {
    MOSS_MESSAGEBOX_ABORT_RETRY_IGNORE,
    MOSS_MESSAGEBOX_CANCEL_TRY_CONTINUE,
    MOSS_MESSAGEBOX_HELP,
    MOSS_MESSAGEBOX_OK,
    MOSS_MESSAGEBOX_OK_CANCEL,
    MOSS_MESSAGEBOX_RETRY_CANCEL,
    MOSS_MESSAGEBOX_YES_NO,
    MOSS_MESSAGEBOX_YES_NO_CANCEL
} Moss_MessageBoxFlags;

typedef enum Moss_WindowMode { MOSS_WINDOWMODE_WINDOWED, MOSS_WINDOWMODE_MINIMIZED, MOSS_WINDOWMODE_MAXIMIZED, MOSS_WINDOWMODE_FULLSCREEN, MOSS_WINDOWMODE_EXCLUSIVE_FULLSCREEN } Moss_WindowMode;
typedef enum Moss_CursorMode { MOSS_CURSOR_VISIBLE, MOSS_CURSOR_HIDDEN, MOSS_CURSOR_CAPTURED, MOSS_CURSOR_CONFINED, MOSS_CURSOR_CONFINED_HIDDEN } Moss_CursorMode;
typedef enum Moss_CursorShape { MOSS_CURSOR_ARROW, MOSS_CURSOR_IBEAM, MOSS_CURSOR_POINTING_HAND, MOSS_CURSOR_CROSS, MOSS_CURSOR_WAIT, MOSS_CURSOR_BUSY, MOSS_CURSOR_DRAG, MOSS_CURSOR_CAN_DROP, MOSS_CURSOR_FORBIDDEN, MOSS_CURSOR_VSIZE, MOSS_CURSOR_HSIZE, MOSS_CURSOR_BDIAGSIZE, MOSS_CURSOR_FDIAGSIZE, MOSS_CURSOR_MOVE, MOSS_CURSOR_VSPLIT, MOSS_CURSOR_HSPLIT, MOSS_CURSOR_HELP } Moss_CursorShape;
typedef enum Moss_PowerState { MOSS_POWERSTATE_UNKNOWN, MOSS_POWERSTATE_ON_BATTERY, MOSS_POWERSTATE_NO_BATTERY, MOSS_POWERSTATE_CHARGING, MOSS_POWERSTATE_CHARGED } Moss_PowerState;
typedef enum Moss_CameraPermissionState { MOSS_CAMERA_PERMISSION_DENIED = -1, MOSS_CAMERA_PERMISSION_PENDING = 0, MOSS_CAMERA_PERMISSION_APPROVED = 1 } Moss_CameraPermissionState;
typedef enum Moss_CameraPosition { MOSS_CAMERA_POSITION_UNKNOWN, MOSS_CAMERA_POSITION_FRONT_FACING, MOSS_CAMERA_POSITION_BACK_FACING } Moss_CameraPosition;
typedef enum Moss_TouchDeviceType { MOSS_TOUCH_DEVICE_UNKNOWN, MOSS_TOUCH_DEVICE_DIRECT, MOSS_TOUCH_DEVICE_INDIRECT } Moss_TouchDeviceType;
typedef enum Moss_PenDeviceType { MOSS_PEN_DEVICE_UNKNOWN, MOSS_PEN_DEVICE_PEN, MOSS_PEN_DEVICE_ERASER } Moss_PenDeviceType;
typedef enum Moss_FileDialogType { MOSS_FILE_DIALOG_OPEN, MOSS_FILE_DIALOG_SAVE, MOSS_FILE_DIALOG_FOLDER } Moss_FileDialogType;
typedef enum Moss_GlobFlags { MOSS_GLOB_NONE = 0, MOSS_GLOB_CASE_INSENSITIVE = 1 } Moss_GlobFlags;
typedef enum Moss_UserFolder { MOSS_USER_FOLDER_HOME, MOSS_USER_FOLDER_DESKTOP, MOSS_USER_FOLDER_DOCUMENTS, MOSS_USER_FOLDER_DOWNLOADS, MOSS_USER_FOLDER_PICTURES, MOSS_USER_FOLDER_MUSIC, MOSS_USER_FOLDER_VIDEOS, MOSS_USER_FOLDER_APPDATA, MOSS_USER_FOLDER_CACHE } Moss_UserFolder;

typedef struct Moss_PathInfo { uint64 size; bool is_file; bool is_directory; uint64 modified_time; } Moss_PathInfo;
typedef struct Moss_DialogFileFilter { const char* name; const char* pattern; } Moss_DialogFileFilter;
typedef struct Moss_CameraSpec { int format; int colorspace; int width; int height; int framerate_numerator; int framerate_denominator; } Moss_CameraSpec;
typedef struct Moss_Finger { Moss_FingerID id; float x; float y; float pressure; } Moss_Finger;

typedef void (*Moss_FramebufferResizeCallback)(int width, int height);
typedef void (*Moss_WindowSizeCallback)(int width, int height);
typedef void (*Moss_WindowPositionCallback)(int xpos, int ypos);
typedef void (*Moss_WindowFocusCallback)(bool focused);
typedef void (*Moss_WindowContentScaleCallback)(float xscale, float yscale);
typedef void (*Moss_WindowResizeCallback)(int width, int height);
typedef void (*Moss_MonitorCallback)(const char* monitorName, bool connected);
typedef void (MOSS_CALL* Moss_DialogFileCallback)(void* userdata, const char* const* filelist, int filter);
typedef bool (*Moss_DirectoryIterateFn)(const Moss_PathInfo* info, const char* path, void* user_data);
typedef bool (*Moss_EnumerateDirectoryCallback)(void* userdata, const char* dirname, const char* fname);

MOSS_API Moss_Window* Moss_CreateWindow(const char* title, int width, int height, Moss_Monitor* monitor, Moss_Window* share);
MOSS_API void Moss_TerminateWindow(Moss_Window* window);
MOSS_API bool Moss_CreateMessageBox(const char* title, const char* message, Moss_MessageBoxFlags flags, Moss_Window* window);
MOSS_API bool Moss_ShouldWindowClose(Moss_Window* window);
MOSS_API void Moss_PollEvents(void);
MOSS_API int Moss_GetWindowWidth(void);
MOSS_API int Moss_GetWindowHeight(void);
MOSS_API void Moss_SetWindowTitle(Moss_Window* window, const char* title);
MOSS_API void Moss_SetWindowIcon(Moss_Window* window, Moss_Image image);
MOSS_API void Moss_CloseWindow(Moss_Window* window);

MOSS_API Moss_Monitor* Moss_MonitorGetPrimary(void);
MOSS_API Moss_Monitor* Moss_MonitorGetSecondary(void);
MOSS_API void Moss_MonitorGetPhysicalSize(Moss_Monitor* monitor, int* width_mm, int* height_mm);
MOSS_API void Moss_MonitorGetContentScale(Moss_Monitor* monitor, float* xscale, float* yscale);
MOSS_API void Moss_MonitorGetPosition(Moss_Monitor* monitor, int* x, int* y);
MOSS_API const char* Moss_MonitorGetName(Moss_Monitor* monitor);
MOSS_API void Moss_MonitorSetGammaRamp(Moss_Monitor* monitor, const Moss_GammaRamp* gammaRamp);
MOSS_API Moss_GammaRamp* Moss_MonitorGetGammaRamp(Moss_Monitor* monitor);
MOSS_API void Moss_MonitorSetGamma(Moss_Monitor* monitor, float gamma);

MOSS_API bool Moss_IsKeyPressed(Moss_Key key);
MOSS_API bool Moss_IsKeyJustPressed(Moss_Key key);
MOSS_API bool Moss_IsKeyJustReleased(Moss_Key key);
MOSS_API bool Moss_IsMousePressed(Moss_MouseButton button);
MOSS_API bool Moss_IsMouseJustPressed(Moss_MouseButton button);
MOSS_API bool Moss_IsMouseJustReleased(Moss_MouseButton button);
MOSS_API void Moss_GetMousePosition(int* x, int* y);
MOSS_API void Moss_SetMousePosition(int x, int y);
MOSS_API void Moss_SetMouseVisible(bool visible);

MOSS_API int Moss_GetNumGamepads(void);
MOSS_API Moss_Gamepad* Moss_OpenGamepad(Moss_GamepadID id);
MOSS_API void Moss_CloseGamepad(Moss_Gamepad* gp);
MOSS_API bool Moss_GamepadConnected(Moss_Gamepad* gp);
MOSS_API void Moss_UpdateGamepads(void);
MOSS_API bool Moss_IsGamepadButtonPressed(Moss_Gamepad* gp, Moss_GamepadButton button);
MOSS_API bool Moss_IsGamepadButtonJustPressed(Moss_Gamepad* gp, Moss_GamepadButton button);
MOSS_API bool Moss_IsGamepadButtonJustReleased(Moss_Gamepad* gp, Moss_GamepadButton button);
MOSS_API float Moss_GetGamepadAxis(Moss_Gamepad* gp, Moss_GamepadAxis axis);
MOSS_API bool Moss_RumbleGamepad(Moss_Gamepad* gp, uint16 low, uint16 high, uint32 duration_ms);
MOSS_API bool Moss_RumbleGamepadTriggers(Moss_Gamepad* gp, uint16 left, uint16 right, uint32 duration_ms);
MOSS_API bool Moss_SetGamepadLED(Moss_Gamepad* gp, uint8 r, uint8 g, uint8 b);
MOSS_API const char* Moss_GetGamepadName(Moss_Gamepad* gp);
MOSS_API Moss_GamepadID Moss_GetGamepadID(Moss_Gamepad* gp);
MOSS_API int Moss_GetGamepadPlayerIndex(Moss_Gamepad* gp);
MOSS_API Moss_PowerState Moss_GetGamepadPowerInfo(Moss_Gamepad* gp, int* percent);

MOSS_API int Moss_GetAvailableCPUCores(void);
MOSS_API int Moss_GetCPUCacheLineSize(void);
MOSS_API int Moss_GetSystemRAM(void);
MOSS_API bool Moss_OpenURL(const char* url);
MOSS_API Moss_PowerState Moss_GetPowerInfo(int* seconds, int* percent);
MOSS_API Moss_Locale* Moss_GetLocale(void);
MOSS_API bool Moss_IsProcessRunningByName(const char* executable_path);
MOSS_API void* Moss_LoadDynamicLibrary(const char* lib_path);
MOSS_API void* Moss_GetLibrarySymbol(void* handle, const char* symbol_name);
MOSS_API void Moss_UnloadDynamicLibrary(void* handle);

MOSS_API void Moss_SetFramebufferResizeCallback(Moss_FramebufferResizeCallback callback);
MOSS_API void Moss_SetWindowSizeCallback(Moss_WindowSizeCallback callback);
MOSS_API void Moss_SetWindowResizeCallback(Moss_WindowResizeCallback callback);
MOSS_API void Moss_SetWindowPositionCallback(Moss_WindowPositionCallback callback);
MOSS_API void Moss_SetWindowFocusCallback(Moss_WindowFocusCallback callback);
MOSS_API void Moss_SetWindowContentScaleCallback(Moss_WindowContentScaleCallback callback);
MOSS_API void Moss_SetMonitorCallback(Moss_MonitorCallback callback);

MOSS_API Moss_CameraID* Moss_GetCameras(int* count);
MOSS_API const char* Moss_GetCameraName(Moss_CameraID camera_id);
MOSS_API Moss_CameraPosition Moss_GetCameraPosition(Moss_CameraID camera_id);
MOSS_API const char* Moss_GetCurrentCameraDriver(void);
MOSS_API int Moss_GetNumCameraDrivers(void);
MOSS_API const Moss_CameraSpec* Moss_GetCameraSupportedFormats(Moss_CameraID camera_id, int* count);
MOSS_API Moss_Surface* Moss_AcquireCameraFrame(Moss_Camera* camera, uint64* timestamp_ns);
MOSS_API void Moss_ReleaseCameraFrame(Moss_Camera* camera, Moss_Surface* frame);
MOSS_API bool Moss_GetCameraFormat(Moss_Camera* camera, Moss_CameraSpec* out_spec);
MOSS_API Moss_CameraPermissionState Moss_GetCameraPermissionState(Moss_Camera* camera);
MOSS_API Moss_PropertiesID Moss_GetCameraProperties(Moss_Camera* camera);
MOSS_API void Moss_CloseCamera(Moss_Camera* camera);
MOSS_API Moss_CameraID Moss_GetCameraID(Moss_Camera* camera);
MOSS_API Moss_Camera* Moss_OpenCamera(Moss_CameraID instance_id, const Moss_CameraSpec* spec);

MOSS_API Moss_VideoCapture* Moss_OpenVideoCapture(Moss_VideoCaptureID captureID);
MOSS_API void Moss_CloseVideoCapture(Moss_VideoCapture* cap);
MOSS_API uint8* Moss_VideoCaptureReadFrame(Moss_VideoCapture* cap);

MOSS_API bool Moss_CopyFile(const char* src_path, const char* dst_path, bool overwrite);
MOSS_API bool Moss_CreateDirectory(const char* path, bool recursive);
MOSS_API bool Moss_RemovePath(const char* path, bool recursive);
MOSS_API bool Moss_RenamePath(const char* old_path, const char* new_path, bool overwrite);
MOSS_API bool Moss_GetPathInfo(const char* path, Moss_PathInfo* out_info);
MOSS_API bool Moss_GetCurrentDirectory(char* out_path, int max_len);
MOSS_API bool Moss_GetBasePath(char* out_path, int max_len);
MOSS_API bool Moss_GetUserFolder(Moss_UserFolder folder, char* out_path, int max_len);
MOSS_API bool Moss_GetPrefPath(const char* org_name, const char* app_name, char* out_path, int max_len);
MOSS_API bool Moss_EnumerateDirectory(const char* path, bool recursive, Moss_DirectoryIterateFn callback, void* user_data);
MOSS_API bool Moss_GlobDirectory(const char* pattern, Moss_DirectoryIterateFn callback, void* user_data);

MOSS_API void Moss_ShowFileDialogWithProperties(Moss_DialogFileCallback callback, void* userdata, Moss_Window* window, const Moss_DialogFileFilter* filters, int nfilters, const char* default_location);
MOSS_API void Moss_ShowOpenFileDialog(Moss_DialogFileCallback callback, void* userdata, Moss_Window* window, const char* default_location, bool allow_many);
MOSS_API void Moss_ShowOpenFolderDialog(Moss_DialogFileCallback callback, void* userdata, Moss_Window* window, const Moss_DialogFileFilter* filters, int nfilters, const char* default_location, bool allow_many);
MOSS_API void Moss_ShowSaveFileDialog(Moss_FileDialogType type, Moss_DialogFileCallback callback, void* userdata, Moss_PropertiesID props);

MOSS_API bool Moss_CloseStorage(Moss_Storage* storage);
MOSS_API bool Moss_CopyStorageFile(Moss_Storage* storage, const char* oldpath, const char* newpath);
MOSS_API bool Moss_CreateStorageDirectory(Moss_Storage* storage, const char* path);
MOSS_API bool Moss_EnumerateStorageDirectory(Moss_Storage* storage, const char* path, Moss_EnumerateDirectoryCallback callback, void* userdata);
MOSS_API bool Moss_GetStorageFileSize(Moss_Storage* storage, const char* path, uint64* length);
MOSS_API uint64 Moss_GetStorageSpaceRemaining(Moss_Storage* storage);
MOSS_API bool Moss_GetStoragePathInfo(Moss_Storage* storage, const char* path, Moss_PathInfo* info);
MOSS_API char** Moss_GlobStorageDirectory(Moss_Storage* storage, const char* path, const char* pattern, Moss_GlobFlags flags, int* count);
MOSS_API Moss_Storage* Moss_OpenFileStorage(const char* path);
MOSS_API Moss_Storage* Moss_OpenStorage(const Moss_Storage* iface, void* userdata);
MOSS_API Moss_Storage* Moss_OpenTitleStorage(const char* override_path, Moss_PropertiesID props);
MOSS_API Moss_Storage* Moss_OpenUserStorage(const char* org, const char* app, Moss_PropertiesID props);
MOSS_API bool Moss_ReadStorageFile(Moss_Storage* storage, const char* path, void* destination, uint64 length);
MOSS_API bool Moss_RemoveStoragePath(Moss_Storage* storage, const char* path);
MOSS_API bool Moss_RenameStoragePath(Moss_Storage* storage, const char* oldpath, const char* newpath);
MOSS_API bool Moss_StorageReady(Moss_Storage* storage);
MOSS_API bool Moss_WriteStorageFile(Moss_Storage* storage, const char* path, const void* source, uint64 length);

#if defined(MOSS_GRAPHICS_OPENGL) || defined(MOSS_GRAPHICS_OPENGLES)
MOSS_API void Moss_MakeContextCurrent(Moss_Window* window);
MOSS_API void Moss_SwapBuffers(void);
MOSS_API void Moss_SwapBuffersInterval(int interval);
MOSS_API void* Moss_GetProcAddress(const char* procname);
#endif

#if defined(MOSS_GRAPHICS_VULKAN)
MOSS_API VkResult Moss_CreateWindowSurface(Moss_Window* window, VkInstance vk_instance, const VkAllocationCallbacks* allocator, VkSurfaceKHR* vk_surface);
MOSS_API int Moss_VulkanSupported(void);
MOSS_API const char** Moss_GetRequiredInstanceExtensions(uint32* count);
MOSS_API void* Moss_GetInstanceProcAddress(VkInstance instance, const char* procname);
MOSS_API int Moss_GetPhysicalDevicePresentationSupport(Moss_Window* window, VkPhysicalDevice device, uint32 queuefamily);
#endif

#if defined(MOSS_GRAPHICS_METAL)
typedef void* Moss_MetalView;
MOSS_API Moss_MetalView Moss_Metal_CreateView(Moss_Window* window);
MOSS_API void Moss_Metal_DestroyView(Moss_MetalView view);
MOSS_API void* Moss_Metal_GetLayer(Moss_MetalView view);
MOSS_API void Moss_Metal_Resize(Moss_MetalView handle, uint32 width, uint32 height);
#endif

#ifdef __cplusplus
}
#endif

#endif // MOSS_PLATFORM_H
