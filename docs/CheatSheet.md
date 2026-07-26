# CheatSheet

## Platform
```c
Moss_Window
Moss_Monitor
Moss_Curser
Moss_GammaRamp
Moss_VideoMode
Moss_Image
Moss_Timer
Moss_Time
Moss_Renderer
```
### Window
```c
Moss_CreateWindow();
Moss_CreatePopup();
Moss_CreateConsole();
Moss_MakeContextCurrent();
Moss_IsWindowRunning();

Moss_PollEvents();
Moss_SwapBuffers();
SwapBuffersInterval();
```
#### Callbacks

### Input
Haptic
InputEventType
#### Callbacks

### Monitor
#### Callbacks

### MultiThreading
### Time & Timer
### OS spesific


## Renderer
Moss_Renderer* Moss_CreateRenderer(Moss_Window& window);
void Moss_RendererBeginFrame(Moss_Renderer& renderer);
void Moss_PresentRenderer(Moss_Renderer& renderer);
void Moss_TerminateRenderer(Moss_Renderer& renderer);
Texture
Shader
Mesh
#### Callbacks

## Audio
AudioBusLayout
AudioChannel
AudioEffect
AudioStream
AudioStream2
AudioStream3
WAV

## Resources
Curve
Curve2
Curve3
Gradient
JSON
Font
Tween

## Variants
AABB
bool
Color
float
Float2
Float3
Float4
int
Mat2
Mat3
Mat4
Mat2x3
Mat2x4
Mat3x2
Mat3x4
Mat4x2
Mat4x3
Quat
Rect2
Rect2i
String
StringName
TArray<>
TMap<>
TMiltiMap<>
TSet<>
TStaticArray<>
TVector<>
Vec2
Vec3
Vec4
Vec2i
Vec3i
Vec4i

## UI

## 2D Components
## 2D Physics

## 3D Components
## 3D Physics

## Renderer


## Compression
## Encryption
## Network


## Macros
### Platform
- MOSS_PLATFORM_WINDOWS
- MOSS_PLATFORM_MACOS
- MOSS_PLATFORM_LINUX
- MOSS_PLATFORM_IOS
- MOSS_PLATFORM_ANDROID
- MOSS_PLATFORM_PLAYSTATION
- MOSS_PLATFORM_XBOXONE
- MOSS_PLATFORM_XBOXSERIES
### Graphics APIS
- MOSS_USE_OPENGL
- MOSS_USE_OPENGLES
- MOSS_USE_VULKAN
- MOSS_USE_METAL
- MOSS_USE_DIRECTX
### CPU
- MOSS_USE_NEON
- MOSS_USE_SSE2
- MOSS_USE_SSE4_1
- MOSS_USE_SSE4_2
- MOSS_USE_AVX
- MOSS_USE_AVX2
- MOSS_USE_AVX512
- MOSS_USE_FP16C
- MOSS_USE_LZCNT
- MOSS_USE_TZCNT
- MOSS_USE_FMADD

- MOSS_CPU_X86
- MOSS_CPU_ARM
- MOSS_CPU_RISCV
- MOSS_CPU_PPC
- MOSS_CPU_BIG_ENDIAN
- MOSS_CPU_LOONGARCH
- MOSS_CPU_E2K
- MOSS_CPU_WASM

### Debugs
- MOSS_DEBUG
- MOSS_TRACE();
- MOSS_DEBUG();
- MOSS_INFO();
- MOSS_WARN();
- MOSS_ERROR();
- MOSS_FATAL();
- MOSS_ASSERT();
### Maths
- MAX_INT8
- MAX_INT16
- MAX_INT32
- MAX_INT64
- MIN_INT8
- MIN_INT16
- MIN_INT32
- MIN_INT64
- MAX_UINT8
- MAX_UINT16
- MAX_UINT32
- MAX_UINT64
- MIN_UINT8
- MIN_UINT16
- MIN_UINT32
- MIN_UINT64
- PI
- HALF_PI
- QUARTER_PI
- M_TAU
- M_FLT_EPSILON
- M_INF
- M_E
- M_LOG2E
- M_LOG10E
- M_LN2
- M_LN10
- M_2_SQRTPI
- M_SQRT2
- M_SQRT1_2
- TAN_POLY();
- RAD();
- FACT();
- SIN();
- COS();
- TAN();
- SIGN();
- LERP();
- ABS();
- ATAN2();
- SQRT();
- ACOS();
- ASIN();
- ATAN();
- CEIL();
- FABS();
- FLOOR();
- FMOD();
- LOG();
- LOG10();
- LOG2();
- EXP();
- POW();
- EXP2();
- ROUND();
- TRUNC();
- COSH();
- SINH();
- TANH();
- ACOSH();
- ASINH();
- ATANH();
- HYPOT();
- DEG_TO_RAD();
- RAD_TO_DEG();
- CLAMP();
- MIN();
- MAX();
- SQUARE();
- CUBED();
- ArraySize();

### Input Keys
- KEY_0
- KEY_1
- KEY_2
- KEY_3
- KEY_4
- KEY_5
- KEY_6
- KEY_7
- KEY_8
- KEY_9
- KEY_A
- KEY_B
- KEY_C
- KEY_D
- KEY_E
- KEY_F
- KEY_G
- KEY_H
- KEY_I
- KEY_J
- KEY_K
- KEY_L
- KEY_M
- KEY_N
- KEY_O
- KEY_P
- KEY_Q
- KEY_R
- KEY_S
- KEY_T
- KEY_U
- KEY_V
- KEY_W
- KEY_X
- KEY_Y
- KEY_Z
- KEY_APOSTROPHE
- KEY_BACKSLASH
- KEY_COMMA
- KEY_EQUAL
- KEY_GRAVE_ACCENT
- KEY_LEFT_BRACKET
- KEY_MINUS
- KEY_PERIOD
- KEY_RIGHT_BRACKET
- KEY_SEMICOLON
- KEY_SLASH
- KEY_WORLD_2
- KEY_BACKSPACE
- KEY_DELETE
- KEY_END
- KEY_ENTER
- KEY_ESCAPE
- KEY_HOME
- KEY_INSERT
- KEY_MENU
- KEY_PAGE_DOWN
- KEY_PAGE_UP
- KEY_PAUSE
- KEY_SPACE
- KEY_TAB
- KEY_CAPS_LOCK
- KEY_NUM_LOCK
- KEY_SCROLL_LOCK
- KEY_F1
- KEY_F2
- KEY_F3
- KEY_F4
- KEY_F5
- KEY_F6
- KEY_F7
- KEY_F8
- KEY_F9
- KEY_F10
- KEY_F11
- KEY_F12
- KEY_F13
- KEY_F14
- KEY_F15
- KEY_F16
- KEY_F17
- KEY_F18
- KEY_F19
- KEY_F20
- KEY_F21
- KEY_F22
- KEY_F23
- KEY_F24
- KEY_LEFT_ALT
- KEY_LEFT_CONTROL
- KEY_LEFT_SHIFT
- KEY_LEFT_SUPER
- KEY_PRINT_SCREEN
- KEY_RIGHT_ALT
- KEY_RIGHT_CONTROL
- KEY_RIGHT_SHIFT
- KEY_RIGHT_SUPER
- KEY_DOWN
- KEY_LEFT
- KEY_RIGHT
- KEY_UP
- KEY_KP_0
- KEY_KP_1
- KEY_KP_2
- KEY_KP_3
- KEY_KP_4
- KEY_KP_5
- KEY_KP_6
- KEY_KP_7
- KEY_KP_8
- KEY_KP_9
- KEY_KP_ADD
- KEY_KP_DECIMAL
- KEY_KP_DIVIDE
- KEY_KP_ENTER
- KEY_KP_EQUAL
- KEY_KP_MULTIPLY
- KEY_KP_SUBTRACT
- MOUSE_BUTTON_LEFT
- MOUSE_BUTTON_RIGHT
- MOUSE_BUTTON_MIDDLE
- MOUSE_WHEEL_UP        
- MOUSE_WHEEL_DOWN       
- MOUSE_WHEEL_LEFT       
- MOUSE_WHEEL_RIGHT         
- GAMEPAD_BUTTON_A
- GAMEPAD_BUTTON_B
- GAMEPAD_BUTTON_X
- GAMEPAD_BUTTON_Y
- JOY_BUTTON_LB
- JOY_BUTTON_RB
- JOY_BUTTON_BACK 
- JOY_BUTTON_START
- JOY_BUTTON_LS
- JOY_BUTTON_RS
- GAMEPAD_AXIS_LX
- GAMEPAD_AXIS_LY
- GAMEPAD_AXIS_RX
- GAMEPAD_AXIS_RY
- GAMEPAD_AXIS_LT
- GAMEPAD_AXIS_RT