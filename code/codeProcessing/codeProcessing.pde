
import processing.net.*;
import java.net.Inet4Address ;
import java.io.*;
int port = 8080; //Sever TCP-Port number

Server server;
String strdata = "0";


int resolution = 2;
float zoom = 1;
ArrayList<float[]> data;
ArrayList<float[]> stock;

int decallageV = 0;
int decallageH = 0;

boolean dispo = false;
String ordre = "début";
String suivant = ";1;30";
boolean nonEnv = true;
float[] landmark;



boolean pass = true;
boolean debut = true;

/* Initialisation du programme, */
void setup(){
  background(0);
  size(1200,700);

  frameRate(30);
  data = new ArrayList<float[]>();
  stock = new ArrayList<float[]>();
  println("fin intialisation");
  delay(1000);
  println("Début de la communication");

// début du serveur
  server = new Server(this, port);
  //println(this);
  noStroke();
  colorMode(RGB, 1);

  println(Server.ip());
  //String[] ip = loadStrings("http://" + "icanhazip.com/");
  //println(ip[0]);


}

/* When a esp32 is connected */
void serverEvent(Server s, Client c){
  println("Client connect - IP:"+c.ip()); // show IP
}


void  draw(){
  Client esp32 = server.available(); //
  
  
//====  Communication with esp32 ====//

  if(esp32 != null){      // if esp32 is  connecting
      esp32.write("\n");
      if((strdata=esp32.readString()) != null){
          strdata=trim(strdata);
          println(strdata);
          reception(strdata); //traitement du string d'arrivé
      }
      print("fin de la réception des données, réponse : ");
      
      String rep = reponse();
      if( !(rep.equals(""))){
         delay(50);
         esp32.write(rep);
      }
      esp32.write("!1;102;");
      println(rep);
  }
  
//==== fin de la communication avec esp32 ====//
  

//// tracé de la map ////
  if (mousePressed == true && nonEnv){
    float x = int(mouseX/resolution)/zoom-decallageH;
    float y = int(mouseY/resolution)/zoom-decallageV;
    println("x : "+x+"  y :"+y);
    //delay(5);
   mousePressed = false;
  }

  background(0);
  boussole();
  pointage();
  scale(zoom);
}




String reponse(){
  
  if(ordre.equals("debut")) return "!0;";
   
    if(dispo){
      if(!(suivant.equals(""))){
        String rtrn = suivant;
        suivant = "";
        return rtrn;
      }
      //while(ordre.equals(""));
      String rtrn = ordre;
      ordre = "";
      return rtrn;
   }
   
   return "";
}

void reception(String strdata){
  //  début de la communication 
     if(strdata.equals("début de la communication avec esp32")){ 
      println("Début de la communication avec esp32");
      return;
    }
    
    if(strdata.matches("(.*);dispo;(.*)")){
      println("esp 32 dispo");
      dispo = true;
      return;
    }
    
    
    if(!strdata.equals("") && !strdata.equals("début de la communication avec esp32") ){
      String [] spl1 = strdata.split("::");

      try{
        for(String atraiter : spl1){
          println(atraiter);
          String [] spl2 = atraiter.split(";");
          int i = 0;
          String sDistance = "";
          String sAngle = "";
          
          for( String s : spl2){
            if( s.equals("distance")){
              sDistance = spl2[i+1];
            }
            if( s.equals("angle")){
              sAngle = spl2[i+1];
            }
            ajoutData(sDistance,sAngle);
            i++;
          }
          
          if( !(sDistance.equals("")) && !(sAngle.equals(""))){
            ajoutData(sDistance,sAngle);
          }
        }
      } catch(Exception e ){ println(e);}
    }
}


void boussole(){
  stroke(#FF1500);
  line(10,10,10,30);
  line(10,10,15,15);
  line(10,10,5,15);

}

void pointage(){
  if(!(data.isEmpty())){
    for(float[] d : data){
       float positionX = (width/(2*zoom) + d[2])*zoom+decallageH;
       float positionY = (height/(2*zoom) - d[3])*zoom+decallageV;
       float landmarkX = (width/(2*zoom) + d[0])*zoom+decallageH;
       float landmarkY = (height/(2*zoom) - d[1])*zoom+decallageV;
       fill(255);
       stroke(#FFFFFF);
       rect(landmarkX,landmarkY,resolution, resolution);
       stroke(#7D7D7D);
       line(positionX,positionY,landmarkX,landmarkY);
       fleche(positionX, positionY, d[4]);
    }
  }
  pass = false;
  data.addAll(stock);
  stock = new ArrayList<float[]>();
  pass = true;
}

void fleche(float px, float py,float orientation){
  stroke(#FF1500);
  line(px,py,px+15*cos(orientation),py+15*sin(orientation));
  line(px+15*cos(orientation),py+15*sin(orientation),px+15*cos(orientation)-5,py+15*sin(orientation)-5);
  line(px+15*cos(orientation),py+15*sin(orientation),px+15*cos(orientation)-5,py+15*sin(orientation)+5);

}

void ajoutData(String sDistance, String sAngle){
  if(sDistance.equals("") || sAngle.equals("")) return;
    float posX = 0;
    float posY = 0;
    float orientation =float(1/4)*PI;
    int distance =  Integer.parseInt(sDistance);
    float ang =  ang = float(sAngle)/180*PI;
    float pntX = posX + cos(ang+orientation)*distance;
    float pntY = posY + sin(ang+orientation)*distance;
    float [] arr = {pntX, pntY, posX, posY, orientation };
    while(!pass);
    stock.add(arr);
}






//---------------- Fonctions de gestion des entrées clavier --------------

void keyTyped() {
  if (key == 'i') {
    zoom *= 1.1;
    println("zoom : "+zoom);
  }

  if (key == 'o') {
    zoom *= 0.9;
    println("zoom : "+zoom);
  }
  if (key == 'q') decallageH += 10;
  if (key == 'd') decallageH -= 10;
  if (key == 'z') decallageV += 10;
  if (key == 's') decallageV -= 10;
}