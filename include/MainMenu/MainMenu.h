#include "GamestateInterface.h"
#include "LevelManager.h"
#include "LevelEditor.h"
#include "Globals.h"
using namespace Global;

class MainMenu 
  
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

