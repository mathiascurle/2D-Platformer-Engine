#include "PauseMenu.h"

PauseMenu::PauseMenu()
{
}

void PauseMenu::initPaused(bool* paused)
{
  m_pbPaused = paused;
}

void PauseMenu::update()
{
  keyboardInputs();
  mouseInputs();
  controllerInputs();
}

void PauseMenu::draw()
{
  BeginDrawing();
  // ClearBackground(RAYWHITE);
  /*----------------------*/

  Rectangle title = {5, 5, 130, 30};
  BeginScissorMode(title.x, title.y, title.width, title.height);
  ClearBackground(DARKGRAY);
  DrawRectangleLinesEx(title, 2.f, LIGHTGRAY);
  DrawText("Pause Menu", title.x+5, title.y+5, 20, LIGHTGRAY);
  EndScissorMode();

  /*----------------------*/
  EndDrawing();

}


void PauseMenu::keyboardInputs()
{
  if (IsKeyPressed(KEY_ESCAPE))
    *m_pbPaused = false;
  else if (IsKeyPressed(KEY_M))
  {
    *m_pbPaused = false;
    LevelManager::UnloadTextures();
    setGamestate(MAIN_MENU);
  }
}

void PauseMenu::mouseInputs()
{
}

void PauseMenu::controllerInputs()
{
}

void PauseMenu::setGamestate(Gamestate state)
{
  g_Gamestate = state;
}
