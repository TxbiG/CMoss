# Audio
## Overview

Audio Supports ```XAudio2 / WASAPI```, ```CoreAudio```, ```ALSA```.


## Macros
```cpp
// Provided by Moss
```
## Enums
```cpp
```
## Structs
```cpp
// Provided by Moss
struct Microphone;
struct Speakers;
struct AudioStream2D;
struct AudioStream3D;
struct AudioListener2D;
struct AudioListener3D;
struct RayCastListenerStream2D;
struct RayCastListenerStream3D;
```

## Functions


## Examples
```cpp

...

int main() {

...

  Moss_Init_Audio();

...

  Moss_Terminate_Audio();

...

}
```
Example
```cpp
```
## Channels
Exmaple
```cpp

...

Moss_CreateChannel(0, 1, 0.0, nullptr_t);  // Dialogue parent to Master
Moss_CreateChannel(0, 2, 0.0, nullptr_t);  // SFX parent to Master
Moss_RemoveChannel();  // SFX parent to Master

...
```

## Effects
```cpp
AudioEffect effect;
```

Exmaple
```cpp
AudioEffect effect;
Moss_CreateEffect(nullptr_t, 0, 0.0, effect);
Moss_RemoveEffect(nullptr_t, 0, 0.0, effect);
```

## Listeners
### AudioListener2
```cpp
Moss_SetAudioListener2();
Moss_GetAudioListener2();
```
### AudioListener3
```cpp
Moss_SetAudioListener3();
Moss_GetAudioListener3();
```


## Streams
### AudioStream
```cpp
AudioStream* Moss_CreateAudioStream();
AudioStream* Moss_UpdateAudioStream();
AudioStream* Moss_RemoveAudioStream();

Moss_Play();
Moss_Pause();
Moss_Stop();
```
### AudioStream2
```cpp
AudioStream2* Moss_CreateAudioStream();
AudioStream2* Moss_UpdateAudioStream();
AudioStream2* Moss_RemoveAudioStream();

Moss_Play();
Moss_Pause();
Moss_Stop();
```
### AudioStream3
```cpp
AudioStream3* Moss_CreateAudioStream();
AudioStream3* Moss_UpdateAudioStream();
AudioStream3* Moss_RemoveAudioStream();

Moss_Play();
Moss_Pause();
Moss_Stop();
```

### Speaker

```cpp
```
Example
```cpp
```
### Microphone
```cpp
```
Example
```cpp
```
## RayTraceAudio
```cpp
struct RayCastAudioStream2D;
struct RayCastAudioStream3D;
```

Example
```cpp
```
