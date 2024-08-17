#pragma once
#include "raylib.h"
#include "raymath.h"

namespace Tiles
{

enum TileType
{
  Empty=0, Grass=17, Dirt=2
};

struct TileData {
  int x;
  int y;
  int type;
};

inline int   g_iTileSize = 32;
inline float g_fTileSize = 32;
inline float g_fScale = 2.0f;

inline Vector2 getTileAtlasPosV(int n)
{
  int xPos = n % 16;
  int yPos = (n / 16) - (xPos / 16);
  return Vector2Scale(Vector2{(float)xPos,
                              (float)yPos},
                              (float)g_iTileSize);
}

inline Rectangle getTileAtlasPosRec(int n)
{
  int xPos = n % 16;
  int yPos = (n / 16) - (xPos / 16);
  return Rectangle {xPos*g_fTileSize, yPos*g_fTileSize, g_fTileSize, g_fTileSize};
}


}
