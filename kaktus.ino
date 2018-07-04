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

  }
};

struct Bullet {
  int x=1;
  int y=1;
  int speedMove=1;

  void moving() {
    x+=speedMove;
  }
};

Player left;
Player right;



void setup() {
  // put your setup code here, to run once:
  ard.begin();
  ard.setFrameRate(45);
  right.x=117;
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!(ard.nextFrame()))
   return;
  ard.pollButtons();
  ard.clear();


  players();
  controls();

  left.moving();
  right.moving();


  ard.drawRect(left.x,left.y,8,8,WHITE);
  ard.drawRect(right.x,right.y,8,8,WHITE);
  
  ard.print("Hello!");
  ard.display();
}

void controls() { //************CONTROLS******************
  
  if( ard.justPressed(LEFT_BUTTON) == true) {
    left.bounce();
    if (left.ammo==true) {

      left.shoot();
    }
  }


}

void players() { //************PLAYERS******************

}

