#include "LevelEditor.h"
#include "raymath.h"
#include <string>
#include <fstream>
#include <iostream>

LevelEditor::LevelEditor()
{
  m_vLevelSize = Vector2 {20, 20};
  s_iSelectedTileType = TileType::Dirt;
  
  m_vCenter = {Screen::g_iScreenWidth/2.f, Screen::g_iScreenHeight/2.f};
  // m_vCenter = Vector2Scale(m_vLevelSize, g_iTileSize/2);
  m_camera = { 0 };
  // m_camera.target = {(float)Screen::g_iScreenWidth, (float)Screen::g_iScreenHeight};
  m_camera.target = Vector2Scale(m_vLevelSize, g_iTileSize/2);
  m_camera.offset = m_vCenter;
  m_camera.rotation = 0.0f;
  m_camera.zoom = 1.0f / g_fScale;

  m_vMousePrevPos = GetMousePosition();
  resetBools();
  m_firstUpdate = true;

  m_gui.m_pvLevelSize = &m_vLevelSize;
}

int LevelEditor:: s_iSelectedTileType;
LevelEditorGui LevelEditor:: m_gui;

void LevelEditor::ReadyTextures()
{
  m_gui.setTilePanelIcons(&s_iSelectedTileType);
}

void LevelEditor::update()
{
  keyboardInputs();
  mouseInputs();
  controllerInputs();

  if (m_gui.isLoadLevel())
    loadFromFile(LevelManager::s_iCurrentLevel);
  if (m_gui.isSaveLevel())
    saveToFile(LevelManager::s_iCurrentLevel);

  resetBools();
}

void LevelEditor::draw()
{
  BeginDrawing();
  ClearBackground({130, 130, 125, 255});
  /*----------------------*/
  BeginMode2D(m_camera);

  drawGrid();
  drawTiles();

  EndMode2D();
  /*----------------------*/
  DrawText("Level Editor", 10, 10, 20, LIGHTGRAY);
  m_gui.draw();
  EndDrawing();
}

void LevelEditor::drawGrid()
{
  for (int i = 0; i <= m_vLevelSize.x; i++)
    DrawLine(i * g_iTileSize * g_fScale, 0, i * g_iTileSize * g_fScale, m_vLevelSize.y*g_iTileSize*g_fScale, LIGHTGRAY);
  for (int i = 0; i <= m_vLevelSize.y; i++) 
    DrawLine(0, i * g_iTileSize * g_fScale, m_vLevelSize.x*g_iTileSize * g_fScale, i * g_iTileSize * g_fScale, LIGHTGRAY);
}

void LevelEditor::drawTiles()
{
  for (TileData tile : m_vTileDatas)
  {
    Vector2 vPosXY = getTileAtlasPosV(tile.type);
    Rectangle source = {vPosXY.x, vPosXY.y, (float)g_iTileSize, (float)g_iTileSize};
    Rectangle dest = {(float)(tile.x*g_iTileSize*g_fScale),
                      (float)(tile.y*g_iTileSize*g_fScale),
                      (float)(g_iTileSize*g_fScale),
                      (float)(g_iTileSize*g_fScale)};
    DrawTexturePro(LevelManager::s_TileAtlas, source, dest, Vector2{0,0}, 0.0f, WHITE);
    if (dest.x >= m_vLevelSize.x*g_iTileSize*g_fScale ||
        dest.y >= m_vLevelSize.y*g_iTileSize*g_fScale ||
        dest.x+dest.width <= 0 || dest.y+dest.height <= 0)
      DrawRectangleRec(dest, Color{10, 0, 0, 140});
  }
}

void LevelEditor::keyboardInputs()
{
  if (IsKeyPressed(KEY_ESCAPE))
  {
    LevelManager::UnloadTextures();
    g_Gamestate = MAIN_MENU;
  }

  // if (IsKeyPressed(KEY_R))
  //   m_camera.target = {(float)Screen::g_iScreenWidth, (float)Screen::g_iScreenHeight};

  if (IsKeyDown(KEY_LEFT_CONTROL))
    m_bCtrlDown = true;
  if (IsKeyDown(KEY_LEFT_SHIFT))
    m_bLeftShiftDown = true;
}

void LevelEditor::mouseInputs()
{
  // Camera movement / delta time
  Vector2 vCurrentPos = GetMousePosition();
  Vector2 vDeltaPos = Vector2Subtract(m_vMousePrevPos, vCurrentPos); 
  m_vMousePrevPos = vCurrentPos;

  // Handle gui
  if (m_gui.mouseInput(vCurrentPos, vDeltaPos))
    return;

  // Camera zoom -- rewrite
  m_camera.zoom += ((float)GetMouseWheelMove()*0.01f);
  if (m_camera.zoom > 3.0f) m_camera.zoom = 3.0f;
  else if (m_camera.zoom < 0.3f) m_camera.zoom = 0.3f;

  Vector2 vWorldPos = GetScreenToWorld2D(vCurrentPos, m_camera);
  int iWorldX = vWorldPos.x/(g_iTileSize*g_fScale);
  int iWorldY = vWorldPos.y/(g_iTileSize*g_fScale);

  // Drag camera
  if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
  {
    if (m_bCtrlDown)
    {
      m_camera.target = GetScreenToWorld2D(Vector2Add(m_camera.offset, vDeltaPos), m_camera);
      return;
    }
    if (!isOutsideCanvas(vWorldPos))
    {
      if (m_bLeftShiftDown)
        eraseTile(iWorldX, iWorldY);
      else
        addTile(iWorldX, iWorldY);
    }
  }

  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
  {
  }

  if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
  {
  }
}

void LevelEditor::controllerInputs()
{
}

void LevelEditor::addTile(int x, int y)
{
  bool exists = false;
  for (TileData tile : m_vTileDatas) 
  {
    if (tile.x == x && tile.y == y) 
    {
      exists = true;
      break;
    }
  }
  if (!exists) 
    m_vTileDatas.push_back(TileData{x, y, s_iSelectedTileType});
}

void LevelEditor::eraseTile(int x, int y)
{
  for (auto it = m_vTileDatas.begin(); it != m_vTileDatas.end();)
  {
    if ((*it).x == x && (*it).y == y)
      it = m_vTileDatas.erase(it);
    else ++it;
  }
  m_vTileDatas.shrink_to_fit();
}

void LevelEditor::resetBools()
{
  m_bCtrlDown = false;
  m_bLeftShiftDown = false;
}

bool LevelEditor::isOutsideCanvas(Vector2 vPos)
{
  return (vPos.x < 0 || vPos.y < 0 || 
    vPos.x > m_vLevelSize.x*g_iTileSize*g_fScale || 
    vPos.y > m_vLevelSize.y*g_iTileSize*g_fScale);
}


// File Management \\

bool LevelEditor::loadFromFile(int levelNumber)
{
  m_vTileDatas.clear(); m_vTileDatas.shrink_to_fit();
  if (levelNumber > LevelManager::s_iNumberOfLevels)
  {
    LevelManager::s_iNumberOfLevels = levelNumber;
    LevelManager::InitLevels();
  }
  LevelManager::SetLevel(LevelManager::s_iCurrentLevel);
  m_vTileDatas = LevelManager::GetCurrentLevel().vTileDatas;
  // m_vLevelSize = LevelManager::GetCurrentLevel().vLevelSize;
  return true;
}

bool LevelEditor::saveToFile(int levelNumber)
{
  using namespace std;
  string filename = TextFormat("resources/LevelData/level%01i.txt", levelNumber);
  ofstream myFile; myFile.open(filename);
  if (!myFile.is_open())
  {
    cerr << "Error opening the file: "<<filename<< endl;
    return false;
  }

  myFile << m_vLevelSize.x << " " << m_vLevelSize.y << ";\n";
  int x = 0, y = 0;
  while (y < m_vLevelSize.y)
  {
    if (x >= m_vLevelSize.x)
    {
      myFile<<";\n";
      x = 0;
      y++;
      continue;
    }
    else
    {
      bool tileAvailable = false;
      for (TileData tile : m_vTileDatas)
      {
        if (tile.x == x && tile.y == y)
        {
          myFile << tile.type;
          tileAvailable = true;
          break;
        }
      }
      if (!tileAvailable)
        myFile << 0;
    }
    myFile << ' ';
    x++;
  }

  myFile.close();
  return true;
}
