#include "Elephant.h"

/*** Public ***/
Elephant::Elephant(byte xpos, byte ypos, byte len)
{
  this->x = xpos;
  this->y = ypos;
  this->frame = 3;
  this->w = len;
}

//get x position
byte Elephant::getX()
{
  return this->x;
}

//get x position
byte Elephant::getY()
{
  return this->y;
}

//get frame number
byte Elephant::getFrame()
{
  return this->frame;
}

byte Elephant::getHealth()
{
  return this->health;
}

bool Elephant::attacking()
{
  return this->isAttacking;
}

bool Elephant::getFacing()
{
  return this->facingRight;
}

void Elephant::damage(byte amount)
{
  this->health -= amount;
}

bool Elephant::isDead()
{
  return (this->health <= 0);
}

//update elephant
void Elephant::updateElephant()
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
//handles moving elephant left and right, also does bounds checking on screen
void Elephant::moveForward()
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

//have elephant attack
void Elephant::attack()
{
  this->attackFrames--;
  
  if(this->attackFrames == 0)
  {
    this->isAttacking = false;
    this->attackFrames = maxAttackFrames;
  }
}

