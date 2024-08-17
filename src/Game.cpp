#include "raylib.h"
#include "raygui.h"
#include "styles/style_dark.h"
#include "Globals.h"
#include "Game.h"
using namespace Global;

Game::Game()
{
  InitWindow(Screen::g_iScreenWidth, Screen::g_iScreenHeight, "mygame");
  SetTargetFPS(Screen::g_iFpsTarget);
  SetExitKey(KEY_BACKSPACE);
  GuiLoadStyleDark();
}

int Game::run()
{
  while (!WindowShouldClose())
  {
    switch (g_Gamestate)
    {
      case (PLAYING):
        m_playing.update();
        m_playing.draw();
        break;
      case (MAIN_MENU):
        m_mainMenu.update();
        m_mainMenu.draw();
        break;
      case (LEVEL_EDITOR):
        m_levelEditor.update();
        m_levelEditor.draw();
        break;
      default:
        break;
    }
  }
  CloseWindow();
  return 0;
}
