import processing.serial.*; // importe la librairie série processing
import java.util.*;
Serial  myPort; // Création objet désignant le port série
int resolution = 2;
float zoom = 1;
LinkedList<Donnee> data;
int decallageV = 0;
int decallageH = 0;


/* Initialisation du programme, */
void setup(){
  for (String name : Serial.list()){
    println(name);
  };
  background(0); 
  size(1200,700); 
  String portName = Serial.list()[3]; 
  println(portName);
  myPort = new Serial(this, portName, 19200); //myPort = new Serial(this, "/dev/ttyACM0", 9600);
  frameRate(30); 
  data = new LinkedList<Donnee>();
}
 
 
void  draw(){
  background(0);
  boussole();
  pointage();
  scale(zoom);
} 


void boussole(){
  stroke(#FF1500);
  line(10,10,10,30);
  line(10,10,15,15);
  line(10,10,5,15);

}

void pointage(){
   for(Donnee d : data){
     println("marche");
     float positionX = (width/(2*zoom) + d.getPosX())*zoom+decallageH;
     float positionY = (height/(2*zoom) - d.getPosY())*zoom+decallageV;
     float landmarkX = (width/(2*zoom) + d.getLandX())*zoom+decallageH;
     float landmarkY = (height/(2*zoom) - d.getLandY())*zoom+decallageV;
     fill(255);
     stroke(#FFFFFF);
     rect(landmarkX,landmarkY,resolution, resolution);
     stroke(#7D7D7D);
     line(positionX,positionY,landmarkX,landmarkY);
     fleche(positionX, positionY, d.getOrientation());
  }
}

void fleche(float px, float py,float orientation){
  stroke(#FF1500);
  line(px,py,px+15*cos(orientation),py+15*sin(orientation));
  line(px+15*cos(orientation),py+15*sin(orientation),px+15*cos(orientation)-5,py+15*sin(orientation)-5);
  line(px+15*cos(orientation),py+15*sin(orientation),px+15*cos(orientation)-5,py+15*sin(orientation)+5);

}

 


//---------------- Fonctions de gestion de réception au port série --------------
void serialEvent (Serial myPort){ 
  String inString = myPort.readStringUntil('\n'); // chaine stockant la chaîne reçue sur le port Série
  if (inString != null){ // si la chaine recue n'est pas vide
    //ajouter un élément au tableau de données.
      println(inString);
      data.push(new Donnee(inString));
    
  }
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






//---------------- Classe des données --------------
class Donnee { 
  float posX, posY, distance, orientation, ang;
  float[] landmark = new float[2];
  
/*on initialise la construction de chaque objet en traitant le String reçu par le port série, via serialEvent */
  Donnee (String ligne) {
    
    String[] splity = split(ligne,';');
    ang = float(splity[0])/180*PI;
    distance = float(split(split(splity[1],'m')[0],' ')[1]); //il manque un replace "," => "."
    
    //il manque aussi la position et l'orientation
    posX = 0;
    posY = 0;
    orientation = float(30/180)*PI;
    landmark[0] = posX + cos(ang+orientation)*distance;
    landmark[1] = posY + sin(ang+orientation)*distance;
  } 
  
  float getPosX(){
    return posX;
  }
  
  float getPosY(){
    return posY;
  }
  
  float getDistance(){
    return distance;
  }
  
  float getOrientation(){
    return orientation;
  }
  
  float getAng(){
    return ang;
  }
  
  float getLandX(){
    return landmark[0];
  }
  
  float getLandY(){
    return landmark[1];
  }
} 