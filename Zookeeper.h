#ifndef zookeeper_h
#define zookeeper_h
#ifndef Arduboy2_h
#include <Arduboy2.h>
#endif
#endif

class Zookeeper
{
  public:
    Zookeeper(byte xpos, byte ypos, byte len);
    Zookeeper(){}

    //get Zookeeper's x pos
    byte getX();
    //get Zookeeper's y pos
    byte getY();
    //get frame number
    byte getFrame();
    byte getHealth();
    bool attacking();
    bool getFacing();
    void damage(byte amount);
    bool isDead();
    //update Zookeeper
    void updateZookeeper();

  private:
	static const byte maxAttackFrames = 20;
    byte x;
    byte y;
    byte w;
    int health = 60;
    byte frame;
    byte attackFrames = maxAttackFrames;
    byte moveSpeed = 5;
    bool isAttacking = false;
    bool facingRight = false;

    //move Zookeeper
    void moveForward();
    //attack
    void attack();
};

