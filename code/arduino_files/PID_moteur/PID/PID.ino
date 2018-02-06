// Manipulation des ports
// PIND :  RX TX 2 3 4 5 6 7
// https://www.arduino.cc/en/Reference/PortManipulation



#include <PID_v1.h>  // Pour le PID
#include <TimerOne.h> // Pour le timer


#define ENCODEURA 2
#define ENCODEURB 4
#define A 5       // Contrôle vitesse moteur 1
#define B 6       //controle direction moteur 1


double Setpoint, Input, Output;


double Kp=0.8, Ki=10, Kd=0.1;


PID PID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

// volatile => pour toute variable qui sera utilise dans les interruptions 

volatile int count =0;  // comptage de tick d'encoder qui sera incrémenté
                        //sur interruption " On change " sur l'interruption 1
volatile double speed =0; // vitesse du moteur 

volatile unsigned long time0=0;  // stock un temps à un instant donné
volatile unsigned long timer=0; // variable qui va contenir le derniers temps enregistré via millis
volatile byte laststate =0;  // etat précédent de l'encodeur 

 
volatile int commande=0; // consigne pour le moteur 

int valeur;  //lecture de la consigne via le moniteur serie


void setup()
{
  
  //initialisation moniteur serie
  Serial.begin(9600);       // facultatif uniquement pour feedback

// on initialise les entrées et sorties
 pinMode(ENCODEURA, INPUT_PULLUP);
 pinMode(ENCODEURB, INPUT_PULLUP);
 
pinMode(A, OUTPUT);
pinMode(B, OUTPUT);
 // +> moteurs à l'arret 
 
  

  // Encoder quadrature counter
  attachInterrupt(0,counter, CHANGE);
  Timer1.initialize(100000); // set a timer of length 100000 microseconds
                      //(or 0.1 sec - or 10Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
  Timer1.attachInterrupt( timerIsr );

  // PID 
  Input = 0;
  Setpoint = 0;
  //active le PID
  PID.SetMode(AUTOMATIC);
  PID.SetOutputLimits(-255, 255);
}

void loop(){
   
if(Serial.available()){
  valeur=Serial.parseInt();  //récupération des caractères sur le port série
 if(valeur!=0){
 commande = valeur;
}
}

    Setpoint=commande;
    Input=speed;
    PID.Compute();
    int output=(int)Output;

   
    Serial.println("commande");
    Serial.println(commande);               // à commenter, utilisé pour débug
    Serial.print("'''''''''''''''''");      // à commenter, utilisé pour débug
    
    Serial.println("speed");
    Serial.println(speed);               // à commenter, utilisé pour débug
   Serial.print("'''''''''''''''''");      // à commenter, utilisé pour débug

    Serial.println("output");
    Serial.println(output);               // à commenter, utilisé pour débug
    Serial.print("'''''''''''''''''");      // à commenter, utilisé pour débug


//utilisation de la sortie du PID pour asservir les moteurs
if(output>=0){
  advance(255-output);
}
if(output<0){
  back_off(abs(output));
}

  timer = millis();
  if( (timer-time0)>10000)
  {
    commande= 0;
    time0=timer;
    //Timeout ! 
    
  }
}


void advance(int a) // En avant
{
analogWrite (A,a); // Contrôle de vitesse en PWM
digitalWrite(B,HIGH);
}

void back_off (int a) // En arrière
{
analogWrite (A,a);
digitalWrite(B,LOW);
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


// Timer pour calculer la vitesse grace aux encodeurs

void timerIsr()
{
    speed=count;
    count=0;
}


