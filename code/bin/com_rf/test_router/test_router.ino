#include <SPI.h>
#include <LoRa.h>
#include <WiFi.h>
#include <Wire.h>
#include "SSD1306.h"
 

SSD1306 display(0x3c, 4, 15);

WiFiClient servProcessing;
WiFiServer server(80);


const char *ssid = "ESP32ap";
const char *password = "12345678";

const char* ssidProcessing = "192.168.0.23";
const int port = 8080;



void setup() {
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
  
  Serial.begin(115200);
   while(!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println();
  ecrire("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  ecrire("configuré");
  IPAddress myIP = WiFi.softAPIP();
  ecrire("AP IP address: ");
  Serial.print(myIP);

  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  ecrire("WiFi connected");
  ecrire("IP address: ");
  Serial.println(WiFi.localIP());
  
  server.begin();



}

void loop() {
  /*    
    unsigned long t1 = millis();
    servProcessing.print("début de la loop");
    unsigned long timeout = millis();
    while (servProcessing.available() == 0) {
        if (millis() - timeout > 5000) {
            Serial.println(">>> servProcessing Timeout !");
            servProcessing.stop();
            connexion();
        }
    }

    // Read all the lines of the reply from server and print them to Serial
    while(servProcessing.available()) {
        String line = servProcessing.readStringUntil('\r');
        ecrire(line);
    }

    unsigned long t = millis() - t1;
    ecrire(String(t)); */
}
void connexion(){
      if (!servProcessing.connect(ssidProcessing, port)) {
        ecrire("connexion fail");
        return;
    }


    //ici on envoie des données à processing
    servProcessing.print("début de la communication avec esp32");
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
        Serial.print(line);
    }
}


void ecrire(String s){
  Serial.println(s);
  display.clear();
  display.drawString(0,0,s);
  display.display();
}
