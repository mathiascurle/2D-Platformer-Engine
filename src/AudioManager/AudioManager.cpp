#include "AudioManager.h"

AudioManager::AudioManager()
{
  InitAudioDevice();
  if (IsAudioDeviceReady())
    SetMasterVolume(1.0f);
  // else
    // feilmelding
}

void AudioManager::closeAudioDevice()
{
  unloadSounds();
  unloadMusic();
  CloseAudioDevice();
}

void AudioManager::loadSounds()
{
  m_sound1 = LoadSound("resources/Ping.wav");
}

void AudioManager::loadMusic()
{
}

void AudioManager::unloadSounds()
{
  UnloadSound(m_sound1);
}

void AudioManager::unloadMusic()
{
}

