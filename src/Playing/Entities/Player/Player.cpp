#include "Player.h"
#include "raymath.h"
#include <iostream>

Player::Player()
{
  m_vPos = {3*32, 2*32};
  m_vCenter = Vector2AddValue(m_vPos, 16);
  m_fRadius = 16;

  m_vVel = {0.0f, 0.0f};
  m_fAccel = 20.0f;
  m_fDecel = 20.0f;
  m_fMaxSpeed = 80.0f;

  m_animationRec = {0, 0, 64, 40};
  m_aniTick = 0;

  m_fGravity = 10;
  m_fJumpGravity = 0;
  m_fFallGravity = 0;

  m_bInAir = false;
  m_bJumping = false;
  m_bFalling = false;
  m_bMaxJump = false;
}

void Player::update(float dt)
{
  this->dt = dt;
  // m_vVel.y = m_fGravity * dt;
  handleInputs();
  handleCollision();
  updatePos();
  updateAnimation();
  m_vCenter.x = m_vPos.x + (64/2);
  m_vCenter.y = m_vPos.y + (40/2);
  m_hitbox = {m_vPos.x+24, m_vPos.y+8, 15, 27};
}

void Player::draw()
{
  // DrawCircleV(m_vCenter, m_fRadius, BLUE);
  DrawTextureRec(LevelManager::s_PlayerAtlas, m_animationRec, m_vPos, WHITE);
  // DrawRectangleLinesEx(m_hitbox, 1.f, RED);
}

void Player::updatePos()
{
  m_vPos = Vector2Add(m_vPos, m_vVel);
}

Vector2 Player::getCenterV()
{
  return m_vCenter;
}


// ------------ PRIVATE ------------ \\

void Player::handleInputs()
{
  moveInputs();
}

void Player::moveInputs()
{
  bool up = false, down = false, left = false, right = false;
  m_bJumping = false;

  // up   = IsKeyDown(KEY_W);
  // down = IsKeyDown(KEY_S);
  // if ( up && !down) m_vVel.y -= m_vVel.y <= -m_fMaxSpeed * dt ? 0.0f : m_fAccel * dt;
  // if (!up &&  down) m_vVel.y += m_vVel.y >= +m_fMaxSpeed * dt ? 0.0f : m_fAccel * dt;
  // if ( up ==  down) decelerate(&m_vVel.y);
  
  left  = IsKeyDown(KEY_A);
  right = IsKeyDown(KEY_D);
  if ( left && !right) m_vVel.x -= m_vVel.x <= -m_fMaxSpeed * dt ? 0.0f : m_fAccel * dt;
  if (!left &&  right) m_vVel.x += m_vVel.x >= +m_fMaxSpeed * dt ? 0.0f : m_fAccel * dt;
  if ( left ==  right) decelerate(&m_vVel.x);

  // Jumping
  if (IsKeyPressed(KEY_SPACE) && !m_bInAir)
  {
    m_bInAir = true;
    m_fJumpGravity = 70;
  }
  if (m_bInAir)
    m_vVel.y -= m_fJumpGravity * dt;
  if (m_fJumpGravity != 0)
    m_fJumpGravity -= 10;
  if (m_vVel.y <= 8)
    m_vVel.y += m_fGravity * dt;

  // if ((up && left) || (up && right)) 
  //   Vector2Scale(m_vVel, 0.59f);
}

bool Player::nearingZero(float n)
{
  float threshold = m_fDecel*dt;
  if (n <= threshold && n >= -threshold)
    return true;
  return false;
}

void Player::decelerate(float* vel)
{
  int dir = (*vel < 0) ? 1 : -1;
  *vel += nearingZero(*vel) ? -(*vel)  : (m_fDecel*dir*dt);
}

void Player::handleCollision()
{
  for (TileData tile : LevelManager::GetCurrentLevel().vTileDatas)
  {
    Rectangle tileRect = {tile.x*g_fTileSize, tile.y*g_fTileSize, g_fTileSize, g_fTileSize};
    Rectangle nextHitbox = {m_hitbox.x+m_vVel.x, m_hitbox.y+m_vVel.y, m_hitbox.width, m_hitbox.height};
    if (tile.type != 0) // Tile is none void
    {
      if (CheckCollisionRecs(nextHitbox, tileRect)) 
      {
        m_fJumpGravity = 0;
        if (m_hitbox.y+m_hitbox.height < tileRect.y) // Player is over tile
        {
          m_vVel.y = 0;
          m_bInAir = false;
        }
      }
    }
  }
}

void Player::updateAnimation()
{
  int animationLength = 0;
  if (m_vVel.x == 0) // Standing still 
  {
    m_animationRec.y = 40*0;
    animationLength = 5;
  }
  else if (m_vVel.x > 0) // Moving right
  {
    m_animationRec.y = 40*1;
    animationLength = 6;
  }
  else if (m_vVel.x < 0) // Moving left
  {
    m_animationRec.y = 40*2;
    animationLength = 6;
  }

  m_aniTick += 6+dt; // animation speed

  if (m_aniTick >= Global::Screen::g_iFpsTarget)
  {
    if (m_animationRec.x >= 64*(animationLength-1))
      m_animationRec.x = 0;
    else
      m_animationRec.x += 64;
    m_aniTick = 0;
  }
}

void Player::fallGravity()
{
  if (m_bInAir)
  {
    // m_vVel.y = -300 * dt;
    m_fFallGravity += (m_vVel.y > 10 * dt) ? -m_fJumpGravity : m_fGravity * dt;
    m_vVel.y += m_fJumpGravity;
  }
  else
  {
    m_bFalling = false;
    m_fFallGravity = 0;
  }
}
