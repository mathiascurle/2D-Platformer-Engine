#include "GamestateInterface.h"
#include "LevelManager.h"
#include "PauseMenu.h"
#include "Player.h"
#include "AudioFunctions.h"
#include <iostream>
#include "raymath.h"

class Playing : public GamestateInterface
{
public:
  Playing();
  void update();
  void draw();

  void keyboardInputs(); 
  void mouseInputs(); 
  void controllerInputs();

private:
  Player   m_player;
  Camera2D m_camera;

  bool     m_bPaused;
  PauseMenu pauseMenu;
};
