#include "Vulture.h"

/*** Public ***/

Vulture::Vulture(byte xpos, byte ypos, byte len)
{
  this->x = xpos;
  this->y = ypos;
  this->frame = 5;
  this->w = len;
  this->frameStep = 1;
}

//get x position
byte Vulture::getX()
{
  return this->x;
}

//get x position
byte Vulture::getY()
{
  return this->y;
}

//get frame number
byte Vulture::getFrame()
{
  return this->frame;
}

byte Vulture::getHealth()
{
  return this->health;
}

bool Vulture::attacking()
{
  return this->isAttacking;
}

bool Vulture::getFacing()
{
  return this->facingRight;
}

void Vulture::damage(byte amount)
{
  this->health -= amount;
}

bool Vulture::isDead()
{
  return (this->health <= 0);
}

//update Vulture
void Vulture::updateVulture()
{
  if (this->isAttacking)
  {
    if(this->facingRight)
    {
      if(this->frame == 3 && attackFrames < maxAttackFrames/2) this->frame = 4;
      else this->frame = 3;
    }
    else
    {
      if(this->frame == 8 && attackFrames < maxAttackFrames/2) this->frame = 9;
      else this->frame = 8;
    }

    attack();
  }
  else
  {
    moveForward();

    if (this->facingRight)
    {
      if(this->frame > 2) this->frameStep = -1;
      else if (this->frame == 0) this->frameStep = 1;
    }
    else
    {
      if (this->frame > 7) this->frameStep = -1;
      else if(this->frame == 5) this->frameStep = 1;
    }
    this->frame += frameStep;
  }
}

/*** Private ***/
//handles moving Vulture left and right, also does bounds checking on screen
void Vulture::moveForward()
{
  if(this->moveVertical) moveY();
  else moveX();
}

void Vulture::moveY()
{
  if(this->moveDown) this->y += moveSpeed;
  else this->y -= moveSpeed;

  if(this->y >= HEIGHT - w - moveSpeed + 1)
  {
    this->y = HEIGHT - w;
    this->isAttacking = true;
    this->moveDown = false;
  }
  else if(this->y <= moveSpeed)
  {
    this->y = moveSpeed + 1;
    this->isAttacking = false;
    this->moveDown = true;
    this->moveVertical = false;
  }
}

//horizontal movement
void Vulture::moveX()
{
  if (this->facingRight)
  {
    this->x += moveSpeed;

    if (this->x >= WIDTH - w - moveSpeed)
    {
      this->x = WIDTH - w;
      this->facingRight = false;
      this->moveVertical = true;
      this->moveDown = true;
      this->frame = 5;
    }
  }
  else
  {
    this->x -= moveSpeed;

    if (this->x <= moveSpeed)
    {
      this->x = 0;
      this->facingRight = true;
      this->moveVertical = true;
      this->moveDown = true;
      this->frame = 0;
    }
  }
}

//have Vulture attack
void Vulture::attack()
{
  this->attackFrames--;

  if (this->attackFrames == 0)
  {
    this->isAttacking = false;
    this->attackFrames = maxAttackFrames;
  }
}
