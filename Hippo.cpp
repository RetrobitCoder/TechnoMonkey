#include "Hippo.h"

/*** Public ***/

Hippo::Hippo(byte xpos, byte ypos, byte len)
{
  this->x = xpos;
  this->y = ypos;
  this->frame = 3;
  this->w = len;
}

//get x position
byte Hippo::getX()
{
  return this->x;
}

//get x position
byte Hippo::getY()
{
  return this->y;
}

//get frame number
byte Hippo::getFrame()
{
  return this->frame;
}

byte Hippo::getHealth()
{
  return this->health;
}

bool Hippo::attacking()
{
  return this->isAttacking;
}

bool Hippo::getFacing()
{
  return this->facingRight;
}

void Hippo::damage(byte amount)
{
  this->health -= amount;
}

bool Hippo::isDead()
{
  return (this->health <= 0);
}

//update Hippo
void Hippo::updateHippo()
{
  if (this->isAttacking)
  {
    if (this->facingRight) this->frame = 2;
    else this->frame = 5;
    attack();
  }
  else
  {
    moveForward();

    if (this->facingRight)
    {
      if (!this->moveDown) this->frame = 0;
      else this->frame = 1;
    }
    else
    {
      if (!this->moveDown) this->frame = 3;
      else this->frame = 4;
    }
  }
}

/*** Private ***/
//handles moving Hippo left and right, also does bounds checking on screen
void Hippo::moveForward()
{
  if (this->moveDown) this->y += moveSpeed;
  else this->y -= moveSpeed;

  if (this->y < HEIGHT - (w/2))
  {
    this->isAttacking = true;
    this->moveDown = true;
  }
  else if (this->y > HEIGHT - moveSpeed)
  {
    if(this->facingRight)
    {
      this->facingRight = false;
      this->x = WIDTH - w;
    }
    else
    {
      this->facingRight = true;
      this->x = 0;
    }
    this->moveDown = false;
  }
}



//have Hippo attack
void Hippo::attack()
{
  this->attackFrames--;

  if (this->attackFrames == 0)
  {
    this->isAttacking = false;
    this->attackFrames = ATTACK_FRAMES;
  }
}
