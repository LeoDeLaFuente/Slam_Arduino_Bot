import processing.serial.*; // importe la librairie série processing
Serial  myPort; // Création objet désignant le port série
int resolution = 2;
float zoom = 1;
ArrayList<float[]> data;
ArrayList<float[]> stock;

int decallageV = 0;
int decallageH = 0;

boolean pass = true;
boolean debut = false;
/* Initialisation du programme, */
void setup(){
  background(0); 
  size(1200,700); 
  String[] serialPorts = Serial.list();
  printArray(serialPorts);
  String portName = serialPorts[0]; 
  println(portName);
  myPort = new Serial(this, portName, 9600);
  myPort.bufferUntil('\n');
  frameRate(30); 
  data = new ArrayList<float[]>();
  stock = new ArrayList<float[]>();
  println("attention");
  delay(1000);  
  println("HOP Départ !"); 
  debut = true;
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

 


//---------------- Fonctions de gestion de réception au port série --------------
void serialEvent (Serial myPort){ 
  if(debut){
    String inString = myPort.readStringUntil('\n'); // chaine stockant la chaîne reçue sur le port Série
    if (inString != null){ // si la chaine recue n'est pas vide
      println(inString);
            try{
              String[] spl1 = inString.split("::");
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
    /*  float posX = 0;
      float posY = 0;
      float orientation =float(30/180)*PI;
      String [] spl = inString.split(";");
      int distance =  Integer.parseInt(spl[0]);
      float ang =  ang = float(spl[1])/180*PI;
      float pntX = posX + cos(ang+orientation)*distance;
      float pntY = posY + sin(ang+orientation)*distance;
      float [] arr = {pntX, pntY, posX, posY, orientation};
      while(!pass);
      stock.add(arr); */
    }
  }
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






//---------------- Classe des données --------------

/*
class Donnee { 
  float posX, posY, distance, orientation, ang;
  float[] landmark = new float[2];
  
//on initialise la construction de chaque objet en traitant le String reçu par le port série, via serialEvent 
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
*/