#pragma once

#include "raylib.h"
#include "raygui.h"
#include "Tiles.h"
#include <vector>

using namespace Tiles;

#if !defined(RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT)
  #define RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT 24
#endif

struct Panel
{
  Rectangle   bounds;
  const char* title;
  bool        isOver;
  bool        moving;
  bool        resizing;
  std::vector<Rectangle> elementBounds;
};

class BaseGui
{
protected:
  BaseGui() = default;
public:
  virtual void draw() = 0;
  virtual bool mouseInput(Vector2 vPos, Vector2 vDeltaPos) = 0;

  bool isPosOnGui(Vector2 vPos);
  bool isPanelMoving(Panel* panel, Vector2 vPos);
  void movePanel(Panel* panel, Vector2 vDeltaPos);
  bool resizePanel(Panel* panel, Vector2 vPos, Vector2 vDeltaPos);

public:
  std::vector<Rectangle> m_vGuiBounds;

};


