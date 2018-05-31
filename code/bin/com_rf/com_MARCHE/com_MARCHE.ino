#include <SPI.h>
#include <LoRa.h>
#include <WiFi.h>
#include <Wire.h>
#include "SSD1306.h"


const char* ssid     = "le_nom_de_votre_réseau";
const char* password = "pswd";

const char* ssidProcessing = "192.168.0.23"; // l'adresse ip de processing dans le réseau.

//écran oled
SSD1306 display(0x3c, 4, 15);



void setup(){
/*==== initialisation de l'écran oled ====*/
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
    while (WiFi.status() != WL_CONNECTED) {
        delay(250);
        Serial.print(".");
        display.drawString(10,0,"...");
        display.display();
        delay(250);
        display.clear();
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
}

int value = 0;

void loop()
{
    delay(3000);
    ++value;

    display.clear();
    display.drawString(0,0,"connecting to "+String(ssidProcessing));
    display.display();
    Serial.print("connecting to ");
    Serial.println(ssidProcessing);

    // Use WiFiClient class to create TCP connections
    WiFiClient servProcessing;
    const int port = 8080;

    //si la connexion echoue
    if (!servProcessing.connect(ssidProcessing, port)) {
        Serial.println("connection failed");
        display.clear();
        display.drawString(0,0,"connection failed");
        display.display();
        return;
    }


    //ici on envoie des données à processing
    servProcessing.print("miaou");
    unsigned long timeout = millis();
    while (servProcessing.available() == 0) {
        if (millis() - timeout > 5000) {
            Serial.println(">>> servProcessing Timeout !");
            servProcessing.stop();
            return;
        }
    }

    // Read all the lines of the reply from server and print them to Serial
    while(servProcessing.available()) {
        String line = servProcessing.readStringUntil('\r');
        Serial.print(line);
    }

    Serial.println();
    Serial.println("closing connection");
}
