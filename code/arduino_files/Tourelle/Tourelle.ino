#include <SoftwareSerial.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
SoftwareSerial Laser(8,9); //RX TX (vert = 9 ; blanc = 8)

char c; 
boolean passe = true;
long chrono = 0;
int i = 20;

void setup() {
  Serial.begin(19200);
  myservo.attach(5);  // attaches the servo on pin 11 to the servo object
  Laser.begin(19200);
  delay(3000);
  Serial.println("Arduino 1 : je suis pret a recevoir/emmettre");
}

void loop(){
 /*dans ce loop, on va effectuer la demande de mesure avec le char F
 puis attendre minimum 0,310 secondes, et récuper les char avec le while*/
 if(millis()-chrono>1010){
    if(Laser.available() && !passe){
      while( c != '\n'){
        c=Laser.read();
        Serial.print(c);
      }
      c = ' ';
      passe = true;
    }

  myservo.write(i);
  Serial.print(i+";");
  if(i>=120){
    i=20;
   }else{
     i=i+5;
   }
    
    if(passe){
      Laser.print('F');
      passe = false;
    }
 chrono=millis();   
 }
}
