#include <Arduboy2.h>

Arduboy2 ard;

int leftX = 3;
int leftY = 32;
int leftSpeed = 1;
bool leftAmmo=1;
bool shootLeft=0;
int leftBulletX=0;
int leftBulletY=0;

int rightX = 117;
int rightY = 32;
int rightSpeed=1;
bool rightAmmo=1;


void setup() {
  // put your setup code here, to run once:
  ard.begin();
  ard.setFrameRate(45);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!(ard.nextFrame()))
   return;
  ard.pollButtons();
  ard.clear();


  players();
  controls();
  
  ard.print("Hello!");
  ard.drawRect(leftX,leftY,8,8,WHITE);
  ard.drawRect(rightX,rightY,8,8,WHITE);
  ard.display();
}

void controls() { //************CONTROLS******************
  
  if( ard.justPressed(LEFT_BUTTON) == true) {
    leftSpeed=leftSpeed*-1;
    if (leftAmmo==true) {
      leftAmmo=0;
      leftBulletX=leftX;
      leftBulletY=leftY;
      shootLeft=true;
    }
  }


}

void players() { //************PLAYERS******************
   leftY+=leftSpeed;

   if (leftY<=0 and leftSpeed<0) leftSpeed=leftSpeed*-1;
   if (leftY>=56 and leftSpeed>0) leftSpeed=leftSpeed*-1;

   if (shootLeft==true) {
    leftBulletX+=2;
    ard.drawRect(leftBulletX,leftBulletY,2,2,WHITE);
    if (leftBulletX>128) {
      leftAmmo=1;
      shootLeft=false;
    }
    }
}

