//                        MIT License
//
//                  Copyright (c) 2026 Toby
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
 * - **Ray-Traced Audio Listeners** - CPU tracing for real-time occlusion and first-order reflections.
 * - **Wav Files** - .Wav files are supported
 *
 * ---
 *
 * ### Design Goals:
 * - Low-latency, high-fidelity cross-platform audio.
 * - Thread-safe mixing and real-time streaming.
 * - Integration with Moss Engine’s physics and rendering systems for synchronized A/V effects.
 * - Modular extension for third-party DSPs and audio middleware.
 */

#ifndef MOSS_AUDIO_H
#define MOSS_AUDIO_H

#include <Moss/Moss_stdinc.h>
#include <Moss/Moss_Physics.h>
#include <Moss/Core/Variants/Vector/Vec2.h>
#include <Moss/Core/Variants/Vector/Vec3.h>

// AudioStream player set as signal for calling
#define CHANNEL_INVALID 0

MOSS_SUPRESS_WARNINGS_BEGIN

// ==========================
// Forward Declorations
// ==========================

typedef struct Wav;
typedef struct AudioEffect AudioEffect;
typedef struct Moss_AudioSystem Moss_AudioSystem;
typedef struct Moss_AudioStream Moss_AudioStream;
typedef struct Moss_AudioStream2D Moss_AudioStream2D;
typedef struct Moss_AudioStream3D Moss_AudioStream3D;
typedef struct Moss_AudioListener2D Moss_AudioListener2D;
typedef struct Moss_AudioListener3D Moss_AudioListener3D;
typedef struct Moss_RayAudioListener2D Moss_RayAudioListener2D;
typedef struct Moss_RayAudioListener3D Moss_RayAudioListener3D;
typedef struct Moss_AudioChannel Moss_AudioChannel;
typedef struct Moss_Microphone Moss_Microphone;

typedef uint32_t ChannelID;

enum AudioEffectType {
    AUDIO_EFFECT_TYPE_LOWPASS,
    AUDIO_EFFECT_TYPE_HIGHTPASS,
    AUDIO_EFFECT_TYPE_ECHO,
    AUDIO_EFFECT_TYPE_FLANGE,
    AUDIO_EFFECT_TYPE_DISTORTION,
    AUDIO_EFFECT_TYPE_NORMALIZE,
    AUDIO_EFFECT_TYPE_PARAMEQ,
    AUDIO_EFFECT_TYPE_PITCHSHIFTER,
    AUDIO_EFFECT_TYPE_CHORUS,
    AUDIO_EFFECT_TYPE_COMPRESSOR,
    AUDIO_EFFECT_TYPE_REVERB,
    AUDIO_EFFECT_TYPE_DELAY,
    // Doppler, panning, distance attenuation
};

typedef struct AudioChannel {
    ChannelID id;
    ChannelID parent;        // CHANNEL_INVALID = master output

    float volume;            // 0..1
    uint8_t muted;

    AudioEffect* effects;    // linked list
} AudioChannel;

struct AudioStream {
    #ifdef _WIN32
    IXAudio2SourceVoice* sourceVoice = nullptr;
#endif // WIN32
    Wav& wav;
    Moss_Microphone mic;
private:
    bool playing = false;
    bool loop;
    float pitch;
    float volume;
    ChannelID channel;
};

struct AudioStream2D {
    AudioStream stream;
    Vec2 position;
    Vec3 velocity;
    float maxDistance;
};

struct AudioStream2D {
    AudioStream stream;
    Vec2 position;
    Vec3 velocity;
    float maxDistance;
    float currentPan = 0.0f;
};

MOSS_API void Moss_Init_Audio();
MOSS_API void Moss_Terminate_Audio();



MOSS_API AudioEffect* Moss_CreateAudioEffect(AudioEffectType type);
MOSS_API void Moss_AudioCreateEffect(AudioEffect* effect, const char* paramName, float value);
MOSS_API void Moss_AudioRemoveEffect(AudioEffect* effect);


// Channels
/*! @brief X. */
MOSS_API ChannelID Moss_AudioCreateChannel(ChannelID channel);
/*! @brief X. */
MOSS_API void      Audio_RemoveChannel(ChannelID channel);
/*! @brief X. */
MOSS_API ChannelID Moss_AudioGetMasterChannel();
/*! @brief X. */
MOSS_API void Moss_AudioSetChannelVolume(ChannelID channel, float volume);
/*! @brief X. */
MOSS_API void Moss_AudioSetChannelMute(ChannelID channel, bool mute);
/*! @brief X. */
MOSS_API void Moss_AudioAddChannelEffect(ChannelID channel, AudioEffect* effect);
/*! @brief X. */
MOSS_API void Moss_AudioRemoveChannelEffect(ChannelID channel, AudioEffect* effect);
/*! @brief X. */
MOSS_API void Moss_AudioRemoveAllChannelEffects(ChannelID channel);


MOSS_API Wav* CreateWav(const char* path);
MOSS_API void RemoveWav(Wav* wav);

// AudioStreams
/*! @brief X. */
MOSS_API AudioStream* Moss_CreateAudioStream(Wav& WavFile, float volume = 1.0f, float pitch = 1.0f, bool loop = false);
MOSS_API void Moss_PlayAudioStream();
MOSS_API void Moss_StopAudioStream();
MOSS_API void Moss_AudioStreamSetPosition(float seconds);
MOSS_API void Moss_AudioStreamSetVolume(float volume);
MOSS_API void Moss_AudioStreamSetPitch(float pitch);
MOSS_API void Moss_AudioStreamSetLooping(bool loop);
/*! @brief X. */
MOSS_API AudioStream2D* Moss_CreateAudioStream2D(Wav& WavFile, float volume = 1.0f, float pitch = 1.0f, bool loop = false, float maxDistance = 100.0f, Float2 position = Float2(0.0f, 0.0f));
MOSS_API void Moss_PlayAudioStream2D();
MOSS_API void Moss_StopAudioStream2D();
MOSS_API void Moss_AudioStream2DSetPosition(float seconds);
MOSS_API void Moss_AudioStream2DSetVolume(float volume);
MOSS_API void Moss_AudioStream2DSetPitch(float pitch);
MOSS_API void Moss_AudioStream2DSetLooping(bool loop);
MOSS_API void Moss_AudioStream2DSetPosition();
MOSS_API void Moss_AudioStream2DSetVelocity();
MOSS_API void Moss_AudioStream2DSetMaxDistance();
/*! @brief X. */
MOSS_API AudioStream3D* Moss_CreateAudioStream3D(Wav& WavFile, float volume = 1.0f, float pitch = 1.0f, bool loop = false, float maxDistance = 100.0f, Float3 position = Float3(0.0f, 0.0f, 0.0f), 
    Float3 velocity = Float3(0.0f, 0.0f, 0.0f));
MOSS_API void Moss_PlayAudioStream3D();
MOSS_API void Moss_StopAudioStream3D();
MOSS_API void Moss_AudioStream3DSetPosition(float seconds);
MOSS_API void Moss_AudioStream3DSetVolume(float volume);
MOSS_API void Moss_AudioStream3DSetPitch(float pitch);
MOSS_API void Moss_AudioStream3DSetLooping(bool loop);
MOSS_API void Moss_AudioStream3DSetPosition();
MOSS_API void Moss_AudioStream3DSetVelocity();
MOSS_API void Moss_AudioStream3DSetMaxDistance();

/*! @brief X. */
MOSS_API AudioStream* Moss_CreateAudioStream(Moss_Microphone& microphone, float volume = 1.0f, float pitch = 1.0f);
/*! @brief X. */
MOSS_API AudioStream2D* Moss_CreateAudioStream2D(Moss_Microphone& microphone, float volume = 1.0f, float pitch = 1.0f, bool loop = false, float maxDistance = 100.0f, Float2 position = Float2(0.0f, 0.0f));
/*! @brief X. */
MOSS_API AudioStream3D* Moss_CreateAudioStream3D(Moss_Microphone& microphone, float volume = 1.0f, float pitch = 1.0f, bool loop = false, float maxDistance = 100.0f, Float3 position = Float3(0.0f, 0.0f, 0.0f), 
    Float3 velocity = Float3(0.0f, 0.0f, 0.0f));

MOSS_API void Moss_RemoveAudioStream(AudioStream* audio);
MOSS_API void Moss_RemoveAudioStream2D(AudioStream2D* audio);
MOSS_API void Moss_RemoveAudioStream3D(AudioStream3D* audio);

// Listeners
/*! @brief X. */
MOSS_API AudioListener2D* Moss_CreateAudioListener2D(const Vec2& pos);
/*! @brief X. */
MOSS_API AudioListener3D* Moss_CreateAudioListener3D(const Vec3& pos);
/*! @brief X. */
MOSS_API RayAudioListener2D* Moss_CreateRayAudioListener2D(const Vec2& pos);
/*! @brief X. */
MOSS_API RayAudioListener3D* Moss_CreateRayAudioListener3D(const Vec3& pos);

/*! @brief X. */
MOSS_API void Moss_RemoveAudioListener2D(AudioListener2D* listener);
/*! @brief X. */
MOSS_API void Moss_RemoveAudioListener3D(AudioListener3D* listener);
/*! @brief X. */
MOSS_API void Moss_RemoveRayAudioListener2D(RayAudioListener2D* listener);
/*! @brief X. */
MOSS_API void Moss_RemoveRayAudioListener3D(RayAudioListener3D* listener);

// Set Audiolistener for the audio system
MOSS_API void Moss_AudioSetListener2D(AudioListener2D* listener);
MOSS_API void Moss_AudioSetListener3D(AudioListener3D* listener);
MOSS_API void Moss_AudioSetRayListener2D(RayAudioListener2D* listener);
MOSS_API void Moss_AudioSetRayListener3D(RayAudioListener3D* listener);

MOSS_API void Moss_AudioListener2DSetPosition(AudioListener2D* listener, const Vec2& pos);
MOSS_API void Moss_AudioListener2DSetVelocity(AudioListener2D* listener, const Vec2& vel);
MOSS_API void Moss_AudioListener3DSetPosition(AudioListener3D* listener, const Vec3& pos);
MOSS_API void Moss_AudioListener3DSetVelocity(AudioListener3D* listener, const Vec3& vel);
MOSS_API void Moss_RayAudioListener2DSetPosition(RayAudioListener2D* listener, const Vec2& pos);
MOSS_API void Moss_RayAudioListener2DSetVelocity(RayAudioListener2D* listener, const Vec2& vel);
MOSS_API void Moss_RayAudioListener3DSetPosition(RayAudioListener3D* listener, const Vec3& pos);
MOSS_API void Moss_RayAudioListener3DSetVelocity(RayAudioListener3D* listener, const Vec3& vel);

MOSS_API void Moss_AudioListener2DActive(AudioListener2D* listener, bool active);
MOSS_API void Moss_AudioListener3DActive(AudioListener3D* listener, bool active);
MOSS_API void Moss_AudioRayListener2DActive(RayAudioListener2D* listener, bool active);
MOSS_API void Moss_AudioRayListener3DActive(RayAudioListener3D* listener, bool active);

// Speakers
/*! @brief X. */
MOSS_API bool Moss_IsSpeakerDeviceReady();
/*! @brief X. */
MOSS_API void Moss_AudioSpeakerOpen();
/*! @brief X. */
MOSS_API void Moss_AudioSpeakerPause();
/*! @brief X. */
MOSS_API void Moss_AudioSpeakerResume();
/*! @brief X. */
MOSS_API bool Moss_AudioSpeakerIsPaused();
/*! @brief X. @param X X. */
MOSS_API bool Moss_SelectSpeakerDevice(int id);
/*! @brief X. */
MOSS_API int Moss_GetCurrentSpeakerDeviceID();
/*! @brief Get speaker name. @param X X. */
MOSS_API const char* Moss_GetSpeakerDeviceName(int id);
/*! @brief Return number of speakers. */
MOSS_API int Moss_ListSpeakerDevices();

// Microphone
/*! @brief Check if microphone is ready. */
MOSS_API bool Moss_IsMicrophoneDeviceReady();
/*! @brief Initialize microphone. */
MOSS_API int Moss_AudioMicrophoneOpen();
/*! @brief Terminate microphone. */
MOSS_API int Moss_AudioMicrophoneClose();
/*! @brief Start capture. */
MOSS_API void Moss_AudioMicrophonePlay();
/*! @brief Stop capture. */
MOSS_API void Moss_AudioMicrophoneStop();
/*! @brief Get default microphone ID. */
MOSS_API int  Moss_AudioMicrophoneID();
/*! @brief X. @param X X. */
MOSS_API bool Moss_SelectMicrophoneDevice(int id);
/*! @brief Get microphone name. */
MOSS_API const char* Moss_GetMicrophoneDeviceName(int index);
/*! @brief Return number of microphones. */
MOSS_API int Moss_ListMicrophoneDevices();

MOSS_SUPRESS_WARNINGS_END

#endif // MOSS_AUDIO_H


