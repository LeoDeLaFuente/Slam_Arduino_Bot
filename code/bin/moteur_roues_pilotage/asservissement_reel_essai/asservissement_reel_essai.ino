
// Ce code a pour but d'asservir un moteur CC en vitesse avec un correcteur PID. On entre une consigne, le moteur essaie de la suivre.
// Ce code appele donc simplement d'autres fonctions. A savoir "TournerDroite", "asservissement" et "compteur".

#include <SimpleTimer.h>

SimpleTimer timer;                 // Timer pour échantillonnage

unsigned int tick_codeuse = 0;     // Compteur de tick de la codeuse
int vitMoteur = 0;                       // Commande du moteur
const int frequence_echantillonnage = 100;  // Fréquence d'exécution de l'asservissement
const int rapport_reducteur = 80;          // Rapport entre le nombre de tours de l'arbre moteur et de la roue
const int tick_par_tour_codeuse = 4;  //64 tick sur deux capteurs hall, ici on a pris un seul capteur

//definition des entrées
int pinInput1 = 4; // Commande de sens moteur, Input 1
int pinInput2 = 5; // Commande de sens moteur, Input 2
const int pinPower =  9; // Commande de vitesse moteur, Output Enabled1

//consigne en tour/s
float consigne_moteur= 1;  //  Consigne nombre de tours de roue par seconde

// init calculs asservissement PID
float erreur_precedente = consigne_moteur; // (en tour/s)
float somme_erreur = 0;

//Definition des constantes du correcteur PID
float kp =120;// 150          // Coefficient proportionnel    choisis par tatonnement sur le moniteur. Ce sont les valeurs qui donnaient les meilleures performances
float ki = 40;// 25      // Coefficient intégrateur
float kd = 45;// 45           // Coefficient dérivateur

int avancer_tick=0; 
 unsigned int tick_codeuse_A = 0; 
 unsigned int tick_codeuse_B = 0; 
 float consigne_moteur_A = 2;
 int dir1PinA = 4;
int dir2PinA = 5;
int speedPinA = 9; 
int speed_A;
int inByte_A = 0; 
int inByte_B = 0;
float entraxe_roue=18.5; //entraxe de nos roues :18.5cm
float perim=entraxe_roue*3.14; //perimetre du cercle parcourue par les roues lors d'un tour du robot dur lui même
float diametre_roue= 6.4 ;//diametre de nos roue : 6.4cm
 
/* Routine d'initialisation */
void setup() {
  Serial.begin(57600);         // Initialisation port COM
  pinMode(pinPower, OUTPUT);   // Sorties commande moteur
  pinMode( pinInput1, OUTPUT );
  pinMode( pinInput2, OUTPUT );

  analogWrite(pinPower, 0);  // Initialisation sortie moteur à 0 
  delay(300);                // Pause de 0,3 sec pour laisser le temps au moteur de s'arréter si celui-ci est en marche

  attachInterrupt(digitalPinToInterrupt(2), compteur, CHANGE);    // Interruption sur tick de la codeuse  (interruption 0 = pin2 arduino)
  timer.setInterval(1000/frequence_echantillonnage, asservissement);  // Interruption pour calcul du PID et asservissement; toutes les 10ms, on recommence la routine


  avancer_tick=action(1, 50);
  deplacement();
  delay(5000);

}



/* Fonction principale */
void loop(){
  timer.run();  //on fait tourner l'horloge
  delay(10);
}

/* Interruption sur tick de la codeuse */
void compteur(){
  tick_codeuse++; 
  // On incrémente le nombre de tick de la codeuse.   un seul sens
}

void deplacement(){
   while(true){
    
    
    
    
    // Initialize the Serial interface:
    
    
      
      
      if(avancer_tick-tick_codeuse_A<250){
        consigne_moteur_A=0.5;
        //speed_A=20;
      }
      if(avancer_tick-tick_codeuse_B<250){
//        speed_B=20;
      }
      if(tick_codeuse_A>avancer_tick and tick_codeuse_B>avancer_tick){
        // on s'assure que tous les moteurs soient éteints
        analogWrite(speedPinA, 0);
        digitalWrite(dir1PinA, LOW);
        digitalWrite(dir2PinA, HIGH);
        
        analogWrite(speedPinA, 0);
        digitalWrite(dir1PinA, LOW);
        digitalWrite(dir2PinA, HIGH);
        
        
        break;
      }
      
      Serial.print(tick_codeuse_A);
      Serial.print(" | ");
      Serial.println(tick_codeuse_B);
    
      
     //Serial.println(avancer_tick);
    if(tick_codeuse_A<avancer_tick){
      Serial.println(speed_A);
      switch (inByte_A) {
      
      //______________Motor 1______________
      
      case '1': // Fait avancer les deux moteurs dans les sens de la marche
      analogWrite(speedPinA, speed_A);//Sets speed variable via PWM 
      
    
      
      digitalWrite(dir1PinA, LOW);
      digitalWrite(dir2PinA, HIGH);
      
      Serial.println(speed_A);
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
      analogWrite(speedPinA, 0);
      digitalWrite(dir1PinA, LOW);
      digitalWrite(dir2PinA, HIGH);
      Serial.println("Motor 2 Stop");
      Serial.println("    ");
      break;
      
      case '6': // Motor 2 Reverse
//      analogWrite(speedPinB, speed_B);
      digitalWrite(dir1PinA, HIGH);
      digitalWrite(dir2PinA, LOW);
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
    
     if(tick_codeuse_B<avancer_tick){
      
      switch (inByte_B) {
      
      //______________Motor 1______________
      
      case '4': // Fait avancer les deux moteurs dans les sens de la marche
     
//      analogWrite(speedPinB, speed_B);
      
    
      digitalWrite(dir1PinA, LOW);
      digitalWrite(dir2PinA, HIGH);
      
      //Serial.println("Motor 1 Forward"); // Prints out “Motor 1 Forward” on the serial monitor
      //Serial.println("    "); // Creates a blank line printed on the serial monitor
      break;
      
      case '6': // Motor 2 Reverse
//      analogWrite(speedPinB, speed_B);
      digitalWrite(dir1PinA, HIGH);
      digitalWrite(dir2PinA, LOW);
     
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
  }
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

      //speed_A=255;
      //speed_B=255;
      consigne_moteur_A = 2; 

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

      //speed_B=200;
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

//      speed_B=30;
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

//      speed_B=30;
      speed_A=30;

      
      return convert((dist*perim)/360);
    break;
    default :
    return 0;

//    case '4'  : 
  }
}

/* Interruption pour calcul du P */
void asservissement()
{
  // Calcul de l'erreur
  int frequence_codeuse = frequence_echantillonnage*tick_codeuse; //100*tick_codeuse
  float vit_roue_tour_sec = (float)frequence_codeuse/(float)tick_par_tour_codeuse/(float)rapport_reducteur;    //(100*tick_codeuse)/32/19 
  float erreur = consigne_moteur - vit_roue_tour_sec; // pour le proportionnel
  somme_erreur += erreur; // pour l'intégrateur
  float delta_erreur = erreur-erreur_precedente;  // pour le dérivateur
  erreur_precedente = erreur;
  
  // Réinitialisation du nombre de tick de la codeuse
  tick_codeuse=0;

  // P : calcul de la commande
  vitMoteur = kp*erreur + ki*somme_erreur + kd*delta_erreur;  //somme des tois erreurs
  String s = String(vitMoteur);
 // Serial.print(vitMoteur + "  ");
  // Normalisation et contrôle du moteur
  if (vitMoteur > 255) {
    vitMoteur = 255;  // sachant que l'on est branché sur un pont en H L293D
  } 
  else if (vitMoteur <0) {
    vitMoteur = 0;
  }
  TournerDroite (vitMoteur);


  // DEBUG


 Serial.println(vit_roue_tour_sec);  


}


void TournerDroite( int powerRate ){
  digitalWrite( pinInput1, LOW );
  digitalWrite( pinInput2, HIGH );
  analogWrite( pinPower, powerRate );
}

int convert(float cm){
  float roue=cm/(diametre_roue*3.14); 
  int tick=roue*80*4;
  return tick;
  }

