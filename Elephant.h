#ifndef elephant_h
#define elephant_h
#endif

#include <Arduboy2.h>

class Elephant
{
  public:
    Elephant(byte xpos, byte ypos, byte len);
    Elephant(){}

    //get elephant's x pos
    byte getX();
    //get elephant's y pos
    byte getY();
    //get frame number
    byte getFrame();
    byte getHealth();
    bool attacking();
    bool getFacing();
    void damage(byte amount);
    bool isDead();
    //update elephant
    void updateElephant();

  private:
	static const byte maxAttackFrames = 10;
    byte x;
    byte y;
    byte w;
    int health = 50;
    byte frame;
    byte attackFrames = maxAttackFrames;
    byte moveSpeed = 5;
    bool isAttacking = false;
    bool facingRight = false;

    //move elephant
    void moveForward();
    //attack
    void attack();
};

