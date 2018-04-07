#include <wifi.h>

void setup() {
  Serial.begin(9600);
  WIFI.disconnect();
  delay(3000);
  Serial.println("debut");
  WIFI.begin("iot");
  while(WIFI.status() != WL_CONNECTED){
    Serial.print("...");
    delay(3000);
  }
  Serial.println("\n connecté");
  Serial.println(WIFI.localIP());
}

void loop() {

}
