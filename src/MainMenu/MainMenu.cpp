#include "MainMenu.h"
#include "raygui.h"

MainMenu::MainMenu()
{
  LevelManager::InitLevels();
}


// -- GamestateInterface ------------ //
void MainMenu::update()
{
  keyboardInputs();
  mouseInputs();
  controllerInputs();
}

void MainMenu::draw()
{
  BeginDrawing();
  ClearBackground(RAYWHITE);
  /*----------------------*/

  DrawText("Main Menu", 10, 10, 20, GRAY);
  float width = Screen::g_iScreenWidth / 10;
  float height = Screen::g_iScreenHeight / 14;
  // float x = (Screen::g_iScreenWidth / 2) - (width / 2);
  float x = 10;
  float y = 50;

  if (GuiButton(Rectangle {x, y, width, height}, "Level 0"))
    LevelManager::SetLevel(0);
  y += height + 10;
  if (GuiButton(Rectangle {x, y, width, height}, "Level 1"))
    LevelManager::SetLevel(1);
  y += height + 10;
  if (GuiButton(Rectangle {x, y, width, height}, "Level 2"))
    LevelManager::SetLevel(2);
  y += height + 10;
  if (GuiButton(Rectangle {x, y, width, height}, "Level 3"))
    LevelManager::SetLevel(3);

  /*----------------------*/
  EndDrawing();
}


// -- Private ----------------------- //
void MainMenu::keyboardInputs()
{
  if (IsKeyPressed(KEY_ENTER))
  {
    LevelManager::LoadTextures();
    g_Gamestate = PLAYING;
  }
  if (IsKeyPressed(KEY_E))
  {
    LevelManager::LoadTextures();
    LevelEditor::ReadyTextures();
    g_Gamestate = LEVEL_EDITOR;
  }

  if (IsKeyPressed(KEY_ZERO))
    LevelManager::SetLevel(0);
  if (IsKeyPressed(KEY_ONE))
    LevelManager::SetLevel(1);
  if (IsKeyPressed(KEY_TWO))
    LevelManager::SetLevel(2);
}

void MainMenu::mouseInputs()
{
}

void MainMenu::controllerInputs()
{
}
