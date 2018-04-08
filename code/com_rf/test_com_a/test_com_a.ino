#include <SPI.h>
#include <WiFi.h>
#include <TinkerKit.h>
 
char ssid[] = "CYTA BACD";      //  your network SSID (name) 
char pass[] = "arxid...........";   // your network password
int keyIndex = 0;                 // your network key Index number (needed only for WEP)
 TKRelay relay(O5);
 TKLightSensor sensor(I0);
int status = WL_IDLE_STATUS;
WiFiServer server(80);
 
void setup() {
  Serial.begin(9600);      // initialize serial communication
 
  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present"); 
    while(true);        // don't continue
  } 
 
  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) { 
    //Serial.print("Attempting to connect to Network named: ");
    //Serial.println(ssid);                   // print the network name (SSID);
 
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:    
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(10000);
  } 
  server.begin();                           // start the web server on port 80
  printWifiStatus();                        // you're connected now, so print out the status
}
 
 
void loop() {
  WiFiClient client = server.available();   // listen for incoming clients
 
  if (client) {                             // if you get a client,
 
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
 
        if (c == 'n') {                   
          relay.on();
        }
 
        if(c == 'f'){
          relay.off();
        }
      }
   }
 
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}
 
void printWifiStatus() {
 
  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  //Serial.print("IP Address: ");
  Serial.print(ip);
  Serial.print(".");
  Serial.println();
 
}
