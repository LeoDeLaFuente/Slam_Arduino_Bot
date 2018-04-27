
import processing.net.*;
import java.net.Inet4Address ;
int port = 8080; //Sever TCP-Port number

Server server;
String strdata = "0";

void setup(){
  size(400,400,P3D);
  server = new Server(this, port);
  //println(this);
  noStroke(); 
  colorMode(RGB, 1);
  
  println(Server.ip());
  //String[] ip = loadStrings("http://" + "icanhazip.com/");
  //println(ip[0]);
  
  
}

void draw(){
  Client client = server.available(); // 
  /* Communication with client */
  if(client != null){      // if client is  connecting
      client.write("\n");
      if((strdata=client.readString()) != null){ 
          strdata=trim(strdata);
          println(strdata);
      }
  }
  delay(10);
}

/* When a client is connected */
void serverEvent(Server s, Client c){
  println("Client connect - IP:"+c.ip()); // show IP 
}