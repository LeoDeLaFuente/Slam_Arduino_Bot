#include <SoftwareSerial.h>
SoftwareSerial Laser(8,9); //RX TX
char b = 'F';
char c = 'F';
boolean passe = true;
boolean sort = false;
long chrono = 0;

void setup() {
  Serial.begin(19200);
  Laser.begin(19200);
  delay(3000);
  Serial.println("Arduino A : je suis pret a recsvoir/emmettre");
}

void loop(){
 //*
 if(millis()-chrono>310){
    if(Laser.available() && !passe){
      while( c != '\n'){
        c=Laser.read();
        Serial.print(c);
      }
      c = ' ';
      passe = true;
    }
    
    if(passe){
      Laser.print('F');
      passe = false;
    }
 chrono=millis();   
 }
 
 //*/
  
}

