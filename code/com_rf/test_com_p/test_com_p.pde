
import processing.net.*;
import java.net.Inet4Address ;
int port = 8080; //Sever TCP-Port number
boolean commencement = true;

Server server;
String strdata = "0";

void setup(){
  size(400,400,P3D);
  server = new Server(this, port);
  noStroke(); 
  colorMode(RGB, 1);
  
  println("Adresse du server : "+Server.ip());
}

void draw(){
  Client esp32 = server.available(); // 
  /* Communication with client */
  if(esp32 != null){      // if client is  connecting
     // if(commencement){
         esp32.write("bien recu\r");
         commencement = false;
     // }
      if((strdata=esp32.readString()) != null){ 
          strdata=trim(strdata);
          println(strdata);
      }
  }
  delay(10);
}

/* When a client is connected */
void serverEvent(Server s, Client c){
  println("Client connect - IP:"+c.ip());
  
  
  // show IP 
}