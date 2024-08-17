#include "LevelManager.h"
#include <iostream>

Texture2D LevelManager::s_TileAtlas;
Texture2D LevelManager::s_PlayerAtlas;

int LevelManager::s_iNumberOfLevels = 4;
int LevelManager::s_iCurrentLevel = 0;
int LevelManager::s_iPreviousLevel = s_iCurrentLevel;
std::vector<Level> LevelManager::s_vLevels;

void LevelManager::InitLevels()
{
  s_vLevels.clear(); s_vLevels.shrink_to_fit();
  for (int i=0; i<=s_iNumberOfLevels; i++)
    s_vLevels.push_back(Level(i));
}

bool LevelManager::LoadTextures()
{
  std::cout << "Loading textures\n";
  s_TileAtlas = LoadTexture("resources/tilemap.png");
  s_PlayerAtlas = LoadTexture("resources/player_sprites.png");
  if (!IsTextureReady(s_TileAtlas) ||
      !IsTextureReady(s_PlayerAtlas))
    return false;
  return true;
}

void LevelManager::UnloadTextures()
{
  std::cout << "Unloading textures\n";
  UnloadTexture(s_TileAtlas);
}

void LevelManager::LoadLevel(int level)
{
  std::cout<<"Loading level "<<level<<" ...\n";
  s_vLevels[level].LoadData();
}

void LevelManager::UnloadLevel(int level)
{
  std::cout<<"Unloading level "<<level<<" ...\n";
  s_vLevels[level].UnloadData();
}

void LevelManager::SetLevel(int level)
{
  UnloadLevel(s_iPreviousLevel);
  if (level >= 0 && level < s_iNumberOfLevels)
    s_iCurrentLevel = level;
  LoadLevel(s_iCurrentLevel);
  s_iPreviousLevel = s_iCurrentLevel;
  s_iCurrentLevel = level;
  std::cout << "Current level is: " << s_iCurrentLevel << "\n";
}

Level LevelManager::GetCurrentLevel()
{
  return s_vLevels[s_iCurrentLevel];
}

