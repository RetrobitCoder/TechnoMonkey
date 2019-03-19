#include <Arduboy2.h>
#include <Sprites.h>
#include "Bitmaps.h"
#include "Bosses.h"

enum class GameState : unsigned char
{
	Title, Map, Play, Pause, Win, GameOver
};

#define SELECT_SIZE 4

struct attack
{
  Rect rect;
  byte damage;
  byte moveSpeed;
  byte frame;
  bool isFacingRight;
  bool isNull;
  bool isShield;
} bossAttack1, bossAttack2, bossAttack3, playerAttack1, playerAttack2, playerAttack3;

struct attack bossAttacks[3];
struct attack playerAttacks[3];

GameState gameState = GameState::Title;
byte lives = 3;
bool bossesClear = false;
bool invertRect = false;
bool isFighting = false;
bool attacked = false;
int bossIndex = 0;
//bear, vulture, hippo, lion, elephant, final
int bossPoints[] = {25, 10, WIDTH / 2 - 5, HEIGHT / 2, 35, 55, 90, 55, WIDTH - 10, 40, WIDTH / 2, 10};

bool bearBeat = false;
bool vultureBeat = false;
bool hippoBeat = false;
bool lionBeat = false;
bool elephantBeat = false;

Arduboy2 ab;
Sprites sprites;
Rect rect;

Player player;
Elephant bossElephant;
Bear bossBear;
Vulture bossVulture;
Hippo bossHippo;
Lion bossLion;
Zookeeper finalBoss;

void setup()
{
  ab.begin();
  ab.clear();
  sprites.drawSelfMasked(0,0, ArduboyTitle_RetrobitCoder, 0);
  ab.display();
  ab.delayShort(3000);
}

//draw title screen
void titleScreen()
{
  ab.drawBitmap(0, 0, TechnoMonkeyTitle, WIDTH, HEIGHT, WHITE);
  if (ab.pressed(A_BUTTON))
  {
    gameState = GameState::Map;
    ab.delayShort(200);
  }

  ab.setCursor(40, HEIGHT - 8);
  ab.print("Press A Button");

  bearBeat = false;
  vultureBeat = false;
  lionBeat = false;
  hippoBeat = false;
  elephantBeat = false;
}

//draw boss select screen
void mapScreen()
{
  if (lives == 0) gameState = GameState::GameOver;
  else
  {
    ab.drawBitmap(0, 0, Map, WIDTH, HEIGHT);

    if (ab.justPressed(LEFT_BUTTON)) bossIndex--;
    else if (ab.justPressed(RIGHT_BUTTON)) bossIndex++;

    if(bearBeat && vultureBeat && lionBeat && hippoBeat && elephantBeat) bossesClear = true;
    
    if (bossesClear)
    {
      if (bossIndex > 5 && bossesClear) bossIndex = 0;
      else if (bossIndex < 0 && bossesClear) bossIndex = 5;
    }
    else
    {
      if (bossIndex > 4) bossIndex = 0;
      else if (bossIndex < 0) bossIndex = 4;
    }

    byte x = bossPoints[2 * bossIndex];
    byte y = bossPoints[2 * bossIndex + 1];

    if (invertRect && ab.everyXFrames(7)) ab.fillRect(x, y, SELECT_SIZE, SELECT_SIZE, WHITE);
    else ab.fillRect(x, y, SELECT_SIZE, SELECT_SIZE, BLACK);

    invertRect = !invertRect;

    if (ab.justPressed(B_BUTTON))
    {
      gameState = GameState::Play;
      bossAttack1.isNull = true;
      bossAttack2.isNull = true;
      bossAttack3.isNull = true;

      bossAttacks[0] = bossAttack1;
      bossAttacks[1] = bossAttack2;
      bossAttacks[2] = bossAttack3;

      playerAttack1.isNull = true;
      playerAttack2.isNull = true;
      playerAttack3.isNull = true;

      playerAttacks[0] = playerAttack1;
      playerAttacks[1] = playerAttack2;
      playerAttacks[2] = playerAttack3;

      attacked = false;
      ab.delayShort(200);
    }
  }
}

void pauseScreen()
{
  ab.drawRect(WIDTH/2 - 20, HEIGHT/2 - 5, 40, 12);
  ab.setCursor(WIDTH/2 - 18, HEIGHT/2 - 3);
  ab.print("Paused");
  if(ab.justPressed(DOWN_BUTTON)) gameState = GameState::Play;
}

void gameOver()
{
  ab.setCursor(WIDTH / 2 - (4 * 6), HEIGHT / 2);
  ab.print("GAME OVER");
  ab.setCursor(10, HEIGHT - 12);
  ab.print("Press A to Restart");

  if (ab.justPressed(A_BUTTON))
  {
    gameState = GameState::Title;
    lives = 3;
    ab.delayShort(200);
  }
}

void winScreen()
{
  ab.setCursor(0, 0);
  ab.print("Thanks for Playing");
  ab.setCursor(0, 10);
  ab.print("Arduboyjam:");
  ab.setCursor(0, 20);
  ab.print("The Zoo had to close!");
  ab.setCursor(0, 30);
  ab.print("Credits");
  ab.setCursor(0, 40);
  ab.print("Art and Programming");
  ab.setCursor(0, 50);
  ab.print("Zachariah Falgout");
}

void updateRect(byte x, byte y)
{
  rect.x = x;
  rect.y = y;
}

void updatePlayerAttacks()
{
  bool deletePlayerAttacks[3] = {false, false, false};
  int i = 0;

  for (struct attack weapon : playerAttacks)
  {
    if (!weapon.isNull)
    {
      if (weapon.rect.x <= weapon.moveSpeed || weapon.rect.x >= WIDTH - weapon.moveSpeed) deletePlayerAttacks[i] = true;
      else
      {
        if (weapon.isFacingRight) weapon.rect.x += weapon.moveSpeed;
        else weapon.rect.x -= weapon.moveSpeed;
      }
      playerAttacks[i] = weapon;
    }
    i++;
  }

  for (int i = 0; i < 3; i++)
  {
    if (deletePlayerAttacks[i])
    {
      playerAttacks[i].isNull = true;
    }
  }
}

void updateBossAttacks()
{
  bool deleteBossAttacks[3] = {false, false, false};
  int i = 0;

  for (struct attack weapon : bossAttacks)
  {
    if (!weapon.isNull)
    {
      if (ab.collide(weapon.rect, player.getRect()))
      {
        player.damage(weapon.damage);
        deleteBossAttacks[i] = true;
      }
      else if (weapon.rect.x <= weapon.moveSpeed || weapon.rect.x >= WIDTH - weapon.moveSpeed) deleteBossAttacks[i] = true;
      else
      {
        if (weapon.isFacingRight) weapon.rect.x += weapon.moveSpeed;
        else weapon.rect.x -= weapon.moveSpeed;
      }
      bossAttacks[i] = weapon;
    }
    i++;
  }

  for (int i = 0; i < 3; i++)
  {
    if (deleteBossAttacks[i])
    {
      bossAttacks[i].isNull = true;
      attacked = false;
    }
  }
}

//fighting against bear boss
void bearFight()
{
  if (!isFighting)
  {
    bossBear = Bear(WIDTH - bear[0], HEIGHT - bear[1], bear[0]);
    rect.x = bossBear.getX();
    rect.y = bossBear.getY() + 5;
    rect.width = bear[0] - 10;
    rect.height = bear[1] - 5;
    isFighting = true;
  }
  else
  {
    if (bossBear.attacking())
    {
      if (!attacked)
      {
        attacked = true;
        byte offset = 0;
        int i = 0;
        for (struct attack weapon : bossAttacks)
        {
          if (weapon.isNull && i < 2)
          {
            weapon.isNull = false;
            weapon.isFacingRight = bossBear.getFacing();

            if (weapon.isFacingRight)
            {
              weapon.rect.x = bossBear.getX() + bear[0] + offset;
              weapon.frame = 0;
            }
            else
            {
              weapon.rect.x = bossBear.getX() - offset;
              weapon.frame = 1;
            }

            weapon.rect.y = bossBear.getY() + 5;
            weapon.rect.width = claws[0];
            weapon.rect.height = claws[1];

            weapon.damage = 5;
            weapon.moveSpeed = 10;

            bossAttacks[i] = weapon;

            offset += claws[0] + 32;
          }
          i++;
        }
      }
      else attacked = true;
    }

    for (struct attack weapon : bossAttacks)
    {
      if (!weapon.isNull)
      {
        sprites.drawSelfMasked(weapon.rect.x, weapon.rect.y, claws, weapon.frame);
      }
    }

    sprites.drawSelfMasked(bossBear.getX(), bossBear.getY(), bear, bossBear.getFrame());
    ab.drawFastHLine(WIDTH - bossBear.getHealth(), 0, bossBear.getHealth());

    updateRect(bossBear.getX(), bossBear.getY());
    bossBear.damage(collision(rect));

    if (ab.everyXFrames(6))
    {
      bossBear.updateBear();
      updateBossAttacks();
    }

    if (bossBear.isDead())
    {
      gameState = GameState::Map;
      bearBeat = true;
      isFighting = false;
    }
  }
}

//fighting against vulture boss
void vultureFight()
{
  if (!isFighting)
  {
    bossVulture = Vulture(WIDTH - vulture[0], HEIGHT - vulture[1], vulture[0]);
    rect.x = bossVulture.getX();
    rect.y = bossVulture.getY();
    rect.width = vulture[0];
    rect.height = vulture[1];
    isFighting = true;
  }
  else
  {
    if (bossVulture.attacking())
    {
      if (!attacked)
      {
        attacked = true;
        int i = 0;
        for (struct attack weapon : bossAttacks)
        {
          if (weapon.isNull && i < 1)
          {
            weapon.isNull = false;
            weapon.isFacingRight = bossVulture.getFacing();
            weapon.isShield = true;

            if (weapon.isFacingRight)
            {
              weapon.rect.x = bossVulture.getX() + vulture[0];
              weapon.frame = 0;
            }
            else
            {
              weapon.rect.x = bossVulture.getX() - vulture[0];
              weapon.frame = 0;
            }

            weapon.rect.y = bossVulture.getY();
            weapon.rect.width = feathers[0];
            weapon.rect.height = feathers[1];

            weapon.damage = 5;
            weapon.moveSpeed = 5;

            bossAttacks[i] = weapon;
          }
          i++;
        }
      }
      else attacked = true;
    }

    for (struct attack weapon : bossAttacks)
    {
      if (!weapon.isNull)
      {
        sprites.drawSelfMasked(weapon.rect.x, weapon.rect.y, feathers, weapon.frame);
      }
    }

    sprites.drawSelfMasked(bossVulture.getX(), bossVulture.getY(), vulture, bossVulture.getFrame());
    ab.drawFastHLine(WIDTH - bossVulture.getHealth(), 0, bossVulture.getHealth());
    updateRect(bossVulture.getX(), bossVulture.getY());
    bossVulture.damage(collision(rect));

    if (ab.everyXFrames(6))
    {
      bossVulture.updateVulture();
      updateBossAttacks();
    }

    if (bossVulture.isDead())
    {
      gameState = GameState::Map;
      vultureBeat = true;
      isFighting = false;
    }
  }
}

//fighting against hippo boss
void hippoFight()
{
  if (!isFighting)
  {
    bossHippo = Hippo(WIDTH - hippo[0], HEIGHT - hippo[1], hippo[0]);
    rect.x = bossHippo.getX();
    rect.y = bossHippo.getY();
    rect.width = hippo[0];
    rect.height = hippo[1];
    isFighting = true;
  }
  else
  {
    if (bossHippo.attacking())
    {
      if (!attacked)
      {
        attacked = true;
        byte offset = 0;
        int i = 0;
        for (struct attack weapon : bossAttacks)
        {
          if (weapon.isNull && i < 3)
          {
            weapon.isNull = false;
            weapon.isFacingRight = bossHippo.getFacing();

            if (weapon.isFacingRight)
            {
              weapon.rect.x = bossHippo.getX() + hippo[0] + offset;
              weapon.frame = 0;
            }
            else
            {
              weapon.rect.x = bossHippo.getX() - offset;
              weapon.frame = 0;
            }

            weapon.rect.y = bossHippo.getY() + 5;
            weapon.rect.width = bomb[0];
            weapon.rect.height = bomb[1] / 2;

            weapon.damage = 5;
            weapon.moveSpeed = 5;

            bossAttacks[i] = weapon;

            offset += 2 * bomb[0];
          }
          i++;
        }
      }
      else attacked = true;
    }

    for (struct attack weapon : bossAttacks)
    {
      if (!weapon.isNull)
      {
        sprites.drawSelfMasked(weapon.rect.x, weapon.rect.y, bomb, weapon.frame);
      }
    }

    sprites.drawSelfMasked(bossHippo.getX(), bossHippo.getY(), hippo, bossHippo.getFrame());
    ab.drawFastHLine(WIDTH - bossHippo.getHealth(), 0, bossHippo.getHealth());
    updateRect(bossHippo.getX(), bossHippo.getY());
    bossHippo.damage(collision(rect));

    if (ab.everyXFrames(6))
    {
      bossHippo.updateHippo();
      updateBossAttacks();
    }

    if (bossHippo.isDead())
    {
      gameState = GameState::Map;
      hippoBeat = true;
      isFighting = false;
    }
  }
}

//fighting against lion boss
void lionFight()
{
  if (!isFighting)
  {
    bossLion = Lion(WIDTH - lion[0], HEIGHT - lion[1], lion[0]);
    rect.x = bossLion.getX();
    rect.y = bossLion.getY();
    rect.width = lion[0];
    rect.height = lion[1];
    isFighting = true;
  }
  else
  {
    if (bossLion.attacking())
    {
      if (!attacked)
      {
        attacked = true;
        int i = 0;
        for (struct attack weapon : bossAttacks)
        {
          if (weapon.isNull && i < 1)
          {
            weapon.isNull = false;
            weapon.isFacingRight = bossLion.getFacing();

            if (weapon.isFacingRight)
            {
              weapon.rect.x = bossLion.getX() + lion[0];
              weapon.frame = 0;
            }
            else
            {
              weapon.rect.x = bossLion.getX();
              weapon.frame = 1;
            }

            weapon.rect.y = bossLion.getY() + 5;
            weapon.rect.width = roars[0];
            weapon.rect.height = roars[1];

            weapon.damage = 5;
            weapon.moveSpeed = 6;

            bossAttacks[i] = weapon;
          }
          i++;
        }
      }
      else attacked = true;
    }

    for (struct attack weapon : bossAttacks)
    {
      if (!weapon.isNull)
      {
        sprites.drawSelfMasked(weapon.rect.x, weapon.rect.y, roars, weapon.frame);
      }
    }

    sprites.drawSelfMasked(bossLion.getX(), bossLion.getY(), lion, bossLion.getFrame());
    ab.drawFastHLine(WIDTH - bossLion.getHealth(), 0, bossLion.getHealth());
    updateRect(bossLion.getX(), bossLion.getY());
    bossLion.damage(collision(rect));

    if (ab.everyXFrames(6))
    {
      bossLion.updateLion();
      updateBossAttacks();
    }

    if (bossLion.isDead())
    {
      gameState = GameState::Map;
      lionBeat = true;
      isFighting = false;
    }
  }
}

//fighting against elephant boss
void elephantFight()
{
  if (!isFighting)
  {
    bossElephant = Elephant(WIDTH - elephant[0], HEIGHT - elephant[1], elephant[0]);
    rect.x = bossElephant.getX();
    rect.y = bossElephant.getY() + 10;
    rect.width = elephant[0] - 5;
    rect.height = elephant[1];
    isFighting = true;
  }
  else
  {
    if (bossElephant.attacking())
    {
      if (!attacked)
      {
        attacked = true;
        int i = 0;
        for (struct attack weapon : bossAttacks)
        {
          if (weapon.isNull && i < 1)
          {
            weapon.isNull = false;
            weapon.isFacingRight = bossElephant.getFacing();

            if (weapon.isFacingRight)
            {
              weapon.rect.x = bossElephant.getX() + elephant[0];
              weapon.frame = 0;
            }
            else
            {
              weapon.rect.x = bossElephant.getX();
              weapon.frame = 1;
            }

            weapon.rect.y = bossElephant.getY() + 5;
            weapon.rect.width = missiles[0];
            weapon.rect.height = missiles[1];

            weapon.damage = 5;
            weapon.moveSpeed = 6;

            bossAttacks[i] = weapon;
          }
          i++;
        }
      }
      else attacked = true;
    }

    for (struct attack weapon : bossAttacks)
    {
      if (!weapon.isNull)
      {
        sprites.drawSelfMasked(weapon.rect.x, weapon.rect.y, missiles, weapon.frame);
      }
    }

    sprites.drawSelfMasked(bossElephant.getX(), bossElephant.getY(), elephant, bossElephant.getFrame());
    ab.drawFastHLine(WIDTH - bossElephant.getHealth(), 0, bossElephant.getHealth());
    updateRect(bossElephant.getX(), bossElephant.getY());
    bossElephant.damage(collision(rect));

    if (ab.everyXFrames(6))
    {
      bossElephant.updateElephant();
      updateBossAttacks();
    }

    if (bossElephant.isDead())
    {
      gameState = GameState::Map;
      elephantBeat = true;
      isFighting = false;
    }
  }
}

//fighting against final boss
void finalFight()
{
  if (!isFighting)
  {
    finalBoss = Zookeeper(WIDTH - zookeeper[0], HEIGHT - zookeeper[1], zookeeper[0]);
    rect.x = finalBoss.getX();
    rect.y = finalBoss.getY();
    rect.width = zookeeper[0];
    rect.height = zookeeper[1];
    isFighting = true;
  }
  else
  {
    if (finalBoss.attacking())
    {
      if (!attacked)
      {
        attacked = true;
        int i = 0;
        for (struct attack weapon : bossAttacks)
        {
          if (weapon.isNull && i < 1)
          {
            weapon.isNull = false;
            weapon.isFacingRight = finalBoss.getFacing();

            if (weapon.isFacingRight)
            {
              weapon.rect.x = finalBoss.getX() + zookeeper[0];
              weapon.frame = 0;
            }
            else
            {
              weapon.rect.x = finalBoss.getX();
              weapon.frame = 0;
            }

            weapon.rect.y = finalBoss.getY();
            weapon.rect.width = technobeam[0];
            weapon.rect.height = technobeam[1];

            weapon.damage = 10;
            weapon.moveSpeed = 6;

            bossAttacks[i] = weapon;
          }
          i++;
        }
      }
      else attacked = true;
    }

    for (struct attack weapon : bossAttacks)
    {
      if (!weapon.isNull)
      {
        sprites.drawSelfMasked(weapon.rect.x, weapon.rect.y, technobeam, weapon.frame);
      }
    }

    sprites.drawSelfMasked(finalBoss.getX(), finalBoss.getY(), zookeeper, finalBoss.getFrame());
    ab.drawFastHLine(WIDTH - finalBoss.getHealth(), 0, finalBoss.getHealth());
    updateRect(finalBoss.getX(), finalBoss.getY());
    finalBoss.damage(collision(rect));

    if (ab.everyXFrames(6))
    {
      finalBoss.updateZookeeper();
      updateBossAttacks();
    }

    if (finalBoss.isDead())
    {
      gameState = GameState::Win;
      isFighting = false;
    }
  }
}

//handle updating and drawing player
void updatePlayer()
{
  char button = ' ';
  char combo = ' ';

  if (ab.pressed(B_BUTTON)) button = 'B';
  if (ab.pressed(RIGHT_BUTTON)) button = 'R';
  if (ab.pressed(LEFT_BUTTON)) button = 'L';
  if (ab.pressed(B_BUTTON + RIGHT_BUTTON))
  {
    button = 'B';
    combo = 'R';
  }
  if (ab.pressed(B_BUTTON + LEFT_BUTTON))
  {
    button = 'B';
    combo = 'L';
  }

  if (!isFighting) player = Player(1, HEIGHT - monkey[1], monkey[0]);
  else
  {
    if (ab.justPressed(A_BUTTON))
    {
      int i = 0;
      for (struct attack weapon : playerAttacks)
      {
        if (weapon.isNull)
        {
          weapon.isNull = false;
          weapon.isFacingRight = player.getFacing();

          if (weapon.isFacingRight)
          {
            weapon.rect.x = player.getX() + monkey[0];
            weapon.frame = 0;
          }
          else
          {
            weapon.rect.x = player.getX();
            weapon.frame = 0;
          }

          weapon.rect.y = player.getY() + 9;
          weapon.rect.width = shot[0];
          weapon.rect.height = shot[1] / 2;

          weapon.damage = 2;
          weapon.moveSpeed = 1;

          playerAttacks[i] = weapon;
          break;
        }
        i++;
      }
    }

    for (struct attack weapon : playerAttacks)
    {
      if (!weapon.isNull)
      {
        sprites.drawSelfMasked(weapon.rect.x, weapon.rect.y, shot, weapon.frame);
      }
    }

    if (player.checkInvin() && ab.everyXFrames(2)) sprites.drawErase(player.getX(), player.getY(), monkey, player.getFrame());
    else sprites.drawSelfMasked(player.getX(), player.getY(), monkey, player.getFrame());

    ab.setCursor(WIDTH / 2 - 3, 0);
    ab.print(lives);
    ab.drawFastHLine(0, 0, player.getHealth());
    player.updatePlayer(button, combo);
    updatePlayerAttacks();

  }
}

//check for collisions, players and attacks
byte collision(Rect bossRect)
{
  if (ab.collide(bossRect, player.getRect())) player.damage(2);

  byte damage = 0;
  bool deletePlayerAttacks[3] = {false, false, false};

  for (int i = 0; i < 3; i++)
  {
    if (!playerAttacks[i].isNull && ab.collide(bossRect, playerAttacks[i].rect))
    {
      damage += playerAttacks[i].damage;
      deletePlayerAttacks[i] = true;
    }
  }

  for (int i = 0; i < 3; i++)
  {
    if (deletePlayerAttacks[i])
    {
      playerAttacks[i].isNull = true;
    }
  }
  return damage;
}

//main game loop
void gameLoop()
{
  ab.drawFastHLine(0, HEIGHT - 1, WIDTH);
  if (ab.justPressed(DOWN_BUTTON))
  {
    gameState = GameState::Pause;
  }
  else
  {
    updatePlayer();

    if (lives == 0)
    {
      gameState = GameState::GameOver;
      isFighting = false;
    }
    else if (player.isDead())
    {
      gameState = GameState::Map;
      isFighting = false;
      //player.setHealth(50);
      lives--;
    }
    else
    {
      switch (bossIndex)
      {
        case 0: //bear
          bearFight();
          break;
        case 1: //vulture
          vultureFight();
          break;
        case 2: //hippo
          hippoFight();
          break;
        case 3: //lion
          lionFight();
          break;
        case 4: //elephant
          elephantFight();
          break;
        case 5: //final
          finalFight();
          break;
      }
    }
  }
}

//main loop
void loop()
{
  if (!ab.nextFrame()) return;

  ab.clear();
  ab.pollButtons();

  switch (gameState)
  {
    case GameState::Title:
      titleScreen();
      break;
    case GameState::Map:
      mapScreen();
      break;
    case GameState::Play:
      gameLoop();
      break;
    case GameState::Pause:
      pauseScreen();
      break;
    case GameState::GameOver:
      gameOver();
      break;
    case GameState::Win:
      winScreen();
      break;
  }

  ab.display();
}
