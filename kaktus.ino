#include <Arduboy2.h>

Arduboy2 ard;

int shotsInRound=2;

class Player {
  public:
  int x=3;
  int y=32;
  int speedMove=1;
  int score=0;
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
  int x=-1;
  int y=-1;
  int speedMove=3;

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
  bulletRight.speedMove=-3;
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!(ard.nextFrame()))
   return;
  ard.pollButtons();
  ard.clear();


  controls();
  //controls2(left, LEFT_BUTTON, bulletLeft);
  //controls2(right, B_BUTTON, bulletRight);
    
  left.moving();
  right.moving();

  shooting();

  collision();

  ard.drawRect(left.x,left.y,8,8,WHITE);
  ard.drawRect(right.x,right.y,8,8,WHITE);
  ard.drawRect(bulletLeft.x,bulletLeft.y,2,2,WHITE);
  ard.drawRect(bulletRight.x,bulletRight.y,2,2,WHITE);
  ard.setCursor(30,0);
  ard.print(left.score);
  ard.setCursor(80,0);
  ard.print(right.score);
  ard.display();
}

void controls() { //************CONTROLS******************
  
  if( ard.justPressed(LEFT_BUTTON) == true and left.ammo==true and left.shooting==false) {
    left.bounce();
    bulletLeft.x=left.x;
    bulletLeft.y=left.y;
   
    left.shooting=true;
    bulletLeft.moving();
    left.ammo=false;
     
  }

  if( ard.justPressed(B_BUTTON) == true and right.ammo==true and right.shooting==false) {
    right.bounce();
    bulletRight.x=right.x;
    bulletRight.y=right.y;

    right.shooting=true;
    bulletRight.moving();
    right.ammo=false;
  
  }


}

void controls2(Player player, uint8_t button, Bullet bullet) {

   if( ard.justPressed(button) == true and player.ammo==true and player.shooting==false) {
   player.bounce();
   bullet.x=player.x;
   bullet.y=player.y;
   
   player.shooting=true;
   player.ammo=false;
     
  }
}

void shooting() {
    if (left.shooting==true) bulletLeft.moving();
    if (right.shooting==true) bulletRight.moving();

    if (left.ammo==false and right.ammo==false) {
      left.ammo=true;
      right.ammo=true;
      
    }

    if (bulletRight.x<0) right.shooting=false;
    if (bulletLeft.x>164) left.shooting=false;
}

bool checkCollision(Player player, Bullet bullet) {
   if (player.x+8>=bullet.x and player.x<=bullet.x and player.y<=bullet.y and player.y+8>=bullet.y) {
    return true;
   }
   else return false;

}

void collision() {
  
  if (checkCollision(left, bulletRight)) {
    right.score+=1;
    bulletRight.y=-10;
    right.shooting=false;
  }
  if (checkCollision(right, bulletLeft)) {
    left.score+=1;
    bulletLeft.y=-10;
    left.shooting=false;
  }
}



