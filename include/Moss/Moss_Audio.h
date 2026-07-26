//                        MIT License
//
//                  Copyright (c) 2026 Toby
//
#ifndef MOSS_AUDIO_H
#define MOSS_AUDIO_H

#include <Moss/Moss_stdinc.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CHANNEL_INVALID 0U

typedef struct AudioEffect AudioEffect;
typedef struct AudioStream AudioStream;
typedef struct AudioStream2D AudioStream2D;
typedef struct AudioStream3D AudioStream3D;
typedef struct AudioListener2D AudioListener2D;
typedef struct AudioListener3D AudioListener3D;
typedef struct RayAudioListener2D RayAudioListener2D;
typedef struct RayAudioListener3D RayAudioListener3D;
typedef struct Moss_AudioSource Moss_AudioSource;
typedef struct Moss_Microphone Moss_Microphone;
typedef struct Moss_Wav Moss_Wav;

typedef uint32 ChannelID;

typedef enum AudioEffectType {
    AUDIO_EFFECT_LOWPASS = 0,
    AUDIO_EFFECT_HIGHPASS = 1 << 0,
    AUDIO_EFFECT_ECHO = 1 << 1,
    AUDIO_EFFECT_FLANGE = 1 << 2,
    AUDIO_EFFECT_DISTORTION = 1 << 3,
    AUDIO_EFFECT_NORMALIZE = 1 << 4,
    AUDIO_EFFECT_PARAMEQ = 1 << 5,
    AUDIO_EFFECT_PITCHSHIFTER = 1 << 6,
    AUDIO_EFFECT_CHORUS = 1 << 7,
    AUDIO_EFFECT_COMPRESSOR = 1 << 8,
    AUDIO_EFFECT_REVERB = 1 << 9,
    AUDIO_EFFECT_DELAY = 1 << 10,
    AUDIO_EFFECT_DOPPLER = 1 << 11,
    AUDIO_EFFECT_PANNING = 1 << 12,
    AUDIO_EFFECT_DISTANCE_ATTENUATION = 1 << 13
} AudioEffectType;

typedef enum DistanceModel { DISTANCE_MODEL_LINEAR, DISTANCE_MODEL_INVERSE, DISTANCE_MODEL_EXPONENTIAL } DistanceModel;
typedef enum AudioLoadType { AUDIO_LOAD_FULLY_LOADED, AUDIO_LOAD_STREAMING } AudioLoadType;

typedef void (*MicrophoneCallback)(const float* buffer, int frames, void* userData);
typedef void (*AudioStreamCallback)(float* buffer, int frames, void* userData);

MOSS_API int Moss_Init_Audio(void);
MOSS_API void Moss_Terminate_Audio(void);
MOSS_API void Moss_AudioUpdate(float deltaTime);

MOSS_API Moss_AudioSource* Moss_AudioLoadWav(const char* filename);
MOSS_API Moss_AudioSource* Moss_AudioLoadOgg(const char* filename, AudioLoadType type);
MOSS_API Moss_AudioSource* Moss_AudioLoadMP3(const char* filename);
MOSS_API Moss_AudioSource* Moss_AudioCaptureMicrophone(Moss_Microphone* mic);

MOSS_API AudioEffect* Moss_AudioCreateEffect(AudioEffectType type);
MOSS_API void Moss_AudioEffectSetParameter(AudioEffect* effect, const char* paramName, float value);
MOSS_API void Moss_AudioRemoveEffect(AudioEffect* effect);

MOSS_API ChannelID Moss_AudioCreateChannel(ChannelID channel);
MOSS_API void Moss_AudioRemoveChannel(ChannelID channel);
MOSS_API ChannelID Moss_AudioGetMasterChannel(void);
MOSS_API void Moss_AudioSetChannelVolume(ChannelID channel, float volume);
MOSS_API void Moss_AudioSetChannelMute(ChannelID channel, bool mute);
MOSS_API void Moss_AudioAddChannelEffect(ChannelID channel, AudioEffect* effect);
MOSS_API void Moss_AudioRemoveChannelEffect(ChannelID channel, AudioEffect* effect);
MOSS_API void Moss_AudioRemoveAllChannelEffects(ChannelID channel);

MOSS_API AudioStream* Moss_AudioStreamCreate(void);
MOSS_API void Moss_AudioStreamPlay(AudioStream* stream);
MOSS_API void Moss_AudioStreamStop(AudioStream* stream);
MOSS_API void Moss_AudioStreamSetVolume(AudioStream* stream, float volume);
MOSS_API void Moss_AudioStreamSetPitch(AudioStream* stream, float pitch);
MOSS_API void Moss_AudioStreamSetLoop(AudioStream* stream, bool loop);
MOSS_API void Moss_AudioStreamSetCallback(AudioStream* stream, AudioStreamCallback callback, void* userData);
MOSS_API void Moss_AudioStreamRemove(AudioStream* stream);

MOSS_API AudioStream2D* Moss_AudioStream2DCreate(void);
MOSS_API void Moss_AudioStream2DPlay(AudioStream2D* stream);
MOSS_API void Moss_AudioStream2DStop(AudioStream2D* stream);
MOSS_API void Moss_AudioStream2DSetVolume(AudioStream2D* stream, float volume);
MOSS_API void Moss_AudioStream2DSetPitch(AudioStream2D* stream, float pitch);
MOSS_API void Moss_AudioStream2DSetLoop(AudioStream2D* stream, bool loop);
MOSS_API void Moss_AudioStream2DSetPosition(AudioStream2D* stream, Vec2 position);
MOSS_API void Moss_AudioStream2DSetVelocity(AudioStream2D* stream, Vec2 velocity);
MOSS_API void Moss_AudioStream2DSetMaxDistance(AudioStream2D* stream, float max_distance);
MOSS_API void Moss_AudioStream2DRemove(AudioStream2D* stream);

MOSS_API AudioStream3D* Moss_AudioStream3DCreate(void);
MOSS_API void Moss_AudioStream3DPlay(AudioStream3D* stream);
MOSS_API void Moss_AudioStream3DStop(AudioStream3D* stream);
MOSS_API void Moss_AudioStream3DSetVolume(AudioStream3D* stream, float volume);
MOSS_API void Moss_AudioStream3DSetPitch(AudioStream3D* stream, float pitch);
MOSS_API void Moss_AudioStream3DSetLoop(AudioStream3D* stream, bool loop);
MOSS_API void Moss_AudioStream3DSetPosition(AudioStream3D* stream, Vec3 position);
MOSS_API void Moss_AudioStream3DSetVelocity(AudioStream3D* stream, Vec3 velocity);
MOSS_API void Moss_AudioStream3DSetMaxDistance(AudioStream3D* stream, float max_distance);
MOSS_API void Moss_AudioStream3DSetDistanceModel(AudioStream3D* stream, DistanceModel model);
MOSS_API void Moss_AudioStream3DRemove(AudioStream3D* stream);

MOSS_API AudioListener2D* Moss_AudioCreateAudioListener2D(void);
MOSS_API AudioListener3D* Moss_AudioCreateAudioListener3D(void);
MOSS_API RayAudioListener2D* Moss_AudioCreateRayAudioListener2D(void);
MOSS_API RayAudioListener3D* Moss_AudioCreateRayAudioListener3D(void);
MOSS_API void Moss_AudioRemoveAudioListener2D(AudioListener2D* listener);
MOSS_API void Moss_AudioRemoveAudioListener3D(AudioListener3D* listener);
MOSS_API void Moss_AudioRemoveRayAudioListener2D(RayAudioListener2D* listener);
MOSS_API void Moss_AudioRemoveRayAudioListener3D(RayAudioListener3D* listener);
MOSS_API void Moss_AudioActivateAudioListener2D(AudioListener2D* listener, bool activate);
MOSS_API void Moss_AudioActivateAudioListener3D(AudioListener3D* listener, bool activate);
MOSS_API void Moss_AudioActivateRayAudioListener2D(RayAudioListener2D* listener, bool activate);
MOSS_API void Moss_AudioActivateRayAudioListener3D(RayAudioListener3D* listener, bool activate);
MOSS_API void Moss_AudioListenerSetOrientation(AudioListener3D* listener, const Vec3* forward, const Vec3* up);

MOSS_API bool Moss_IsSpeakerDeviceReady(void);
MOSS_API void Moss_AudioSpeakerOpen(void);
MOSS_API void Moss_AudioSpeakerPause(void);
MOSS_API void Moss_AudioSpeakerResume(void);
MOSS_API bool Moss_AudioSpeakerIsPaused(void);
MOSS_API bool Moss_AudioSelectSpeakerDevice(int id);
MOSS_API int Moss_GetCurrentSpeakerDeviceID(void);
MOSS_API const char* Moss_GetSpeakerDeviceName(int id);
MOSS_API int Moss_ListSpeakerDevices(void);

MOSS_API bool Moss_IsMicrophoneDeviceReady(void);
MOSS_API int Moss_AudioMicrophoneOpen(void);
MOSS_API void Moss_AudioMicrophoneClose(void);
MOSS_API void Moss_AudioMicrophonePlay(void);
MOSS_API void Moss_AudioMicrophoneStop(void);
MOSS_API int Moss_AudioMicrophoneID(void);
MOSS_API bool Moss_AudioSelectMicrophoneDevice(int id);
MOSS_API const char* Moss_GetMicrophoneDeviceName(int index);
MOSS_API int Moss_ListMicrophoneDevices(void);
MOSS_API void Moss_AudioMicrophoneSetGain(Moss_Microphone* mic, float gain);
MOSS_API int Moss_AudioMicrophoneGetSampleRate(Moss_Microphone* mic);
MOSS_API int Moss_AudioMicrophoneGetChannels(Moss_Microphone* mic);
MOSS_API void Moss_AudioMicrophoneSetCallback(Moss_Microphone* mic, MicrophoneCallback callback, void* userData);

#ifdef __cplusplus
}
#endif

#endif // MOSS_AUDIO_H
