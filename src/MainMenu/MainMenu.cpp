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

  if (GuiButton(Rectangle {10, 75, 100, 50}, "Level 0"))
    LevelManager::SetLevel(0);
  if (GuiButton(Rectangle {10, 130, 100, 50}, "Level 1"))
    LevelManager::SetLevel(1);
  if (GuiButton(Rectangle {10, 185, 100, 50}, "Level 2"))
    LevelManager::SetLevel(2);
  if (GuiButton(Rectangle {10, 240, 100, 50}, "Level 3"))
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
