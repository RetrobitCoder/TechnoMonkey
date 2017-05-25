#ifndef elephant_h
#define elephant_h
#define ATTACK_FRAMES 10
#ifndef Arduboy2_h
#include <Arduboy2.h>
#endif
#endif

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
    byte x;
    byte y;
    byte w;
    int health = 50;
    byte frame;
    byte attackFrames = ATTACK_FRAMES;
    byte moveSpeed = 5;
    bool isAttacking = false;
    bool facingRight = false;

    //move elephant
    void moveForward();
    //attack
    void attack();
};

