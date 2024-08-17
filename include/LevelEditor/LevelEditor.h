#pragma once

#include "GamestateInterface.h"
#include "LevelEditorGui.h"
#include "LevelManager.h"
#include "Tiles.h"
#include "AudioFunctions.h"
#include <vector>

using namespace Tiles;

class LevelEditor : public GamestateInterface
{
public:
  LevelEditor();
  void update();
  void draw();

  static void ReadyTextures();

private:
  void keyboardInputs(); 
  void mouseInputs(); 
  void controllerInputs();

  void drawGrid();
  void drawTiles();

  void addTile(int x, int y);
  void eraseTile(int x, int y);
  void resetBools();

  bool isOutsideCanvas(Vector2 vPos);

  bool loadFromFile(int levelNumber);
  bool saveToFile(int levelNumber);

private:
  static LevelEditorGui m_gui;
  static int s_iSelectedTileType;

  Camera2D m_camera;

  Vector2  m_vLevelSize;
  Vector2  m_vCenter;
  Vector2  m_vMousePrevPos;

  std::vector<TileData> m_vTileDatas;

  bool m_bCtrlDown;
  bool m_bLeftShiftDown;
  bool m_firstUpdate;

};
