#include "Level.h"
#include "LevelManager.h"
#include "Tiles.h"
#include <fstream>
#include <iostream>
#include <string>
#include <typeinfo>

Level::Level(int levelNr)
{
  iLevelNr = levelNr;
}

void Level::draw()
{
  for (TileData tile : vTileDatas)
  {
    Vector2 vPosXY = getTileAtlasPosV(tile.type);
    DrawTextureRec(LevelManager::s_TileAtlas,
                   Rectangle {vPosXY.x,
                              vPosXY.y,
                              (float)g_iTileSize,
                              (float)g_iTileSize},
                    Vector2  {(float)(tile.x*g_iTileSize),
                              (float)(tile.y*g_iTileSize)},
                    WHITE);
  }
} 

bool Level::LoadData()
{
  std::string filename = TextFormat("resources/LevelData/level%01i.txt", iLevelNr);
  std::ifstream levelDataFile(filename);
  if (!levelDataFile.is_open())
  {
    std::cerr << "Error opening the file: "<<filename<< std::endl;
    return false;
  }
  std::cout<<"Loaded file "<<filename<<std::endl;

  std::string line;
  int x = 0, y = -1;
  while (getline(levelDataFile, line)) 
  { 
    int data = 0, tenth = 1;
    for (char c : line)
    {
      if (c == ' ')
      {
        // Save data
        if (y == -1) // First line reads general level info
        {
          if (x == 0)
            vLevelSize.x = data;
          if (x == 1)
            vLevelSize.y = data;
        }
        else if (data != 0)// Reads tile data
          vTileDatas.push_back(TileData{x, y, data});
        // reset vars and update x
        data = 0; tenth = 1; x++;
        continue;
      }
      else if (c == ';')
        break;
      // Builds total number
      data *= tenth; data += int(c-48); tenth *= 10;
    }
    x = 0; y++;
  }
  return true;
}

void Level::UnloadData()
{
  vTileDatas.clear();
  vTileDatas.shrink_to_fit();
}
