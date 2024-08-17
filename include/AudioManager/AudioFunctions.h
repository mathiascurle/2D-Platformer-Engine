#pragma once

#include "raylib.h"

namespace AudioFunctions 
{
  
// Music
bool FadeOutMusic(Music music, float time);
bool FadeInMusic(Music music, float time);


// Sound
bool FadeOutSound(Sound sound, float time);
bool FadeInSound(Sound sound, float time);


// Master
bool FadeOutMaster(float time);
bool FadeInMaster(float time);

}
