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
#ifndef MOSS_AUDIO_H
#define MOSS_AUDIO_H

/*!
 * @file Moss_Audio.h
 * @brief Cross-platform audio subsystem for the Moss Framework.
 *
 * The audio module provides a unified, high-performance abstraction over
 * multiple platform-specific backends. It is designed to support both
 * **real-time 3D spatial audio** and **2D streamed playback** for games,
 * XR experiences, and simulation systems.
 *
 * ---
 *
 * ### Supported Backends:
 * - **Windows:** XAudio2 / WASAPI
 * - **macOS:** CoreAudio *(under testing)*
 * - **Linux:** ALSA *(under testing)*
 *
 * ---
 *
 * ### Core Capabilities:
 * - **2D / 3D Audio Streams** — Play, pause, and stop streamed or preloaded sounds.
 * - **Audio Effects Pipeline** — Supports a broad range of DSP effects:
 *   - Lowpass / Highpass filters
 *   - Echo, Flange, Distortion
 *   - Normalize, Parametric EQ
 *   - Pitch Shifting, Chorus, Compressor
 *   - Reverb and Delay
 * - **Dynamic Audio Control** — Real-time adjustment of pitch, gain, and pan per stream or channel.
 * - **Hardware Abstraction** — Unified interface for **Speakers** and **Microphones**, with support for enumeration, selection, and control.
 * - **Audio Listeners** — Spatial representation for 2D and 3D listener transforms, integrated with camera and XR systems.
 *
 * ---
 *
 * ### Future Features:
 * - **Ray-Traced Audio Simulation:**
 *   - SIMD-accelerated CPU tracing for real-time occlusion and first-order reflections.
 *   - GPU-based acoustic data baking (impulse responses, reverb zones).
 *   - Reverb convolution caching for realistic environmental acoustics.
 *   - Hybrid models using direction cones and ray bins for real-time efficiency.
 *
 * ---
 *
 * ### Design Goals:
 * - Low-latency, high-fidelity cross-platform audio.
 * - Thread-safe mixing and real-time streaming.
 * - Integration with Moss Engine’s physics and rendering systems for synchronized A/V effects.
 * - Modular extension for third-party DSPs and audio middleware.
 */

#include <Moss/Moss_Core.h>

/*  Cross-platform audio system supporting:
        - Windows: XAudio
        - MacOS: CoreAudio (Testing)
        - Linux: ALSA (Testing)

    Supports Effects: Lowpass, Highpass, Echo, Flange, Distortion, Normalize, ParamEQ, Pitch Shifter, Chorus, Compressor, Reverb, Delay.
    Supports AudioStream: Pitch and Volume for stream player and channel types.
    Supports Microphones (Set and Get Microphones)
    Supports Speakers    (Set and Get Speakers)
*/

// Future support RayTrace Audio:
    //  SIMD CPU ray tracing for real-time occlusion and first-order reflections.
    //  Use GPU for baking global acoustic data (impulse responses, reverb zones).
    //  Cache GPU results into reverb convolution buffers.
    //  Use approximate or heuristic models (like ray bins or direction cones) to bridge both worlds.
#define MOSS_MAX_CHANNELS         32        // Number of Max Channels
#define MOSS_MAX_STREAMS          32        // Max AudioStreams that can be played at once
#define MOSS_MAX_VERTEX_COUNT     200
#define MOSS_MAX_LINE_COUNT       MAX_VERTEX_COUNT/2
#define MOSS_SAMPLE_RATE          44100
#define MOSS_SOUND_SPEED          2043.0f
#define MOSS_MAX_FILE_LENGTH      10000

// AudioStream player set as signal for calling

typedef enum Moss_AudioFormat {
    UNKNOWN = 0x0000u,  // Unspecified audio format.
    U8      = 0x0008u,  // Unsigned 8-bit samples.
    S8      = 0x8008u,  // Signed 8-bit samples.
    S16LE   = 0x8010u,  // Signed 16-bit samples.
    S16BE   = 0x9010u,  // As above, but big-endian byte order.
    S24LE   = 0x8020u,  // Add this
    S32LE   = 0x8030u,  // 32-bit integer samples.
    S32BE   = 0x9030u,  // As above, but big-endian byte order.
    F32LE   = 0x8120u,  // 32-bit floating point samples.
    F32BE   = 0x9120u,  // As above, but big-endian byte order.
    F64LE   = 0x8140u,  // 64-bit float (double)
    F64BE   = 0x9140u
} Moss_AudioFormat;

typedef enum AudioEffectType {
    EFFECT_NONE = 0x0000u,
    EFFECT_LOWPASS = 0x0008u,
    EFFECT_HIGHTPASS,
    EFFECT_ECHO,
    EFFECT_FLANGE,
    EFFECT_DISTORTION,
    EFFECT_NORMALIZE,
    EFFECT_PARAMEQ,
    EFFECT_PITCHSHIFTER,
    EFFECT_CHORUS,
    EFFECT_COMPRESSOR,
    EFFECT_REVERB,
    EFFECT_DELAY,
    EFFECT_CUSTOM,
} AudioEffectType;

typedef struct AudioSpec_t {
    Moss_AudioFormat format;
    int channels;
    int frequency;
};

typedef struct AudioEffect;
typedef struct Microphone;
typedef struct Speaker;
typedef struct Wav;

typedef struct AudioStream;
typedef struct AudioStream2D;
typedef struct AudioStream3D;

typedef struct AudioListener2D;
typedef struct AudioListener3D;
typedef struct RayAudioListener2D;
typedef struct RayAudioListener3D;

#ifdef __cplusplus
extern "C" {
#endif

MOSS_API Wav* loadWav(const char* path);
MOSS_API void RemoveWav(Wav* wav);


MOSS_API AudioStream* Moss_CreateAudioStream();
MOSS_API AudioStream* Moss_CreateAudioStream2D();
MOSS_API AudioStream* Moss_CreateAudioStream3D();
MOSS_API void Moss_DestoryAudioStream(AudioStream* audiostream);
MOSS_API void Moss_DestoryAudioStream2D(AudioStream2D* audiostream);
MOSS_API void Moss_DestoryAudioStream3D(AudioStream3D* audiostream);


MOSS_API AudioListener2D* Moss_CreateAudioListener2D();
MOSS_API AudioListener3D* Moss_CreateAudioListener3D();
MOSS_API RayAudioListener2D* Moss_CreateRayAudioListener2D();
MOSS_API RayAudioListener3D* Moss_CreateRayAudioListener3D();
MOSS_API void Moss_DestoryAudioListener2D(AudioStream* audiostream);
MOSS_API void Moss_DestoryAudioListener3D(AudioStream* audiostream);
MOSS_API void Moss_DestoryRayAudioListener2D(AudioStream* audiostream);
MOSS_API void Moss_DestoryRayAudioListener3D(AudioStream* audiostream);
#ifdef __cplusplus
}
#endif


#endif // MOSS_AUDIO_H





