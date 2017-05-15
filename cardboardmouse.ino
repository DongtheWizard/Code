#include <Event.h>
#include <Timer.h>

Timer ytimer;
Timer xtimer;
 
struct {
    uint8_t button;
    int8_t x;
    int8_t y;
    int8_t wheel;   /* Not yet implemented */
} mouseReport;

uint8_t nullReport[4] = { 0, 0, 0, 0 };
int vry = A0;
int vrx = A1;
int lvrx = A2;
int lvry = A3;

int fbl = 11;
int bbl = 10;
int fbr = 8;
int bbr = 9;

int t =7;
int o = 6;
int i = 5;
int e = 4;

int xaxis = 0;
int yaxis = 0;
int leftclick = 0;
int rightclick = 0;


int leftstart = 515;//515
int rightstart = 515;//515
int upstart = 528;//528
int downstart = 528;//528

  //stich is sensitive i think i hurt its feelings
int errorval = 5;// might have to increase for up and down
int verterr = 5;

int xcounter = 0;
int ycounter = 0;

//instead of changing speed look to model the mouse after an acutal mouse
//i think it is made by the speed of the input or the speed relative to the change of input
//for example
//change of startpos to current/time
//if change is 10 per second speed = 5
//if change is 50 per second speed 10
//speed checkers if this pos and last pos 
//values are arbitrary
 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(fbr, INPUT_PULLUP);//all buttons are using input pullup cause pull up game strong
  pinMode(bbr, INPUT_PULLUP);
  leftclick = digitalRead(fbr);
  rightclick = digitalRead(bbr);
   xaxis = analogRead(vrx);
   yaxis = analogRead(vry);
  rightstart+=errorval;
  leftstart -= errorval;
  upstart += verterr;
  downstart-= verterr;
  
 xtimer.every(1000, xcount);
 ytimer.every(1000, ycount);
 
}

void loop() {
  
  leftclick = digitalRead(fbr);
  rightclick = digitalRead(bbr);
   xaxis = analogRead(vrx);
   yaxis = analogRead(vry);
   mightymouse();

}
void gogomouse(){
  Serial.write((uint8_t *)&mouseReport, 4);
    Serial.write((uint8_t *)&nullReport, 4);
}


void mightymouse(){
    //left click   
if(leftclick == LOW)//sem for hold or protothread
  mouseReport.button = B00000001; 

  //rightclick 
if(rightclick == LOW)
  mouseReport.button =  B00000010; 
    
  //buttonstate = off
if((leftclick == HIGH) && (rightclick == HIGH))
  mouseReport.button = 0; 

// no movement 
 if(xaxis <= rightstart && xaxis >= leftstart)
      mouseReport.x = 0;
 if(yaxis <= upstart && yaxis >= downstart)
      mouseReport.y = 0;


 //mouse up
if(upstart < yaxis){
      //right
      if( yaxis > upstart && yaxis <=(upstart +200))
        mouseReport.y = -1;
      if(yaxis > (upstart +200) && yaxis <= 1000 )
        mouseReport.y = -5;
      if(upstart > 1000){
        
        ytimer.update();
        if(ycounter == 3 || mouseReport.y == 15){
          mouseReport.y = -15;
          ycounter = 0;
        }
        else
          mouseReport.y = -10;
      }
      else
        ycounter = 0;
}
//mouse down
if(downstart > yaxis){//make a function
    //left
    if( yaxis < downstart && yaxis >=(downstart -200))
        mouseReport.y = 1;
      if(yaxis < (downstart-200) && yaxis >= 20 )
        mouseReport.y = 5;
      if(yaxis < 20){
        ytimer.update();
        if(ycounter == 3 || mouseReport.y == -15){
          mouseReport.y = 15;
          ycounter = 0;
        }
        else
          mouseReport.y = 10;
      }
      else
        ycounter = 0;
}
      
 //mouse right
if(rightstart < xaxis){
      //right
      if( xaxis > rightstart && xaxis <=(rightstart +200))
        mouseReport.x = 1;
      if(xaxis > (rightstart +200) && xaxis <= 1000 )
        mouseReport.x = 5;
      if(xaxis > 1000){
        xtimer.update();
        if(xcounter == 3 || mouseReport.x == 15){
          mouseReport.x = 15;
          xcounter = 0;
        }
        else
          mouseReport.x = 10;
      }
      else
        xcounter = 0;
}
//mouse left
if(leftstart > xaxis){
    //left
    if( xaxis < leftstart && xaxis >=(leftstart -200))
        mouseReport.x = -1;
      if(xaxis < (leftstart-200) && xaxis >= 20 )
        mouseReport.x = -5;
      if(xaxis < 20){
        xtimer.update();
        if(xcounter == 3 || mouseReport.x == -15){
          mouseReport.x = -15;
          xcounter = 0;
        }
        else
          mouseReport.x = -10;
      }
      else
        xcounter = 0;
}
 
  gogomouse();
  
}
void ycount(){
  ycounter++;
}
void xcount(){
  xcounter++;
}
void mousexupdate(){
  
}

