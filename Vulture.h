#ifndef vulture_h
#define vulture_h
#define ATTACK_FRAMES 10
#ifndef Arduboy2_h
#include <Arduboy2.h>
#endif
#endif

class Vulture
{
  public:
    Vulture(byte xpos, byte ypos, byte len);
    Vulture(){}
    ~Vulture(){};

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
    byte x;
    byte y;
    byte w;
    int health = 50;
    byte frame;
    int frameStep;
    byte attackFrames = ATTACK_FRAMES;
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
