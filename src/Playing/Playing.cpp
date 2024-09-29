#include "Playing.h"
#include "Globals.h"
using namespace Global;

Playing::Playing()
{
  m_bPaused = false;
  pauseMenu.initPaused(&m_bPaused);

  m_camera = { 0 };
  m_camera.target = m_player.getCenterV();
  m_camera.offset = Vector2{ Screen::g_iScreenWidth/2.0f, Screen::g_iScreenHeight/2.0f };
  m_camera.rotation = 0.0f;
  m_camera.zoom = 2.0f;
}

void Playing::update()
{
  if (m_bPaused)
    {pauseMenu.update(); return;}
  float dt = GetFrameTime();
  m_player.update(dt);
  keyboardInputs();
  mouseInputs();
  controllerInputs();

  // Camera movement
  Vector2 playerPos = m_player.getCenterV();
  if (playerPos.x <= (m_camera.target.x - 80))
    m_camera.target.x = playerPos.x + 80;
  else if (playerPos.x >= (m_camera.target.x + 80))
    m_camera.target.x = playerPos.x - 80;
  if (playerPos.y <= (m_camera.target.y - 100))
    m_camera.target.y = playerPos.y + 100;
  else if (playerPos.y >= (m_camera.target.y + 100))
    m_camera.target.y = playerPos.y - 100;
}

void Playing::draw()
{
  if (m_bPaused)
    {pauseMenu.draw(); return;}
  BeginDrawing();
  ClearBackground(RAYWHITE);
  BeginMode2D(m_camera);
  /*----------------------*/

  LevelManager::GetCurrentLevel().draw();
  m_player.draw();

  /*----------------------*/
  EndMode2D();
  DrawText("Playing", 10, 10, 20, GRAY);
  DrawText(TextFormat("X velocity: %02.02f", m_player.m_vVel.x), 10, 40, 16, GRAY);
  DrawText(TextFormat("Y velocity: %02.02f", m_player.m_vVel.y), 10, 60, 16, GRAY);
  EndDrawing();
}

void Playing::keyboardInputs()
{
  if (IsKeyPressed(KEY_ESCAPE))
    m_bPaused = true;
  else if (IsKeyDown(KEY_R))
    m_camera.target = m_player.getCenterV();
  // else if (IsKeyPressed(KEY_RIGHT_SHIFT))
    // toggle "spectator" and playing mode
}

void Playing::mouseInputs()
{
}

void Playing::controllerInputs()
{
}
