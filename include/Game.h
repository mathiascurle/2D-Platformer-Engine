#include "raylib.h"

#include "Gamestate.h"
#include "Playing.h"
#include "MainMenu.h"
#include "LevelManager.h"
#include "LevelEditor.h"

class Game
{
public:
  Game();
  int run();

private:
  Playing     m_playing;
  MainMenu    m_mainMenu;
  LevelEditor m_levelEditor;
};
