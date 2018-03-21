#include <SoftwareSerial.h>

SoftwareSerial Laser(8,9); //RX TX (vert = 9 ; blanc = 8)

char b;
char c; 

void setup() {
  Serial.begin(19200);
  Laser.begin(19200);
  Serial.println("Pret à echanger");
}

void loop(){
 /*dans ce loop, on va effectuer la demande de mesure avec le char F
 puis attendre minimum 0,310 secondes, et récuper les char avec le while*/
 if(Serial.available()){
    b=Serial.read();
    Laser.print(b);
 }
    
 if(Laser.available()){
      c=Laser.read();
      Serial.print(c);
    }
}

