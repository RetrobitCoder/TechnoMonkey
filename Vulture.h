#ifndef vulture_h
#define vulture_h
#ifndef Arduboy2_h
#include <Arduboy2.h>
#endif
#endif

class Vulture
{
  public:
    Vulture(byte xpos, byte ypos, byte len);
    Vulture(){}

    //get vulture's x pos
    byte getX();
    //get vulture's y pos
    byte getY();
    //get frame number
    byte getFrame();
    byte getHealth();
    bool attacking();
    bool getFacing();
    void damage(byte amount);
    bool isDead();
    //update vulture
    void updateVulture();

  private:
	static const byte maxAttackFrames = 10;
    byte x;
    byte y;
    byte w;
    int health = 50;
    byte frame;
    int frameStep;
    byte attackFrames = maxAttackFrames;
    byte moveSpeed = 3;
    bool isAttacking = false;
    bool facingRight = false;
    bool moveVertical = true;
    bool moveDown = false;

    //move vulture
    void moveForward();
    //x movement
    void moveX();
    //y movement
    void moveY();
    //attack
    void attack();
};
