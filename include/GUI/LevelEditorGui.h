#pragma once

#include "BaseGui.h"
#include "Globals.h"
#include "LevelManager.h"
using namespace Global;

struct TileIcon
{
  Rectangle source;
  Rectangle bounds;
  bool      isOver;
  int       tileType;
};

class LevelEditorGui : public BaseGui
{
public:
  LevelEditorGui();
  void draw();
  void setTilePanelIcons(int* selectedTile);
  bool mouseInput(Vector2 vPos, Vector2 vDeltaPos);

  bool isLoadLevel();
  bool isSaveLevel();

private:
  void initPanels();
  void drawHighlights(Panel* panel);
  void resetIsOver();

  void drawTileSelectionPanel();
  void drawLoadSavePanel();
  void drawLevelSizePanel();

  std::vector<int> getAvailableTiles();

public:
  Vector2* m_pvLevelSize;

private:
  int*     m_piSelectedTileType;

  Panel m_TileSelectionPanel;
  Panel m_LoadSavePanel;
  Panel m_LevelSizePanel;

  std::vector<Panel*>   m_vPanels;
  std::vector<TileIcon> m_vTiles;

  Panel* m_pDraggingPanel;

  bool m_bIsLoadLevel;
  bool m_bIsSaveLevel;

  bool m_bWidthChecked;
  bool m_bHeightChecked;
};
