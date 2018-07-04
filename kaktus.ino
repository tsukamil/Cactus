#include <Arduboy2.h>

Arduboy2 ard;


class Player {
  public:
  int x=3;
  int y=32;
  int speedMove=1;
  bool ammo=1;
  bool shooting=0;

  void bounce() {
    speedMove=speedMove*-1;
  }

  void moving() {
    y+=speedMove;
    if (y<=0 and speedMove<0) bounce();
    if (y>=56 and speedMove>0) bounce();
    
  }
  
  void shoot() {
    ammo=0;
  }

};

class Bullet {
 public: 
  int x=10;
  int y=10;
  int speedMove=1;

  void moving() {
    x+=speedMove;
  }
};

Player left;
Player right;
Bullet bulletLeft;
Bullet bulletRight;


void setup() {
  // put your setup code here, to run once:
  ard.begin();
  ard.setFrameRate(45);
  right.x=117;
  bulletRight.speedMove=-1;
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!(ard.nextFrame()))
   return;
  ard.pollButtons();
  ard.clear();


  controls();

  left.moving();
  right.moving();

  if (left.shooting==true) bulletLeft.moving();


  ard.drawRect(left.x,left.y,8,8,WHITE);
  ard.drawRect(right.x,right.y,8,8,WHITE);
  ard.drawRect(bulletLeft.x,bulletRight.y,2,2,WHITE);
  ard.setCursor(50,0);
  ard.print(left.x); // DLACZEGO 3??????
  ard.display();
}

void controls() { //************CONTROLS******************
  
  if( ard.justPressed(LEFT_BUTTON) == true) {
    left.bounce();
    bulletLeft.x=left.x;
    bulletLeft.y=left.y;

    if (left.ammo==true) {
   
      left.shooting=true;
     
    }
  }

  if( ard.justPressed(B_BUTTON) == true) {
    right.bounce();
    if (right.ammo==true) {

      right.shoot();
    }
  }


}



