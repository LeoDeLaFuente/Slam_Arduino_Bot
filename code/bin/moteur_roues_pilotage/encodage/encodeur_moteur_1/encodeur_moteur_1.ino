const int _MOTEUR =  9;            // Digital pin pour commande moteur
unsigned int tick_codeuse = 0;     // Compteur de tick de la codeuse

int avancer = 20;
 
/* Routine d'initialisation */
void setup() {
  Serial.begin(9600);
   // pinMode(_MOTEUR, OUTPUT);   // Sortie moteur
    //analogWrite(_MOTEUR, 255);  // Sortie moteur à 0
    delay(500);                // Pause de 5 sec pour laisser le temps au moteur de s'arréter si celui-ci est en marche
    Serial.println("yes");
    attachInterrupt(digitalPinToInterrupt(2), compteur, CHANGE);   // Interruption sur tick de la codeuse (interruption 0 = pin2 arduino mega)
    while(tick_codeuse<avancer){
       analogWrite(9, 10);//Sets speed variable via PWM 
       digitalWrite(3, LOW);
       digitalWrite(4, HIGH);
       //Serial.println("Motor 1 Forward");
    }
    analogWrite(9,0);
    
}
 
/* Fonction principale */
void loop(){
  
    //delay(10);
    
}
 
/* Interruption sur tick de la codeuse */
void compteur(){
    tick_codeuse=tick_codeuse+1;  // On incrémente le nombre de tick de la codeuse
    Serial.println(tick_codeuse);
}
