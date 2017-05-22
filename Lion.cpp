#include "Lion.h"

/*** Public ***/
Lion::Lion(byte xpos, byte ypos, byte len)
{
  this->x = xpos;
  this->y = ypos;
  this->frame = 3;
  this->w = len;
}

//get x position
byte Lion::getX()
{
  return this->x;
}

//get x position
byte Lion::getY()
{
  return this->y;
}

//get frame number
byte Lion::getFrame()
{
  return this->frame;
}

byte Lion::getHealth()
{
  return this->health;
}

bool Lion::attacking()
{
  return this->isAttacking;
}

bool Lion::getFacing()
{
  return this->facingRight;
}

void Lion::damage(byte amount)
{
  this->health -= amount;
}

bool Lion::isDead()
{
  return (this->health <= 0);
}

//update Lion
void Lion::updateLion()
{
  if(this->isAttacking)
  {
    if(this->facingRight) this->frame = 2;
    else this->frame = 5;
    
    attack();
  }
  else
  {
    moveForward();

    if(this->facingRight)
    {
      if(this->frame == 1) this->frame = 0;
      else this->frame = 1;
    }
    else
    {
      if(this->frame == 4) this->frame = 3;
      else this->frame = 4;
    }
  }
}

/*** Private ***/
//handles moving Lion left and right, also does bounds checking on screen
void Lion::moveForward()
{
  if(this->facingRight)
  {
    this->x += moveSpeed;
    
    if(this->x >= WIDTH - w - moveSpeed)
    {
      this->x = WIDTH - w;
      this->facingRight = false;
      this->isAttacking = true;
    }
  }
  else
  {
    this->x -= moveSpeed;
    
    if(this->x <= moveSpeed)
    {
      this->x = 0;
      this->facingRight = true;
      this->isAttacking = true;
    }
  }
}

//have Lion attack
void Lion::attack()
{
  this->attackFrames--;
  
  if(this->attackFrames == 0)
  {
    this->isAttacking = false;
    this->attackFrames = ATTACK_FRAMES;
  }
}

