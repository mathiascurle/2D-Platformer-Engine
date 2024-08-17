#include "raylib.h"
#include "Gamestate.h"

class AudioManager
{
public:
  AudioManager();
  void closeAudioDevice();
  void loadSounds();
  void loadMusic();
  // void loadSounds(Gamestate state); // Loads the sounds for specified gamestate
  // void loadMusic(Gamestate state); // Loads music for specified gamestate
  
private:
  void unloadSounds();
  void unloadMusic();

public:
  Sound m_sound1;
  float m_sound1Volume;
  float m_sound1Pitch;
  float m_sound1Pan;
  
  Music m_music1;
  float m_music1Volume;
  float m_music1Pitch;
  float m_music1Pan;
  
  float m_masterVolume;

};
