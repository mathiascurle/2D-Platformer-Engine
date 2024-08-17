#pragma once
#include "raylib.h"
#include "Level.h"
#include <vector>
using namespace std;

class LevelManager
{
public:
  static void InitLevels();
  static void LoadLevel(int level);
  static void UnloadLevel(int level);
  static bool LoadTextures();
  static void UnloadTextures();

  static void SetLevel(int level);
  static Level GetCurrentLevel();


public:
  static Texture2D     s_TileAtlas;
  static Texture2D     s_PlayerAtlas;
  static int           s_iCurrentLevel;
  static int           s_iNumberOfLevels;

private:
  static int           s_iPreviousLevel;
  static vector<Level> s_vLevels;

};
