#ifndef hippo_h
#define hippo_h
#ifndef Arduboy2_h
#include <Arduboy2.h>
#endif
#endif

class Hippo
{
  public:
    Hippo(byte xpos, byte ypos, byte len);
    Hippo(){}

    //get hippo's x pos
    byte getX();
    //get hippo's y pos
    byte getY();
    //get frame number
    byte getFrame();
    byte getHealth();
    bool attacking();
    bool getFacing();
    void damage(byte amount);
    bool isDead();
    //update vulture
    void updateHippo();

  private:
	static const byte maxAttackFrames = 20;
    byte x;
    byte y;
    byte w;
    int health = 50;
    byte frame;
    byte attackFrames = maxAttackFrames;
    byte moveSpeed = 1;
    bool isAttacking = false;
    bool facingRight = false;
    bool moveDown = true;

    //move vulture
    void moveForward();
    //attack
    void attack();
};
