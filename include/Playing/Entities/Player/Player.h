#pragma once
#include "LevelManager.h"
#include "Globals.h"

class Player
{
public:
  Player();
  void update(float dt);
  void draw();

  void updatePos();
  Vector2 getCenterV();

private:
  void handleInputs();
  void moveInputs();
  bool nearingZero(float n);
  void decelerate(float* vel);
  void handleCollision();
  void updateAnimation();

  void fallGravity();

public:
  Vector2 m_vPos;
  Vector2 m_vCenter;
  float   m_fRadius;

  Vector2 m_vVel;
  float   m_fAccel;
  float   m_fDecel;
  float   m_fMaxSpeed;

  Rectangle m_animationRec;
  Rectangle m_hitbox;

  float   m_aniTick;
  float   dt;

  float   m_fGravity;
  float   m_fJumpGravity;
  float   m_fFallGravity;

  bool    m_bInAir;
  bool    m_bJumping;
  bool    m_bFalling;
  bool    m_bMaxJump;
};
