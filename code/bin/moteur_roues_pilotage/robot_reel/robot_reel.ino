
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

//Déclaration des variables permettant la commandes des moteurs A et B
int inByte_A = 0; 
int inByte_B = 0;

// variables de comptage des roues codeuses
unsigned int tick_codeuse_A = 0; 
unsigned int tick_codeuse_B = 0; 

int avancer_cm=250; // variable du nombre de centimètre à avancer
int avancer_tick=0; // variable du nombre de "tick" à effectuer

int speed_B;
int speed_A;

float entraxe_roue=18.5; //entraxe de nos roues :18.5cm
float perim=entraxe_roue*3.14; //perimetre du cercle parcourue par les roues lors d'un tour du robot dur lui même
float diametre_roue= 6.4 ;//diametre de nos roue : 6.4cm



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


//inByte_A = '1';
//inByte_B = '4';


avancer_tick=action(1, 50);
deplacement();
delay(1000);
avancer_tick=action(3,180);
deplacement();
delay(1000);
avancer_tick=action(1, 30);
deplacement();
delay(1000);
avancer_tick=action(3,360);
deplacement();
delay(1000);
avancer_tick=action(2, 50);
deplacement();




  
}

void loop() {
     
}

void deplacement(){
   while(true){
    //action();
    Serial.println(avancer_tick);
    
    
    // Initialize the Serial interface:
    
    
      
      
      if(avancer_tick-tick_codeuse_A<250){
        speed_A=20;
      }
      if(avancer_tick-tick_codeuse_B<250){
        speed_B=20;
      }
      if(tick_codeuse_A>avancer_tick and tick_codeuse_B>avancer_tick){
        
        // on s'assure que tous les moteurs soient éteints
        analogWrite(speedPinA, 0);
        digitalWrite(dir1PinA, LOW);
        digitalWrite(dir2PinA, HIGH);

        analogWrite(speedPinB, 0);
        digitalWrite(dir1PinB, LOW);
        digitalWrite(dir2PinB, HIGH);
        
        break;
      }
      
      Serial.print(tick_codeuse_A);
      Serial.print(" | ");
      Serial.println(tick_codeuse_B);
    
      
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
      digitalWrite(dir1PinA, LOW);
      digitalWrite(dir2PinA, HIGH);
     }
    Serial.println(avancer_tick);
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
      digitalWrite(dir1PinB, LOW);
      digitalWrite(dir2PinB, HIGH);
     }
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

int convert(float cm){
  float roue=cm/(diametre_roue*3.14); 
  int tick=roue*80*4;
  return tick;
  }

float action(int commande, int dist){ 
  /* variable commande : 
      1 : avancer
      2 : reculer
      3 : tour sens horaire
      4 : tour sens anti-horaire
  */
  
  // variable dist => distance en cm
  // note : si la commande est un tour , la variable dist est l'angle en degré

  //renvoi le nombre de tick permettant de faire le déplacement

  switch (commande) {
    
    case 1 :
      //paramétrage du sens de rotation des moteurs
      inByte_A = '1'; 
      inByte_B = '4';

      //initialisation des compteurs
      tick_codeuse_A = 0; 
      tick_codeuse_B = 0; 

      speed_B=255;
      speed_A=255;

      //avancer_tick=convert(dist);
     
      return convert(dist);
    break;
    
    case 2 :
      //paramétrage du sens de rotation des moteurs
      inByte_A = '3'; 
      inByte_B = '6';

      //initialisation des compteurs
      tick_codeuse_A = 0; 
      tick_codeuse_B = 0; 

      speed_B=200;
      speed_A=200;

      //avancer_tick=convert(dist);
      
      return convert(dist);
    break;
    
    
    case 3 :
       // on effectue dans ce cas un tour, la variable dist est donc langle en degrés
      //paramétrage du sens de rotation des moteurs
      inByte_A = '3'; 
      inByte_B = '4';

      //initialisation des compteurs
      tick_codeuse_A = 0; 
      tick_codeuse_B = 0; 

      speed_B=30;
      speed_A=30;
      
      
      return convert((dist*perim)/360);
    break;
    case 4 :
      // on effectue dans ce cas un tour, la variable dist est donc langle en degrés
      //paramétrage du sens de rotation des moteurs
      inByte_A = '1'; 
      inByte_B = '6';

      //initialisation des compteurs
      tick_codeuse_A = 0; 
      tick_codeuse_B = 0; 

      speed_B=30;
      speed_A=30;

      
      return convert((dist*perim)/360);
    break;
    default :
    return 0;

//    case '4'  : 
  }
    

}




