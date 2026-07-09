# Moss Framework CheatSheet

Quick reference for common functions, macros, and types.

## Platform

### Window Management
```c
// Create and manage windows
Moss_Window* Moss_CreateWindow(const char* title);
void Moss_TerminateWindow(Moss_Window* window);
bool Moss_ShouldWindowClose(Moss_Window* window);
bool Moss_IsWindowRunning(Moss_Window* window);

// Input and events
void Moss_PollEvents(void);
void Moss_SwapBuffers(Moss_Window* window);
void Moss_SwapBuffersInterval(int interval);  // V-Sync
```

### Input
```c
// Keyboard
bool Moss_IsKeyPressed(int key);
bool Moss_IsKeyReleased(int key);
bool Moss_IsKeyJustPressed(int key);
bool Moss_IsKeyJustReleased(int key);

// Mouse
bool Moss_IsMouseButtonPressed(int button);
bool Moss_IsMouseButtonReleased(int button);
void Moss_GetMousePosition(float* x, float* y);

// Gamepad
bool Moss_IsGamepadButtonPressed(int gamepad, int button);
float Moss_GetGamepadAxis(int gamepad, int axis);
```

### Haptic Feedback
```c
void Moss_PlayHapticFeedback(int device, float intensity, float duration);
```

### Monitor & Displays
```c
Moss_Monitor* Moss_GetMonitor(int index);
int Moss_GetMonitorCount(void);
const char* Moss_GetMonitorName(Moss_Monitor monitor);
void Moss_GetMonitorPosition(Moss_Monitor monitor, int* x, int* y);
```

## Renderer

### Lifecycle
```c
Moss_Renderer* Moss_CreateRenderer(Moss_Window& window);
void Moss_RendererBeginFrame(Moss_Renderer& renderer);
void Moss_PresentRenderer(Moss_Renderer& renderer);
void Moss_TerminateRenderer(Moss_Renderer& renderer);
```

### Graphics Resources
```c
// Textures
Moss_Texture* Moss_CreateTexture(const char* path);
void Moss_DestroyTexture(Moss_Texture* texture);

// Shaders
Moss_Shader* Moss_CreateShader(const char* vertex_path, const char* fragment_path);
void Moss_DestroyShader(Moss_Shader* shader);

// Meshes
Moss_Mesh* Moss_CreateMesh(const Moss_MeshData* data);
void Moss_DestroyMesh(Moss_Mesh* mesh);

// Camera
void Moss_SetCamera3D(Moss_Camera3D* camera);
void Moss_SetCamera2D(Moss_Camera2D* camera);
```

## Audio

### System
```c
int Moss_Init_Audio(void);
void Moss_Terminate_Audio(void);
```

### Channels
```c
uint32 Moss_CreateChannel(uint32 bus_id, uint32 channel_id, float volume, void* effects);
void Moss_RemoveChannel(uint32 channel_id);
```

### Streams
```c
// 2D Audio (no position)
Moss_AudioStream2D* Moss_CreateAudioStream2D(const char* path);
void Moss_PlayAudioStream2D(Moss_AudioStream2D* stream);
void Moss_StopAudioStream2D(Moss_AudioStream2D* stream);

// 3D Audio (with position)
Moss_AudioStream3D* Moss_CreateAudioStream3D(const char* path);
void Moss_PlayAudioStream3D(Moss_AudioStream3D* stream);
void Moss_SetAudioStream3DPosition(Moss_AudioStream3D* stream, float x, float y, float z);
```

### Listeners
```c
// 2D Listener
void Moss_SetAudioListener2D(float x, float y);
struct Moss_AudioListener2D Moss_GetAudioListener2D(void);

// 3D Listener
void Moss_SetAudioListener3D(float x, float y, float z);
struct Moss_AudioListener3D Moss_GetAudioListener3D(void);
```

## Physics

### Bodies
```c
// 2D Physics
Moss_RigidBody2D* Moss_CreateRigidBody2D(float x, float y);
void Moss_SetRigidBody2DPosition(Moss_RigidBody2D* body, float x, float y);
void Moss_SetRigidBody2DVelocity(Moss_RigidBody2D* body, float vx, float vy);
void Moss_ApplyForce2D(Moss_RigidBody2D* body, float fx, float fy);

// 3D Physics
Moss_RigidBody3D* Moss_CreateRigidBody3D(float x, float y, float z);
void Moss_SetRigidBody3DPosition(Moss_RigidBody3D* body, float x, float y, float z);
void Moss_SetRigidBody3DVelocity(Moss_RigidBody3D* body, float vx, float vy, float vz);
void Moss_ApplyForce3D(Moss_RigidBody3D* body, float fx, float fy, float fz);
```

### Collision
```c
bool Moss_RigidBodyCollision2D(Moss_RigidBody2D* body_a, Moss_RigidBody2D* body_b);
bool Moss_RigidBodyCollision3D(Moss_RigidBody3D* body_a, Moss_RigidBody3D* body_b);
```

## UI

### Containers
```c
// Basic containers
Moss_Container* Moss_CreateContainer(void);
Moss_HBoxContainer* Moss_CreateHBoxContainer(void);
Moss_VBoxContainer* Moss_CreateVBoxContainer(void);

// Layout
Moss_MarginContainer* Moss_CreateMarginContainer(void);
Moss_CenterContainer* Moss_CreateCenterContainer(void);
Moss_GridContainer* Moss_CreateGridContainer(int columns);
```

### Controls
```c
// Buttons
Moss_Button* Moss_CreateButton(const char* label);
void Moss_OnButtonPressed(Moss_Button* button, void (*callback)(void));

// Text
Moss_Label* Moss_CreateLabel(const char* text);
Moss_LineEdit* Moss_CreateLineEdit(void);

// Input
Moss_Slider* Moss_CreateSlider(float min, float max);
Moss_CheckBox* Moss_CreateCheckBox(const char* label);
Moss_ProgressBar* Moss_CreateProgressBar(float min, float max);
```

## Math

### Constants
```c
#define MOSS_PI           3.14159265358979323846f
#define MOSS_TAU          6.28318530717958647693f
#define MOSS_HALF_PI      1.57079632679489661923f
#define MOSS_QUARTER_PI   0.78539816339744830962f
#define MOSS_E            2.71828182845904523536f
#define MOSS_SQRT2        1.41421356237309504880f
```

### Functions
```c
// Random
int Moss_Randi(void);
float Moss_Randf(void);
int Moss_Randi_Range(int min, int max);
float Moss_Randf_Range(float min, float max);

// Trigonometric
float Moss_Sin(float x);
float Moss_Cos(float x);
float Moss_Tan(float x);
float Moss_Atan2(float y, float x);

// Utility
float Moss_Sqrt(float x);
float Moss_Pow(float base, float exponent);
float Moss_Abs(float x);
float Moss_Floor(float x);
float Moss_Ceil(float x);
float Moss_Clamp(float value, float min, float max);
float Moss_Lerp(float a, float b, float t);
```

## Networking

### System
```c
int Moss_Init_Network(void);
void Moss_TerminateNetwork(void);
```

### Host Management
```c
ENetHost* Moss_CreateHost(ENetAddress* address, size_t peer_count, size_t channel_count);
void Moss_DestroyHost(ENetHost* host);
ENetPeer* Moss_HostConnect(ENetHost* host, ENetAddress* address);
int Moss_HostService(ENetHost* host, ENetEvent* event, uint32 timeout);
void Moss_HostFlush(ENetHost* host);
```

### Packets
```c
ENetPacket* Moss_CreatePacket(const void* data, size_t size, uint32 flags);
void Moss_DestroyPacket(ENetPacket* packet);
int Moss_PeerSend(ENetPeer* peer, uint8 channel_id, ENetPacket* packet);
```

## Data Types

### Vectors
```c
typedef struct { float x, y; } Vec2;
typedef struct { float x, y, z; } Vec3;
typedef struct { float x, y, z, w; } Vec4;
typedef struct { int x, y; } Vec2i;
typedef struct { int x, y, z; } Vec3i;
typedef struct { int x, y, z, w; } Vec4i;
```

### Matrices
```c
typedef struct { float m[4][4]; } Mat4x4;
typedef struct { float m[3][3]; } Mat3x3;
typedef struct { float m[2][2]; } Mat2x2;
```

### Geometry
```c
typedef struct { Vec3 min, max; } AABB3;
typedef struct { Vec2 min, max; } AABB2;
typedef struct { Vec2 position, size; } Rect2;
typedef struct { Vec2 position; float radius; } Circle;
```

### Collections
```c
// Template types (use with any data type)
TArray<T>      // Dynamic array
TMap<K, V>     // Hash map / dictionary
TSet<T>        // Hash set
TVector<T>     // Vector (3D) / List
TStack<T>      // Stack (LIFO)
TQueue<T>      // Queue (FIFO)
```

## Platform Macros

### Platform Detection
```c
#define MOSS_PLATFORM_WINDOWS
#define MOSS_PLATFORM_LINUX
#define MOSS_PLATFORM_MACOS
#define MOSS_PLATFORM_IOS
#define MOSS_PLATFORM_ANDROID
#define MOSS_PLATFORM_PLAYSTATION
#define MOSS_PLATFORM_XBOX
```

### Graphics APIs
```c
#define MOSS_USE_OPENGL
#define MOSS_USE_VULKAN
#define MOSS_USE_DIRECTX
#define MOSS_USE_METAL
#define MOSS_USE_OPENGLES
```

### CPU Features
```c
#define MOSS_USE_NEON      // ARM SIMD
#define MOSS_USE_SSE2      // x86 SIMD
#define MOSS_USE_AVX       // x86 Advanced Vector
#define MOSS_USE_AVX2      // x86 Advanced Vector 2
#define MOSS_USE_AVX512    // x86 Advanced Vector 512
```

## Input Keys

### Keyboard
```c
KEY_0 through KEY_9
KEY_A through KEY_Z
KEY_SPACE, KEY_ENTER, KEY_ESCAPE
KEY_BACKSPACE, KEY_DELETE, KEY_TAB
KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN
KEY_HOME, KEY_END, KEY_PAGE_UP, KEY_PAGE_DOWN
KEY_F1 through KEY_F24
KEY_LEFT_SHIFT, KEY_LEFT_CONTROL, KEY_LEFT_ALT
KEY_RIGHT_SHIFT, KEY_RIGHT_CONTROL, KEY_RIGHT_ALT
```

### Mouse
```c
MOUSE_BUTTON_LEFT
MOUSE_BUTTON_RIGHT
MOUSE_BUTTON_MIDDLE
MOUSE_WHEEL_UP
MOUSE_WHEEL_DOWN
MOUSE_WHEEL_LEFT
MOUSE_WHEEL_RIGHT
```

### Gamepad
```c
GAMEPAD_BUTTON_A
GAMEPAD_BUTTON_B
GAMEPAD_BUTTON_X
GAMEPAD_BUTTON_Y
JOY_BUTTON_LB
JOY_BUTTON_RB
JOY_BUTTON_START
JOY_BUTTON_BACK
JOY_BUTTON_LS
JOY_BUTTON_RS
GAMEPAD_AXIS_LX, GAMEPAD_AXIS_LY
GAMEPAD_AXIS_RX, GAMEPAD_AXIS_RY
GAMEPAD_AXIS_LT, GAMEPAD_AXIS_RT
```

## Debugging Macros

```c
#define MOSS_ASSERT(condition)
#define MOSS_TRACE(message)      // Most verbose
#define MOSS_DEBUG(message)
#define MOSS_INFO(message)
#define MOSS_WARN(message)
#define MOSS_ERROR(message)
#define MOSS_FATAL(message)      // Least verbose
```
