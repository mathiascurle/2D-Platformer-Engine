#pragma once
#include "raylib.h"
#include "raymath.h"
#include <vector>
#include "Tiles.h"
#include "Globals.h"
using namespace Tiles;
using namespace Global;
using namespace std;

class Level
{
public:
  Level(int levelNr);
  void draw();
  bool LoadData();
  void UnloadData();

public:
  vector<TileData> vTileDatas;
  Vector2 vLevelSize;
  int     iLevelNr;

};
