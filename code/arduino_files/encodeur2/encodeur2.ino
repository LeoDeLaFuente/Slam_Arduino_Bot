// Prérequis savoir utiliser un timer 
#include <TimerOne.h> // Pour le timer


// Prérequis savoir utiliser les define
// Partie à modifier pour indiquer en define quel pin est branché où A et B à brancher sur 2 et 4
#define ENCODEURA 2
#define ENCODEURB 4


// prérequis : volatile => pour toute variable qui sera utilise dans les interruptions 

volatile int count =0; // comptage de tick d'encoder  qui sera incrémenté sur interruption " On change " sur l'interruption matériel 0 qui se fait sur le pin 2
volatile double speed =0; // vitesse du moteur 
volatile byte laststate =0;  // etat précédent de l'encodeur 


// Contrôle PWM simple
#define A 5 // Contrôle vitesse moteur 1
#define B 6 //controle direction moteur 1

void stop() //Stop
{
digitalWrite(A,LOW);
digitalWrite(B,LOW);
}

void advance(char a) // En avant
{
analogWrite (A,a); // Contrôle de vitesse en PWM
digitalWrite(B,HIGH);
}

void back_off (char a) // En arrière
{
analogWrite (A,a);
digitalWrite(B,LOW);
}

void setup()
{
// on initialise les entrées et sorties
 pinMode(ENCODEURA, INPUT_PULLUP);
 pinMode(ENCODEURB, INPUT_PULLUP);
 
pinMode(A, OUTPUT);
pinMode(B, OUTPUT);
 
attachInterrupt(0,counter, CHANGE); // on crée l'interruption sur changement sur la pin 2 => interruption 0, la routine counter va se faire toute seule sans l'appeler à chaque changement d'état sur le pin 2

Timer1.initialize(100000); // On défini le timeur : 100000 microseconds ( 0.1 sec - or 10Hz )
Timer1.attachInterrupt( timerIsr ); // attach the service routine here la fonction timerIsr est une routine qui va se faire automatiquement 10* par secondes sans l'appeler

Serial.begin(9600); // Définit vitesse de transmission série
Serial.println("Execution du controle par clavier");
}

void loop()
{
if(Serial.available()){
char val = Serial.read(); //récupération des caractères sur le
if(val != -1)             //port série
{
switch(val)
{
case 'z':// En avant si touche "z"
advance (255-255); // en avant vitesse max
                  // le driver fonctionne à l'état bas en marche avant
break;
case 's':// En arrière si touche "s"
back_off (255); // en arrière vitesse max
              // le driver fonctionne à l'état haut en marche arrière
break;
case 'x': // arrêt si touche "x"
stop();
break;
}
}
else stop();
}

Serial.println("speed");             
Serial.println(speed); 
}


// Encoder counter 0

void counter()
{
  byte state=PIND;
  
  state|=B11101011;  // mask pour ne regarder que les changements sur 2 et 4 
  // Modifier le MASK  B01111011 par BXXXXXXXX mettre des 0 là où sont les pins utilisés par l'encodeur
  if( state!=laststate)
  {
    (((state&(1<<ENCODEURA))>>ENCODEURA)^((state&(1<<ENCODEURB))>>ENCODEURB))?count--:count++;
    laststate=state;
  }
}


// Timer event to calculate speed from counters

void timerIsr()
{
    speed=count; // on a le nombre de tick ( signé ) par unité de temps  = vitesse
    count=0; // On remet le compteur de tick à 0 
}



