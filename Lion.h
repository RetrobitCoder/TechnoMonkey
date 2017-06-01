#ifndef lion_h
#define lion_h

#include <Arduboy2.h>

class Lion
{
  public:
    Lion(byte xpos, byte ypos, byte len);
    Lion() {}

    //get Lion's x pos
    byte getX();
    //get Lion's y pos
    byte getY();
    //get frame number
    byte getFrame();
    byte getHealth();
    bool attacking();
    bool getFacing();
    void damage(byte amount);
    bool isDead();
    //update Lion
    void updateLion();

  private:
	static const byte maxAttackFrames = 5;
    byte x;
    byte y;
    byte w;
    int health = 50;
    byte frame;
    byte attackFrames = maxAttackFrames;
    byte moveSpeed = 6;
    bool isAttacking = false;
    bool facingRight = false;

    //move Lion
    void moveForward();
    //attack
    void attack();
};

#endif
