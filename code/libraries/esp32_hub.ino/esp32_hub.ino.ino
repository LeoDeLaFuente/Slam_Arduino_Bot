#include <SPI.h>
#include <LoRa.h>
#include <WiFi.h>
#include <Wire.h>
#include "SSD1306.h"
//#include <SoftwareSerial.h>


const char* ssid1 = "blabla";
const char* ssid     = "iPhone de Félix";
const char* password = "miaoumiaou666:!";

const char* ssidProcessing = "172.20.10.2";

const int port = 8080;

int distance = 0;
int angle = 0;

HardwareSerial Serial2(2); // pin 16=RX, pin 17=TX 
   
WiFiClient servProcessing;



SSD1306 display(0x3c, 4, 15); 



void setup(){
/*==== initialisation de l'écran ====*/  
    pinMode(25,OUTPUT);
    pinMode(16,OUTPUT);
    digitalWrite(16, LOW);    // set GPIO16 low to reset OLED
    delay(50);
    digitalWrite(16, HIGH); // while OLED is running, must set GPIO16 in high
    display.init();
    display.flipScreenVertically();
    display.setFont(ArialMT_Plain_10);
    display.clear();
/*==================*/
    Serial2.begin(9600); // pin 16=RX, pin 17=TX   
    
    Serial.begin(9600);
    delay(100);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    display.drawString(0, 0,"Connecting to "+String(ssid));
    display.display();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);
    //WiFi.begin(ssid1);
    String att = ".";
    while (WiFi.status() != WL_CONNECTED) {
        delay(50);
        Serial.print(".");
        display.drawString(10,0,att);
        display.display();
        delay(250);
        display.clear();
        att += ".";
    }

    display.clear();
    display.drawString(0,0,"WiFi connected");
    display.drawString(0,10,"IP address: ");
    display.drawString(0,20,String(WiFi.localIP()));
    display.display();

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    delay(300);

    //=== début de la connexion vers le server processing ===//

    display.clear();
    display.drawString(0,0,"connecting to "+String(ssidProcessing));
    display.display();
    Serial.print("connecting to ");
    Serial.println(ssidProcessing);

    // Use WiFiClient class to create TCP connections
    connexion();
}


void loop(){
    if(Serial2.available())  lireMega();
    if(servProcessing.available())  lireServ();
    delay(3);
}

void lireMega (){
  ecrire("Réception et envoie des données de la méga");
  while(Serial2.available()) {
    servProcessing.print(Serial2.readStringUntil('\r'));
  }
  ecrire("find de transmition données méga => processing");
}

void lireServ(){
  ecrire("Réception et envoie des données de processing");
  while(servProcessing.available()) {
        Serial2.print(servProcessing.readStringUntil('\r'));
  }
  ecrire("find de transmition données processing => méga");
}

void connexion(){
      if (!servProcessing.connect(ssidProcessing, port)) {
        ecrire("connexion fail");
        connexion();
        return;
    }


    //ici on envoie des données à processing
    servProcessing.print("début de la communication avec esp32\r");
    unsigned long timeout = millis();
    while (servProcessing.available() == 0) {
        if (millis() - timeout > 5000) {
            ecrire(">>> servProcessing Timeout !");
            servProcessing.stop();
            return;
        }
    }

    // Read all the lines of the reply from server and print them to Serial
    while(servProcessing.available()) {
        String line = servProcessing.readStringUntil('\r');
        //Serial.print(line);
        ecrire(line);
    }
}

void ecrire(String s){
  Serial.println(s);
  display.clear();
  display.drawString(0,0,s);
  display.display();
}
