#ifndef hippo_h
#define hippo_h
#define ATTACK_FRAMES 20
#ifndef Arduboy2_h
#include <Arduboy2.h>
#endif
#endif

class Hippo
{
  public:
    Hippo(byte xpos, byte ypos, byte len);
    Hippo() {}
    ~Hippo() {};

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
    byte x;
    byte y;
    byte w;
    int health = 50;
    byte frame;
    byte attackFrames = ATTACK_FRAMES;
    byte moveSpeed = 1;
    bool isAttacking = false;
    bool facingRight = false;
    bool moveDown = true;

    //move vulture
    void moveForward();
    //attack
    void attack();
};
