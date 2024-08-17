#pragma once
#include "raylib.h"
#include "Gamestate.h"
#include "LevelManager.h"

class GamestateInterface
{
public:
  virtual void update() = 0;
  virtual void draw()   = 0;

  virtual void keyboardInputs()   = 0; 
  virtual void mouseInputs()      = 0; 
  virtual void controllerInputs() = 0; 
};
