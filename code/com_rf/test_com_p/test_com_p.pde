
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
  Client esp32 = server.available(); //
  /* Communication with esp32 */
  if(esp32 != null){      // if esp32 is  connecting
      esp32.write("\n");
      if((strdata=esp32.readString()) != null){
          strdata=trim(strdata);
          println(strdata);
          //println("#######");
          esp32.write("ordres à faire \r");

      }
      esp32.write("miaou ! Fin des ordres ");
  }
  //delay(10);
}

/* When a esp32 is connected */
void serverEvent(Server s, Client c){
  println("Client connect - IP:"+c.ip()); // show IP
}
