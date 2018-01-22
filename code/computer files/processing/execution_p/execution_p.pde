import processing.serial.*; // importe la librairie série processing
Serial  myPort; // Création objet désignant le port série
float[] mesures;
float[] position = {0.0 , 0.0};
int resolution = 5;



void setup(){
  mesures = new float[2];
  background(0); 
  size(1200,700); 
  String portName = Serial.list()[3]; 
  println(portName);
  myPort = new Serial(this, portName, 19200); //myPort = new Serial(this, "/dev/ttyACM0", 9600);
  frameRate(10);  
}
 
void  draw(){
  println(mesures[0]);
  println(mesures[1]);
  pointage();
} 


void pointage(){
  if(mesures[0] != 0 || mesures[1] != 0){
    float x;
    float y;   
    x = width/2 + position[0] + cos(mesures[0]);
    y = height/2 + position[1] + sin(mesures[0]);
    fill(255);
    rect(x,y,resolution, resolution);
    mesures[0] = 0;  
    mesures[1] = 0;
  }
}
 
//------------- Fonction de gestion des évènements série ----
void serialEvent (Serial myPort){ 
  String inString = myPort.readStringUntil('\n'); // chaine stockant la chaîne reçue sur le port Série
  if (inString != null){ // si la chaine recue n'est pas vide
    traitement(inString);
  }
} 

void traitement(String inString){
  String[] split = split(inString,";");
  mesures[0] = float(split[0])/180*PI;
  mesures[1] = float(split[1].substring(3,8).replace(',','.'))*10;
}