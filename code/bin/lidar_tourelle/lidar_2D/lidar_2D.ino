//Largement inspiré de : www.qcontinuum.org/lidar

#include <Servo.h>
#include <LIDARLite.h>
#include <LiquidCrystal.h>

Servo servoX;
Servo servoY;
LIDARLite lidar;

// Minimum and maximum servo angle in degrees
// Modify to avoid hitting limits imposed by pan/tilt bracket geometry
int minPosX = 0;
int maxPosX = 180;
int minPosY = 60;
int maxPosY = 130;

int buttonPin = A0;
int buttonValue = 0;
int buttonThreshold = 50;
int lastPosX = 0;
int lastPosY = 0;
int loopCount = 0;
int radius = 0;
int lastRadius = 0;
boolean selectButtonPressed = false;
boolean scanning = false;
boolean scanDirection = false;
int scanIncrement = 1;
int posX = (maxPosX + minPosX) / 2;
int posY = (maxPosY + minPosY) / 4;
float pi = 3.14159265;
float deg2rad = pi / 180.0;

int strength;// LiDAR signal strength
int check;// check numerical value storage
int i;
int j=0;
int uart[9];// store data measured by LiDAR
const int HEADER=0x59;// data package frame header

void setup() {
  lidar.begin(0, true);
  lidar.configure(0);
  servoX.attach(2);
  servoY.attach(3);
  servoX.write(posX);
  servoY.write(posY);
  Serial.begin(115200);
  Serial1.begin(115200);//set the Baud rate of LiDAR and Arduino serial port
}

void loop() {
  Serial.println("START----------START----------START----------START"); //------------------------------------------------------------------
    buttonValue = 740;

//  buttonValue = analogRead(buttonPin);
//*************************************************************************
  if (scanning) { 
    if (abs(buttonValue - 741) < buttonThreshold) {
        if (!selectButtonPressed) {
        // switch to manual scan mode
        selectButtonPressed = true;
        scanning = false;
      }
    } else {
      selectButtonPressed = false;
    }
    if (scanDirection) {
      posX += scanIncrement;
    } else {
      posX -= scanIncrement;
    }
    if (posX > maxPosX || posX < minPosX) {
      // hit limit X limit, reverse auto scan direction
      scanDirection = !scanDirection;
      posY += scanIncrement;
      if (posY > maxPosY) {
        // completed auto scan, return to manual scan mode
        scanning = false;
      }
    }
  }
   else {
    if (abs(buttonValue - 741) < buttonThreshold) {
        if (!selectButtonPressed) {
        // switch to auto scan mode
        selectButtonPressed = true;
        scanning = true;
        posX = minPosX;
        posY = minPosY;
        scanDirection = true;
      }
    } else if (abs(buttonValue - 505) < buttonThreshold) {
      // manual scan left
      posX += 1;
     } else if (abs(buttonValue - 329) < buttonThreshold) {
      // manual scan down
      posY -= 1;
    } else if (abs(buttonValue - 145) < buttonThreshold) {
      // manual scan up
      posY += 1;
    } else if (abs(buttonValue - 0) < buttonThreshold) {
      // manual scan right
      posX -= 1;
     } else {
      selectButtonPressed = false;
     }
  }
//*************************************************************************
  posX = min(max(posX, minPosX), maxPosX);
  posY = min(max(posY, minPosY), maxPosY);
  bool moved = moveServos();

  loopCount += 1;
//  Serial.println(loopCount); //------------------------------------------------------------------
  
//*****************RECALIBRAGE OU PAS***************************  
while(j==0) {
  if (Serial1.available()) {
      if(Serial1.read()==HEADER) {
         uart[0]=HEADER;
         delay(1);
         if(Serial1.read()==HEADER) {
             uart[1]=HEADER;
             for(i=2;i<9;i++) {
                 uart[i]=Serial1.read();
                 Serial.println(uart[i]);
                 }
             check=uart[0]+uart[1]+uart[2]+uart[3]+uart[4]+uart[5]+uart[6]+uart[7];
             if(uart[8]==(check&0xff)) {
                 radius=uart[2]+uart[3]*256;// calculate distance value
                 strength=uart[4]+uart[5]*256;// calculate signal strength value               
                 j=1;
}}}}
   if (Serial1.available()) {    
       j=0;       
   }
   } 
//Serial.println(radius);
 j=0;
//***************************************************************  

  if (abs(radius - lastRadius) > 2)
  {
    lastRadius = radius;
  }
  Serial.print("radius :");
  Serial.println(radius);


   // Serial.print("scanning = ");//------------------------------------------------------------------  
    //Serial.print(scanning);//------------------------------------------------------------------  
    //Serial.print("  moved = ");//------------------------------------------------------------------  
    //Serial.println(moved);//------------------------------------------------------------------  

    

}

bool moveServos()
{

  bool moved = false;
  static int lastPosX;
  static int lastPosY;
  int delta = 0;  
  if (posX != lastPosX) {
    delta += abs(posX - lastPosX);
    servoX.write(180-posX);
    lastPosX = posX;
    moved = true;
 //     Serial.println("SERVO1");//------------------------------------------------------------------
  }
  if (posY != lastPosY) {
    delta += abs(posY - lastPosY);
    servoY.write(180-posY);
    lastPosY = posY;
    moved = true;
//      Serial.println("SERVO2");//------------------------------------------------------------------
  }
//    Serial.print("moved = ");//------------------------------------------------------------------
 //   Serial.println(moved);//------------------------------------------------------------------
  delay(30);
  return moved;

}



