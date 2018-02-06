const int _MOTEUR =  9;            // Digital pin pour commande moteur
unsigned int tick_codeuse = 0;     // Compteur de tick de la codeuse
 
/* Routine d'initialisation */
void setup() {
  Serial.begin(9600);
    pinMode(_MOTEUR, OUTPUT);   // Sortie moteur
    analogWrite(_MOTEUR, 255);  // Sortie moteur à 0
    delay(5000);                // Pause de 5 sec pour laisser le temps au moteur de s'arréter si celui-ci est en marche
    Serial.println("yes");
    attachInterrupt(0, compteur, CHANGE);    // Interruption sur tick de la codeuse (interruption 0 = pin2 arduino mega)
}
 
/* Fonction principale */
void loop(){
    delay(10);
    
}
 
/* Interruption sur tick de la codeuse */
void compteur(){
    tick_codeuse=tick_codeuse+1;  // On incrémente le nombre de tick de la codeuse
    Serial.println(tick_codeuse);
}
