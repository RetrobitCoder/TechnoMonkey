#include "Bear.h"

/*** Public ***/

Bear::Bear(byte xpos, byte ypos, byte len)
{
  this->x = xpos;
  this->y = ypos;
  this->frame = 4;
  this->w = len;
}

//get bear's x position
byte Bear::getX()
{
  return this->x;
}

//get bear's y position
byte Bear::getY()
{
  return this->y;
}

//get current frame number
byte Bear::getFrame()
{
  return this->frame;
}

byte Bear::getHealth()
{
  return this->health;
}

bool Bear::attacking()
{
  return this->isAttacking;
}

bool Bear::getFacing()
{
  return this->facingRight;
}

void Bear::damage(byte amount)
{
  this->health -= amount;
}

bool Bear::isDead()
{
  return (this->health <= 0);
}

void Bear::updateBear()
{
  if(this->isAttacking)
  {
    if(this->facingRight)
    {
      if(this->swapAttack) this->frame = 3;
      else this->frame = 2;
    }
    else
    {
      if(this->swapAttack) this->frame = 7;
      else this->frame = 6;
    }
    
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
      if(this->frame == 5) this->frame = 4;
      else this->frame = 5;
    }
  }
}

/*** Private ***/

//move bear
void Bear::moveForward()
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

//bear attacks

void Bear::attack()
{
  this->attackFrames--;

  if(maxAttackFrames - this->attackFrames == 3) this->swapAttack = true;
  
  if(this->attackFrames == 0)
  {
    this->isAttacking = false;
    this->attackFrames = maxAttackFrames;
  }
}

