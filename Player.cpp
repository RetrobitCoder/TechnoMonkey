#include "Player.h"

/*** Public ***/
Player::Player(byte xpos , byte ypos, byte pSize)
{
  this->x = xpos;
  this->y = ypos;
  this->playerSize = pSize;
  this->frame = 0;
  rect.x = this->x;
  rect.y = this->y;
  rect.width = this->playerSize;
  rect.height = this->playerSize;
}

//get x position
byte Player::getX()
{
  return this->x;
}

//get y position
byte Player::getY()
{
  return this->y;
}

//get current frame #
byte Player::getFrame()
{
  return this->frame;
}

//get current health
byte Player::getHealth()
{
  return this->health;
}

void Player::setHealth(byte amount)
{
  this->health = amount;
  this->died = false;
}

Rect Player::getRect()
{
  return rect;
}

void Player::damage(byte amount)
{
  if (!this->isInvincible)
  {
    this->isInvincible = true;
    this->health -= amount;
  }

  if(this->health <= 0) this->died = true;
}

bool Player::checkInvin()
{
  return this->isInvincible;
}

bool Player::isDead()
{
  return this->died;
}

bool Player::getFacing()
{
  return this->isFacingRight;
}

//update player
void Player::updatePlayer(char buttonPressed, char comboButton)
{
  if (this->isInvincible) this->invincibleFrame++;
  if (this->invincibleFrame == INVINCIBLE_FRAMES && this->isInvincible) this->isInvincible = false;

  rect.x = this->x;
  rect.y = this->y;

  switch (buttonPressed)
  {
    case 'A':
    case 'L':
      if (this->isFacingRight) this->frame = 8;
      this->doMove = true;
      this->isFacingRight = false;
      break;
    case 'R':
      if (!this->isFacingRight || this->frame == 0) this->frame = 1;
      this->doMove = true;
      this->isFacingRight = true;
      break;
    case 'B':
      if (!this->isJumping && !this->isInAir) this->isJumping = true;
      if (comboButton == 'L' || comboButton == 'R')
      {
        this->doMove = true;
        if (comboButton == 'L')
        {
          if (this->isFacingRight) this->frame = 8;
          this->isFacingRight = false;
        }
        else if (comboButton == 'R')
        {
          if (!this->isFacingRight) this->frame = 1;
          this->isFacingRight = true;
        }
      }
      break;
    case 'D':
    default:
      this->doMove = false;
      break;
  }

  movePlayer();
}

/*** Private ***/

//handle jumps
void Player::jump()
{
  if (this->isJumping)
  {
    if (this->isFacingRight) this->frame = 4;
    else this->frame = 11;

    this->isInAir = true;
    this->isJumping = false;
    this->oldY = this->y;
  }
  else if (this->isInAir && !this->isFalling && this->y > (this->oldY - MAX_JUMP_DIST))
  {
    this->y--;

    if (this->isFacingRight) this->frame = 5;
    else this->frame = 12;
  }
  else
  {
    this->y++;
    if (!this->isFalling) this->isFalling = true;

    if (this->y > HEIGHT - this->playerSize)
    {
      this->y = HEIGHT - this->playerSize;
      this->isInAir = false;
      this->isFalling = false;
      this->moveFrame = 0;

      if (this->isFacingRight) this->frame = 0;
      else this->frame = 7;
    }
  }
}

//handles horizontal moving
void Player::horizontalMove()
{
  if (this->isFacingRight)
  {
    this->x += this->moveSpeed;

    if (this->moveFrame == MOVE_FRAMES && !this->isInAir)
    {
      if (this->reverseMove)
      {
        if (this->frame == 3) this->frame = 2;
        else
        {
          this->frame = 1;
          this->reverseMove = false;
        }
      }
      else
      {
        if (this->frame == 1) this->frame = 2;
        else
        {
          this->frame = 3;
          this->reverseMove = true;
        }
      }

      this->moveFrame = 0;
    }
    else this->moveFrame++;

    if (this->x > WIDTH - this->playerSize) this->x = WIDTH - this->playerSize;
  }
  else
  {
    this->x -= this->moveSpeed;

    if (this->moveFrame == MOVE_FRAMES && !this->isInAir)
    {
      if (this->reverseMove)
      {
        if (this->frame == 10) this->frame = 9;
        else
        {
          this->frame = 8;
          this->reverseMove = false;
        }
      }
      else
      {
        if (this->frame == 8) this->frame = 9;
        else
        {
          this->frame = 10;
          this->reverseMove = true;
        }
      }

      this->moveFrame = 0;
    }
    else this->moveFrame++;

    if (this->x < 1) this->x = 1;
  }
}

//handles moving player
void Player::movePlayer()
{
  if (this->isJumping || this->isInAir) jump();
  if (this->doMove) horizontalMove();
}

