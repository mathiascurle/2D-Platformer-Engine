#include "GamestateInterface.h"
#include "LevelManager.h"
#include "LevelEditor.h"

class MainMenu 
  : public GamestateInterface
{
public:
  MainMenu();

  // GamestateInterface
  void update();
  void draw();

private:
  void keyboardInputs(); 
  void mouseInputs(); 
  void controllerInputs();

};

