#include <Servo.h>

unsigned int distance;
int angle = 20;
boolean montee = true;

Servo servoX;
Servo servoY;


void setup(){
  
    Serial1.begin(115200);
    Serial.begin(115200);
    
    servoX.attach(2);
    servoY.attach(3);
    
    servoX.write(30);
    servoY.write(99);
}

void loop(){

  distance = mesure();
  delay(50);
  String res = String(distance)+";"+String(angle);
  Serial.println(res);

  servoX.write(angle);
  delay(50);
  if(montee){
     if(angle<=160){
      angle ++;
     }else{
        montee = false;
     }
  }else{
    if(angle>=20){
      angle --;
     }else{
        montee = true;
     }
  }
}

unsigned int mesure(){
    unsigned int t2;
    while( Serial1.available()>=9){  
      if((0x59 == Serial1.read()) && (0x59 == Serial1.read())){ //Byte1 & Byte2
          unsigned int t1 = Serial1.read(); //Byte3
          t2 = Serial1.read(); //Byte4
          
          t2 <<= 8;
          t2 += t1;
          //Serial.print(t2);
  
          Serial1.read(); //Byte5
          Serial1.read(); //Byte6
          
          for(int i=0; i<3; i++) { 
              Serial1.read(); ////Byte7,8,9
          }
      }
    }
  return t2;

}
