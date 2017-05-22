#include "Zookeeper.h"

/*** Public ***/
Zookeeper::Zookeeper(byte xpos, byte ypos, byte len)
{
  this->x = xpos;
  this->y = ypos;
  this->frame = 3;
  this->w = len;
}

//get x position
byte Zookeeper::getX()
{
  return this->x;
}

//get x position
byte Zookeeper::getY()
{
  return this->y;
}

//get frame number
byte Zookeeper::getFrame()
{
  return this->frame;
}

byte Zookeeper::getHealth()
{
  return this->health;
}

bool Zookeeper::attacking()
{
  return this->isAttacking;
}

void Zookeeper::damage(byte amount)
{
  this->health -= amount;
}

bool Zookeeper::isDead()
{
  return (this->health <= 0);
}

bool Zookeeper::getFacing()
{
  return this->facingRight;
}

//update Zookeeper
void Zookeeper::updateZookeeper()
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
//handles moving Zookeeper left and right, also does bounds checking on screen
void Zookeeper::moveForward()
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

//have Zookeeper attack
void Zookeeper::attack()
{
  this->attackFrames--;
  
  if(this->attackFrames == 0)
  {
    this->isAttacking = false;
    this->attackFrames = ATTACK_FRAMES;
  }
}

