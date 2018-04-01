
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
int i=20;
int val=0;    // variable to read the value from the analog pin

void setup() {
  myservo.attach(3);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
  
}


void loop() {
  
  myservo.write(i);
  Serial.print(i);
  if(i>=160){
    i=20;
   }else{
      i=i+5;}
  delay(333);
    
  
  }
