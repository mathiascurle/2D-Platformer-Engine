#include "BaseGui.h"

bool BaseGui::isPosOnGui(Vector2 vPos)
{
  for (Rectangle widget : m_vGuiBounds)
  {
    if (CheckCollisionPointRec(vPos, widget))
      return true;
  }
  return false;
}

bool BaseGui::isPanelMoving(Panel* panel, Vector2 vPos)
{
  Rectangle titleRect = {panel->bounds.x,
                         panel->bounds.y,
                         panel->bounds.width,
                         RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT};
  return CheckCollisionPointRec(vPos, titleRect);
}

void BaseGui::movePanel(Panel* panel, Vector2 vDeltaPos)
{
    panel->bounds.x -= vDeltaPos.x;
    panel->bounds.y -= vDeltaPos.y;
    for (auto& element : panel->elementBounds)
    {
      element.x -= vDeltaPos.x;
      element.y -= vDeltaPos.y;
    }
}

bool BaseGui::resizePanel(Panel* panel, Vector2 vPos, Vector2 vDeltaPos)
{
  Rectangle resizeRect = {panel->bounds.x + panel->bounds.width - 20,
                          panel->bounds.y + panel->bounds.height - 20,
                          20, 20};
  return false;
}

