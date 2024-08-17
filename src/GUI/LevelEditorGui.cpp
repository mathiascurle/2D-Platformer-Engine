#include "LevelEditorGui.h"
#include <iostream>

LevelEditorGui::LevelEditorGui()
{
  initPanels();
  resetIsOver();

  m_bIsLoadLevel = false;
  m_bIsSaveLevel = false;
}

void LevelEditorGui::setTilePanelIcons(int* selectedTile)
{
  m_piSelectedTileType = selectedTile;
  // Set TileIcons
  int margin = 10;
  int padding = 5;
  float x = m_TileSelectionPanel.bounds.x + margin;
  float y = m_TileSelectionPanel.bounds.y + margin + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT;

  std::vector<int> tileTypesV = getAvailableTiles();
  for (int tileType : tileTypesV)
  {
    if (x+g_fTileSize > m_TileSelectionPanel.bounds.x+m_TileSelectionPanel.bounds.width)
    {
      x = m_TileSelectionPanel.bounds.x + margin;
      y += (g_fTileSize) + padding;
    }
    TileIcon tileIcon = {getTileAtlasPosRec(tileType),
                         Rectangle {x, y, g_fTileSize, g_fTileSize},
                         false, tileType};
    if (tileType == *m_piSelectedTileType)
      tileIcon.isOver = true;
    m_vTiles.push_back(tileIcon);
    m_TileSelectionPanel.elementBounds.push_back(tileIcon.bounds);
    x += (g_fTileSize) + padding;
  }
}

void LevelEditorGui::draw()
{
  drawTileSelectionPanel();
  drawLoadSavePanel();
  drawLevelSizePanel();
}

bool LevelEditorGui::mouseInput(Vector2 vPos, Vector2 vDeltaPos)
{
  bool isLeftMouseDown = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
  if (m_pDraggingPanel != NULL)
  {
    if (m_pDraggingPanel == &m_TileSelectionPanel)
    {
      movePanel(&m_TileSelectionPanel, vDeltaPos);
      for (TileIcon& tile : m_vTiles)
      {
        tile.bounds.x -= vDeltaPos.x;
        tile.bounds.y -= vDeltaPos.y;
      }
    }
    else
      movePanel(m_pDraggingPanel, vDeltaPos);
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
      m_pDraggingPanel = NULL;
    return true;
  }
  // TileSelectionPanel
  if (CheckCollisionPointRec(vPos, m_TileSelectionPanel.bounds))
  {
    m_TileSelectionPanel.isOver = true;
    if (isLeftMouseDown)
    {
      if (isPanelMoving(&m_TileSelectionPanel, vPos))
        m_pDraggingPanel = &m_TileSelectionPanel;
      resizePanel(&m_TileSelectionPanel, vPos, vDeltaPos);
    }
    for (TileIcon& tile : m_vTiles)
    {
      if (CheckCollisionPointRec(vPos, tile.bounds))
      {
        tile.isOver = true;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
          *m_piSelectedTileType = tile.tileType;
      }
    }
  }
  // LoadSavePanel
  else if (CheckCollisionPointRec(vPos, m_LoadSavePanel.bounds))
  {
    m_LoadSavePanel.isOver = true;
    if (isLeftMouseDown)
      if (isPanelMoving(&m_LoadSavePanel, vPos))
        m_pDraggingPanel = &m_LoadSavePanel;
  }
  else if (CheckCollisionPointRec(vPos, m_LevelSizePanel.bounds))
  {
    m_LevelSizePanel.isOver = true;
    if (isLeftMouseDown)
      if (isPanelMoving(&m_LevelSizePanel, vPos))
        m_pDraggingPanel = &m_LevelSizePanel;
  }
  else return false; // if mouse is not over gui
  return isLeftMouseDown; // returns true if mouse left is down
}

void LevelEditorGui::initPanels()
{
  m_TileSelectionPanel.bounds = {10, 50, 126, 187};
  m_TileSelectionPanel.title = "Tile Selection";

  m_LoadSavePanel.bounds = {10, Screen::g_iScreenHeight - 110.f, 200, 100};
  m_LoadSavePanel.title = "Load & Save";

  m_LevelSizePanel.bounds = {10, Screen::g_iScreenHeight-220.f, 110, 100};
  m_LevelSizePanel.title = "Level Size";

  m_vPanels.push_back(&m_TileSelectionPanel);
  m_vPanels.push_back(&m_LoadSavePanel);
  m_vPanels.push_back(&m_LevelSizePanel);

  for (Panel* panel : m_vPanels)
    m_vGuiBounds.push_back(panel->bounds);
}

void LevelEditorGui::drawHighlights(Panel* panel)
{
  if (panel->isOver)
    DrawRectangleLinesEx(panel->bounds, 2.f, LIGHTGRAY);

  if (panel == &m_TileSelectionPanel)
  {
    for (TileIcon& tile : m_vTiles)
    {
      if (tile.isOver)
      {
        if (tile.tileType != *m_piSelectedTileType)
          DrawRectangleRec(tile.bounds, Color{200, 200, 200, 40});
        Rectangle outline = {tile.bounds.x-2,
                             tile.bounds.y-2,
                             tile.bounds.width+4,
                             tile.bounds.height+4};
        DrawRectangleLinesEx(outline, 2.f, LIGHTGRAY);
      }
      if (tile.tileType != *m_piSelectedTileType)
        tile.isOver = false;
    }
  }
  panel->isOver = false;
}

void LevelEditorGui::resetIsOver()
{
  for (Panel* panel : m_vPanels)
    panel->isOver = false;
  for (TileIcon& tile : m_vTiles)
    if (tile.tileType != *m_piSelectedTileType)
      tile.isOver = false;
}

std::vector<int> LevelEditorGui::getAvailableTiles()
{
  std::vector<int> returnObject;
  Image image = LoadImageFromTexture(LevelManager::s_TileAtlas);
  Color pixelColor;
  Vector2 vPos;
  for (int i = 0; i<256; i++)
  {
    vPos = getTileAtlasPosV(i);
    pixelColor = GetImageColor(image, vPos.x, vPos.y);
    if (pixelColor.r != 0 &&
        pixelColor.g != 0 &&
        pixelColor.b != 0 &&
        pixelColor.a != 0)
      returnObject.push_back(i);
  }
  UnloadImage(image);
  return returnObject;
}

bool LevelEditorGui::isLoadLevel()
{
  return m_bIsLoadLevel;
}

bool LevelEditorGui::isSaveLevel()
{
  return m_bIsSaveLevel;
}

void LevelEditorGui::drawTileSelectionPanel()
{
  GuiPanel(m_TileSelectionPanel.bounds, m_TileSelectionPanel.title);
  for (TileIcon tile : m_vTiles)
    DrawTextureRec(LevelManager::s_TileAtlas,
                   tile.source, 
                   Vector2{tile.bounds.x, tile.bounds.y}, 
                   WHITE);

  drawHighlights(&m_TileSelectionPanel);
}

void LevelEditorGui::drawLoadSavePanel()
{
  GuiPanel(m_LoadSavePanel.bounds, m_LoadSavePanel.title);
  Rectangle LoadButton = {m_LoadSavePanel.bounds.x+10,
                          m_LoadSavePanel.bounds.y+RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT+8,
                          80, 25};
  Rectangle SaveButton = {LoadButton.x,
                          LoadButton.y+LoadButton.height+8,
                          LoadButton.width, LoadButton.height};
  Vector2 CurrentLevel = {LoadButton.x + LoadButton.width + 5, LoadButton.y+5};
  Rectangle Increase = {CurrentLevel.x+65, LoadButton.y, 25, 25};
  Rectangle Decrease = {Increase.x, SaveButton.y, 25, 25};

  m_bIsLoadLevel = GuiButton(LoadButton, "LOAD LEVEL");
  m_bIsSaveLevel = GuiButton(SaveButton, "SAVE LEVEL");
  DrawText(TextFormat("%2i", LevelManager::s_iCurrentLevel), CurrentLevel.x, CurrentLevel.y, 50, BLACK);
  if (GuiButton(Increase, "+"))
    LevelManager::s_iCurrentLevel++;
  if (GuiButton(Decrease, "-"))
    if (LevelManager::s_iCurrentLevel != 0)
      LevelManager::s_iCurrentLevel--;

  drawHighlights(&m_LoadSavePanel);
}

void LevelEditorGui::drawLevelSizePanel()
{
  GuiPanel(m_LevelSizePanel.bounds, m_LevelSizePanel.title);
  Rectangle width = {m_LevelSizePanel.bounds.x+10,
                     m_LevelSizePanel.bounds.y+12+RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT,
                     20, 20};
  Rectangle height = {width.x,
                      width.y+20+12,
                      20, 20};
  Rectangle increase = {width.x+width.width+50, width.y, width.width, width.height};
  Rectangle decrease = {increase.x, height.y, increase.width, increase.height};

  GuiCheckBox(width, "Width", &m_bWidthChecked);
  GuiCheckBox(height, "Height", &m_bHeightChecked);
  if (GuiButton(increase, "+"))
  {
    if (m_bWidthChecked) m_pvLevelSize->x++;
    if (m_bHeightChecked) m_pvLevelSize->y++;
  }
  if (GuiButton(decrease, "-"))
  {
    if (m_bWidthChecked) m_pvLevelSize->x--;
    if (m_bHeightChecked) m_pvLevelSize->y--;
  }


  drawHighlights(&m_LevelSizePanel);
}
