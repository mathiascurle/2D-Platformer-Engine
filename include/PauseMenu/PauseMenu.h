// #include "GamestateInterface.h"
#pragma once
#include "raylib.h"
#include "Gamestate.h"
#include "LevelManager.h"
#include <memory>

class PauseMenu
{
public:
  PauseMenu();
  void initPaused(bool* paused);
  void update();
  void draw();

  void keyboardInputs(); 
  void mouseInputs(); 
  void controllerInputs();

private:
  void setGamestate(Gamestate state);

private:
  bool* m_pbPaused;

};
