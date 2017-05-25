#ifndef player_h
#define player_h
#define MOVE_FRAMES 15
#define INVINCIBLE_FRAMES 5
#ifndef Arduboy2_h
#include <Arduboy2.h>
#endif
#endif

class Player
{
  public:
    Player(byte xpos, byte ypos, byte pSize);
    Player(){}

    //get player's x
    byte getX();
    //get player's y
    byte getY();
    //get current frame for player
    byte getFrame();
    //get current health
    byte getHealth();
    //set health
    void setHealth(byte amount);
    //get bounding box
    Rect getRect();
    //take damage
    void damage(byte amount);
    //check if invincible
    bool checkInvin();
    //check if player died
    bool isDead();
    bool getFacing();
    //update the player and with a button if one was pressed
    void updatePlayer(char buttonPressed, char comboButton);

  private:
	static const byte maxAttackFrames = 15;
    Rect rect;
    byte x;
    byte y;
    byte oldY;
    byte frame;
    int health = 50;
    byte moveFrame = 0;
    byte invincibleFrame = 0;
    byte playerSize;
    byte moveSpeed = 1;
    byte MAX_JUMP_DIST = 30;
    bool isFacingRight = true;
    bool isJumping = false;
    bool isInAir = false;
    bool isFalling = false;
    bool isInvincible = false;
    bool doMove = false;
    bool moveRight = true;
    bool reverseMove = false;
    bool died = false;

    //make player jump
    void jump();
    //lateral movement
    void horizontalMove();
    //move player
    void movePlayer();
    //attack
    void attack();
};

