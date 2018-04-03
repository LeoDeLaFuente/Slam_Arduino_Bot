//Code by Reichenstein7 (thejamerson.com)

//Keyboard Controls:
//
// 1 -Motor 1 Left
// 2 -Motor 1 Stop
// 3 -Motor 1 Right
//
// 4 -Motor 2 Left
// 5 -Motor 2 Stop
// 6 -Motor 2 Right

// Declare L298N Dual H-Bridge Motor Controller directly since there is not a library to load.

// Motor 1
int dir1PinA = 4;
int dir2PinA = 5;
int speedPinA = 9; // Needs to be a PWM pin to be able to control motor speed

// Motor 2
int dir1PinB = 6;
int dir2PinB = 7;
int speedPinB = 10; // Needs to be a PWM pin to be able to control motor speed

int speed_A=0;
int speed_B=0;

int inByte_A = 0;
int inByte_B = 0;

unsigned int tick_codeuse_A = 0; 
unsigned int tick_codeuse_B = 0; 

int avancer_tick=0;

void setup() {  // Setup runs once per reset
// initialize serial communication @ 9600 baud:
Serial.begin(9600);

//Define L298N Dual H-Bridge Motor Controller Pins

pinMode(dir1PinA,OUTPUT);
pinMode(dir2PinA,OUTPUT);
pinMode(speedPinA,OUTPUT);
pinMode(dir1PinB,OUTPUT);
pinMode(dir2PinB,OUTPUT);
pinMode(speedPinB,OUTPUT);

attachInterrupt(digitalPinToInterrupt(2), compteur_A, CHANGE); // Interruption sur tick de la codeuse (interruption 0 = pin2 arduino mega)
attachInterrupt(digitalPinToInterrupt(3), compteur_B, CHANGE);
int avancer_cm=150;
inByte_A = '1';
inByte_B = '4';

avancer_tick=convert(avancer_cm);
Serial.println(avancer_tick);
int depart=0;
int a=5;
depart=millis();
}

void loop() {
//action();

Serial.println(avancer_tick);

int speed_A=255;
int speed_B=0;
// Initialize the Serial interface:


  
  unsigned long depart;
  unsigned long arrive;
  Serial.print(tick_codeuse_A);
  Serial.print(" | ");
  Serial.println(tick_codeuse_B);
  int temps=arrive-depart;
  Serial.println(temps);
  Serial.println(arrive);

  
 //Serial.println(avancer_tick);
if(tick_codeuse_A<avancer_tick){
  
  switch (inByte_A) {
  
  //______________Motor 1______________
  
  case '1': // Fait avancer les deux moteurs dans les sens de la marche
  analogWrite(speedPinA, speed_A);//Sets speed variable via PWM 

  
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, HIGH);
  
 
  
  //Serial.println("Motor 1 Forward"); // Prints out “Motor 1 Forward” on the serial monitor
  //Serial.println("    "); // Creates a blank line printed on the serial monitor
  break;
  
  case '2': // Motor 1 Stop (Freespin)
  analogWrite(speedPinA, 0);
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, HIGH);
  Serial.println("Motor 1 Stop");
  Serial.println("    ");
  break;
  
  case '3': // Motor 1 Reverse
  analogWrite(speedPinA, speed_A);
  digitalWrite(dir1PinA, HIGH);
  digitalWrite(dir2PinA, LOW);
  Serial.println("Motor 1 Reverse");
  Serial.println("    ");
  break;
  
  //______________Motor 2______________
  
  case '4': // Motor 2 Forward
  
  
  Serial.println("Motor 2 Forward");
  Serial.println("    ");
  break;
  
  case '5': // Motor 1 Stop (Freespin)
  analogWrite(speedPinB, 0);
  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, HIGH);
  Serial.println("Motor 2 Stop");
  Serial.println("    ");
  break;
  
  case '6': // Motor 2 Reverse
  analogWrite(speedPinB, speed_B);
  digitalWrite(dir1PinB, HIGH);
  digitalWrite(dir2PinB, LOW);
  Serial.println("Motor 2 Reverse");
  Serial.println("    ");
  break;
  
  default:
  // turn all the connections off if an unmapped key is pressed:
  for (int thisPin = 2; thisPin < 11; thisPin++) {
  digitalWrite(thisPin, LOW);
  }
    }
      }
else {
  analogWrite(speedPinA, 0);
  arrive=millis();
 }

 if(tick_codeuse_B<avancer_tick){
  
  switch (inByte_B) {
  
  //______________Motor 1______________
  
  case '4': // Fait avancer les deux moteurs dans les sens de la marche
 
  analogWrite(speedPinB, speed_B);
  

  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, HIGH);
  
  //Serial.println("Motor 1 Forward"); // Prints out “Motor 1 Forward” on the serial monitor
  //Serial.println("    "); // Creates a blank line printed on the serial monitor
  break;
  
  case '6': // Motor 2 Reverse
  analogWrite(speedPinB, speed_B);
  digitalWrite(dir1PinB, HIGH);
  digitalWrite(dir2PinB, LOW);
 
  break;
  
 
  default:
  // turn all the connections off if an unmapped key is pressed:
  for (int thisPin = 2; thisPin < 11; thisPin++) {
  digitalWrite(thisPin, LOW);
  }
    }
      }
else {
  
  analogWrite(speedPinB, 0);
 }
      
}
      

/* Interruption sur tick de la codeuse */
void compteur_A(){
    tick_codeuse_A=tick_codeuse_A+1;  // On incrémente le nombre de tick de la codeuse
    //Serial.println(tick_codeuse);
}
void compteur_B(){
    tick_codeuse_B=tick_codeuse_B+1;  // On incrémente le nombre de tick de la codeuse
    //Serial.println(tick_codeuse);
}

int convert(int cm){
  int roue=cm/20.5;
  int tick=roue*80*4;
  return tick;
  }

void action(int commande, int dist){ 
  /* variable commande : 
      1 : avancer
      2 : reculer
      3 : tour sens horaire
      4 : tour sens anti-horaire
  */
  
  // variable dist => distance en cm
  // note : si la commande est un tour , la variable dist est l'angle en degré

  switch (commande) {
    case '1' :
      //paramétrage du sens de rotation des moteurs
      inByte_A = '1'; 
      inByte_B = '4';

      //initialisation des compteurs
      tick_codeuse_A = 0; 
      tick_codeuse_B = 0; 

      avancer_tick=convert(dist);
    
    break;
    case '2' :
      //paramétrage du sens de rotation des moteurs
      inByte_A = '3'; 
      inByte_B = '6';

      //initialisation des compteurs
      tick_codeuse_A = 0; 
      tick_codeuse_B = 0; 

      avancer_tick=convert(dist);
    break;
//    case '3':
//    break;
//    case '4'  : 
  }
    

}



