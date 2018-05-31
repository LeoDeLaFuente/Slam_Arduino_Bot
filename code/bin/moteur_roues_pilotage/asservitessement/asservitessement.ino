
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

//   Serial.print(s+" ");
//  Serial.println(vit_roue_tour_sec,8);  // affiche à gauche la vitesse et à droite l'erreur
//  Serial.print(" : ");
//  Serial.print(erreur,4);
//  Serial.print(" : ");
//  Serial.print(vitMoteur);

//   String var = "$"+String(vit_roue_tour_sec)+";";
//   Serial.print(var);
//   
//  Serial.print("$");
 Serial.println(vit_roue_tour_sec);  
//  Serial.print(";");

}


void TournerDroite( int powerRate ){
  digitalWrite( pinInput1, LOW );
  digitalWrite( pinInput2, HIGH );
  analogWrite( pinPower, powerRate );
}





