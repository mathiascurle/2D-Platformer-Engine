#pragma once

enum Gamestate
{
  MAIN_MENU, PLAYING, LEVEL_EDITOR
};

inline Gamestate g_Gamestate = MAIN_MENU;
