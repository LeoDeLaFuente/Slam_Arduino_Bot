/*
  * Code processing d'exemple d'un server sous processing, reçevant les informations de l'esp32
  * Il faut que l'esp32 et l'ordinateur soient connecté sur le même réseau wifi.
  * Le port par defaut est 8080.
  * Une fois executé, le server envoi son adresse ip dans la sortie standard de processing.
*/
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


}

void draw(){
  Client esp32 = server.available(); //
  /* Communication with esp32 */
  if(esp32 != null){      // if esp32 is  connecting
      esp32.write("\n");
      if((strdata=esp32.readString()) != null){
          strdata=trim(strdata);
          println(strdata);
          esp32.write("ordres à faire \r");

      }
      esp32.write("Bien reçu !");
  }
}

/* Quand l'esp 32 se connecte. */
void serverEvent(Server s, Client c){
  println("Client connect - IP:"+c.ip()); // show IP
}
