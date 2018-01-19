import processing.serial.*; // importe la librairie série processing
Serial  myPort; // Création objet désignant le port série
 
void setup()
{
  background(0); // fond noir
  size(200,200); //make our canvas 200 x 200 pixels big
  String portName = Serial.list()[0]; //change the 0 to a 1 or 2 etc. to match your port
  myPort = new Serial(this, portName, 9600); //myPort = new Serial(this, "/dev/ttyACM0", 9600);
  frameRate(10);
  
}
 
void  draw()
{ // fonction exécutée en boucle
   
   
} // fin de la fonction draw()
 
//------------- Fonction de gestion des évènements série ----
void serialEvent (Serial myPort)
{ // fonction appelée lors de la survenue d'un évènement série
  // ******** Gestion de la valeur reçue sur le port série : **********
  // saut de ligne en marque de fin
  String inString = myPort.readStringUntil('\n'); // chaine stockant la chaîne reçue sur le port Série
  if (inString != null)
  { // si la chaine recue n'est pas vide
    int[] point = new int [512];
    for ( int i=0; i< 512;i++){
      point[i]=int(inString);
      if(i==511){
        i=0;
      }
    }
  } // fin condition chaine recue pas vide
} // fin de la fonction de gestion des évènements Série