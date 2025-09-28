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


#ifdef __cplusplus
extern "C" {
#endif

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

enum Moss_AudioFormat {
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

enum AudioEffectType {
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

struct AudioSpec_t {
    Moss_AudioFormat format;
    int channels;
    int frequency;
};

struct AudioEffect;
struct Microphone;
struct Speaker;
struct Wav;

struct AudioStream;
struct AudioStream2D;
struct AudioStream3D;

struct AudioListener2D;
struct AudioListener3D;
struct RayAudioListener2D;
struct RayAudioListener3D;

MOSS_API Wav* loadWav(const char* path);
MOSS_API void RemoveWav(Wav* wav);

#ifdef __cplusplus
}
#endif


#endif // MOSS_AUDIO_H

