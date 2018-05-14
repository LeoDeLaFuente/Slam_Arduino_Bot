
#include <SimpleTimer.h>

// parti lidar
#include <Servo.h>
///branchements  :
/*servomoteur bleu horizontale : 12
 * servomoteur bleu verticale : 13 
 * + fils + des servomoteurs branchés à la tension des piles (4*1.5v) 
 * lidar :  fil blanc =>rx1 18 
 *          fil vert =>tx1 19
 *          fil violet et noir du => non branchés
 * capa aux bornes de lalime des piles (4*1.5 v)
 *          
*/
unsigned int distance;
int angle = 20;
boolean montee = true;

boolean change=false;

Servo servoX;
Servo servoY;

SimpleTimer timer;    // Timer pour échantillonnage



// parti robot 

//###########################
//##asservissement vitesse###
 unsigned int tick_codeuse_vit_A = 0;  // Compteur de tick de la codeuse
unsigned int tick_codeuse_vit_B = 0; 
 int vitMoteur_A = 0;   // Commande du moteur
 int vitMoteur_B = 0;
const int frequence_echantillonnage = 100;  // Fréquence d'exécution de l'asservissement
const int rapport_reducteur = 80;          // Rapport entre le nombre de tours de l'arbre moteur et de la roue
const int tick_par_tour_codeuse = 4;  //64 tick sur deux capteurs hall, ici on a pris un seul capteur



//consigne en tour/s
float consigne_moteur_A = 0.5; //  Consigne nombre de tours de roue par seconde
float consigne_moteur_B = 0.5;

// init calculs asservissement PID
 float erreur_precedente_A = consigne_moteur_A; // (en tour/s)
 float erreur_precedente_B = consigne_moteur_B;
float somme_erreur_A = 0;
float somme_erreur_B = 0;

//Definition des constantes du correcteur PID
float kp =120;// 150          // Coefficient proportionnel    choisis par tatonnement sur le moniteur. Ce sont les valeurs qui donnaient les meilleures performances
float ki = 40;// 25      // Coefficient intégrateur
float kd = 45;// 45           // Coefficient dérivateur

int etape = 1;

boolean fin_A=false;
boolean fin_B=false;
boolean ok=true;


 
//###########################



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

int avancer_cm=0; // variable du nombre de centimètre à avancer
int avancer_tick=0; // variable du nombre de "tick" à effectuer

int speed_B;
 int speed_A;

float entraxe_roue=19.1; //entraxe de nos roues :18.9cm
float perim=entraxe_roue*3.14159; //perimetre du cercle parcourue par les roues lors d'un tour du robot dur lui même
float diametre_roue= 6.5 ;//diametre de nos roue : 6.5cm



void setup() {  // Setup runs once per reset
    
    // setup lidar
    
    Serial1.begin(115200);
    //Serial.begin(115200);
    Serial2.begin(115200);
    
    servoX.attach(12);
    servoY.attach(13);
    
    servoX.write(30);
    servoY.write(97);
    delay(1000);


  // setup robot
  // initialize serial communication @ 9600 baud:
  
  //Define L298N Dual H-Bridge Motor Controller Pins
  
  pinMode(dir1PinA,OUTPUT);
  pinMode(dir2PinA,OUTPUT);
  pinMode(speedPinA,OUTPUT);
  pinMode(dir1PinB,OUTPUT);
  pinMode(dir2PinB,OUTPUT);
  pinMode(speedPinB,OUTPUT);
  
  attachInterrupt(digitalPinToInterrupt(2), compteur_A, CHANGE); // Interruption sur tick de la codeuse (interruption 0 = pin2 arduino mega)
  attachInterrupt(digitalPinToInterrupt(3), compteur_B, CHANGE);
  
  
  //Serial.println(perim);
  
  timer.setInterval(1000/frequence_echantillonnage,asservissement_A);
  
  
  
  







  
}

void loop() {
    timer.run();
    
    if (etape==1 and ok){
      prise();
      delay(2000);
      reinitialise();
      avancer_tick=action(1,35);
      
      
    }else if (etape==2 and ok){
      prise();
      delay(2000);
      reinitialise();
      avancer_tick=action(4,180);
      
      
      etape=0;
      
    }else if ( etape == 3 and ok){
      
    }else if (etape == 4 and ok){
      
      }

}

// fonction lidar :
void prise(){
  while (true){
    
    
    
    distance = mesure();
    delay(10); //  quoi sert ce delay ???
    String res = String(distance)+";"+String(angle)+";";
    //Serial.println(res);
    Serial2.println(res);
    
    servoX.write(angle);
    if (change){
      change = false;
      break;
    }
    delay(40);
//    if(montee){
//       if(angle<=160){
//        angle ++;
//       }else{
//          montee = false;
//       }
//    }else{
//      if(angle>=20){
//        angle --;
//       }else{
//          montee = true;      
//          break;
//       }
    if (angle<160) {
      angle ++;
    }else {
      angle = 19;
      change =true;
    }
  }
}

unsigned int mesure(){
    unsigned int t2;
    while( Serial1.available()>=9){  
      if((0x59 == Serial1.read()) && (0x59 == Serial1.read())){ //Byte1 & Byte2
          unsigned int t1 = Serial1.read(); //Byte3
          t2 = Serial1.read(); //Byte4
          
          t2 <<= 8;
          t2 += t1;
          //Serial.print(t2);
  
          Serial1.read(); //Byte5
          Serial1.read(); //Byte6
          
          for(int i=0; i<3; i++) { 
              Serial1.read(); ////Byte7,8,9
          }
      }
    }
  return t2;

}


// fonction robot

void reinitialise(){
   tick_codeuse_vit_A = 0;  // Compteur de tick de la codeuse
   tick_codeuse_vit_B = 0; 
   vitMoteur_A = 0;   // Commande du moteur
   vitMoteur_B = 0;
  consigne_moteur_A = 0; //  Consigne nombre de tours de roue par seconde
  consigne_moteur_B = 0;


 erreur_precedente_A = consigne_moteur_A; // (en tour/s)
 erreur_precedente_B = consigne_moteur_B;
  somme_erreur_A = 0;
  somme_erreur_B = 0;
  ok=false;
      fin_B=false;
      fin_A=false;
 timer.restartTimer(0);

  }

void deplacement(){
   
   
      
      
      

      
  /*    Serial.print(tick_codeuse_A);
      Serial.print(" | ");
      Serial.println(tick_codeuse_B);
   */// debogages 
      
     
    if(tick_codeuse_A<avancer_tick){
      
      
      switch (inByte_A) {
      
      //______________Motor 1______________
      
      case '1': 
      
      analogWrite(speedPinA, speed_A);//Sets speed variable via PWM 
      digitalWrite(dir1PinA, LOW);
      digitalWrite(dir2PinA, HIGH);
  
      
      
      
      break;
      
      case '2': // Motor 1 Stop (Freespin)
      analogWrite(speedPinA, 0);
      digitalWrite(dir1PinA, LOW);
      digitalWrite(dir2PinA, HIGH);
      
      break;
      
      case '3': // Motor 1 Reverse
      analogWrite(speedPinA, speed_A);
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
    
     if(tick_codeuse_B<avancer_tick){
      
      switch (inByte_B) {
      
      //______________Motor 1______________
      
      case '4': // Fait avancer les deux moteurs dans les sens de la marche
     
      analogWrite(speedPinB, speed_B);
      digitalWrite(dir1PinB, LOW);
      digitalWrite(dir2PinB, HIGH);
      
      
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

///* Interruption sur tick de la codeuse */
void compteur_A(){
    tick_codeuse_A=tick_codeuse_A+1;  // On incrémente le nombre de tick de la codeuse
    tick_codeuse_vit_A=tick_codeuse_vit_A+1;
    //Serial.println(tick_codeuse);
}
void compteur_B(){
    tick_codeuse_B=tick_codeuse_B+1;// On incrémente le nombre de tick de la codeuse
    tick_codeuse_vit_B=tick_codeuse_vit_B+1;
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

      
      consigne_moteur_B = 0.5;
      consigne_moteur_A = 0.5; 

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

      consigne_moteur_B = 0.5;
      consigne_moteur_A = 0.5;

      //avancer_tick=convert(dist);
      
      return convert(dist);
    break;
    
    // fonctionne mieux en 4(sensanti-horaire
//    case 3 :
//       // on effectue dans ce cas un tour, la variable dist est donc langle en degrés
//      //paramétrage du sens de rotation des moteurs
//      inByte_A = '3'; 
//      inByte_B = '4';
//
//      //initialisation des compteurs
//      tick_codeuse_A = 0; 
//      tick_codeuse_B = 0; 
//
//      consigne_moteur_B = 0.5;
//      consigne_moteur_A = 0.5;

      
      
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

      consigne_moteur_B = 0.5;
      consigne_moteur_A = 0.5;

      
      return convert((dist*perim)/360);
    break;
    default :
    return 0;

//    case '4'  : 
  }
    

}

/* Interruption pour calcul du P */
void asservissement_A(){
  if(avancer_tick>tick_codeuse_A ){
    if(avancer_tick-tick_codeuse_A<250){
          consigne_moteur_A=0.5;
          
        }
        
    // Calcul de l'erreur
    int frequence_codeuse_A = frequence_echantillonnage*tick_codeuse_vit_A; //100*tick_codeuse
     float vit_roue_tour_sec_A = (float)frequence_codeuse_A/(float)tick_par_tour_codeuse/(float)rapport_reducteur;    //(100*tick_codeuse)/32/19 
    float erreur_A = consigne_moteur_A - vit_roue_tour_sec_A; // pour le proportionnel
    somme_erreur_A += erreur_A; // pour l'intégrateur
     float delta_erreur_A = erreur_A-erreur_precedente_A;  // pour le dérivateur
    erreur_precedente_A = erreur_A;
    
    // Réinitialisation du nombre de tick de la codeuse
    tick_codeuse_vit_A=0;
  
    // P : calcul de la commande
    speed_A = kp*erreur_A + ki*somme_erreur_A + kd*delta_erreur_A;  //somme des tois erreurs
    
    // Normalisation et contrôle du moteur
    if (speed_A > 255) {
      speed_A = 255;  // sachant que l'on est branché sur un pont en H L293D
    } 
    else if (speed_A <0) {
      speed_A = 0;
    }
  }else {
    fin_A=true;
    }
  if(avancer_tick>tick_codeuse_B ){
    if(avancer_tick-tick_codeuse_B<250){
          consigne_moteur_B=0.5;
          
        }
        
    // Calcul de l'erreur
    int frequence_codeuse_B = frequence_echantillonnage*tick_codeuse_vit_B; //100*tick_codeuse
     float vit_roue_tour_sec_B = (float)frequence_codeuse_B/(float)tick_par_tour_codeuse/(float)rapport_reducteur;    //(100*tick_codeuse)/32/19 
    float erreur_B = consigne_moteur_B - vit_roue_tour_sec_B; // pour le proportionnel
    somme_erreur_B += erreur_B; // pour l'intégrateur
     float delta_erreur_B = erreur_B-erreur_precedente_B;  // pour le dérivateur
    erreur_precedente_B = erreur_B;
    
    // Réinitialisation du nombre de tick de la codeuse
    tick_codeuse_vit_B=0;
  
    // P : calcul de la commande
    speed_B = kp*erreur_B + ki*somme_erreur_B + kd*delta_erreur_B;  //somme des tois erreurs
    
    // Normalisation et contrôle du moteur
    if (speed_B > 255) {
      speed_B = 255;  // sachant que l'on est branché sur un pont en H L293D
    } 
    else if (speed_B <0) {
      speed_B = 0;
    }
  }else {
    fin_B=true;
  }
  if(fin_A and fin_B){
     etape=etape+1;
     ok=true;
  }
  //Serial.println(speed_B);
  deplacement();
  
  
}



