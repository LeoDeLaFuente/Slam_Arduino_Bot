
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
int dir1PinA = 3;
int dir2PinA = 4;
int speedPinA = 9; // Needs to be a PWM pin to be able to control motor speed

// Motor 2
int dir1PinB = 5;
int dir2PinB = 6;
int speedPinB = 10; // Needs to be a PWM pin to be able to control motor speed

int speed=0;
int inByte = 0;

unsigned int tick_codeuse = 0; 
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

attachInterrupt(digitalPinToInterrupt(2), compteur, CHANGE);   // Interruption sur tick de la codeuse (interruption 0 = pin2 arduino mega)

int avancer_cm=75;
inByte = '1';

avancer_tick=convert(avancer_cm);
Serial.println(avancer_tick);
  
}

void loop() {

int speed=255;
// Initialize the Serial interface:


  
  
  if(avancer_tick-tick_codeuse<35){
    speed=10;
  }
  Serial.println(tick_codeuse);
 //Serial.println(avancer_tick);
if(tick_codeuse<avancer_tick){
  //Serial.println(inByte);
switch (inByte) {

//______________Motor 1______________

case '1': // Motor 1 Forward
analogWrite(speedPinA, speed);//Sets speed variable via PWM 
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
analogWrite(speedPinA, 255);
digitalWrite(dir1PinA, HIGH);
digitalWrite(dir2PinA, LOW);
Serial.println("Motor 1 Reverse");
Serial.println("    ");
break;

//______________Motor 2______________

case '4': // Motor 2 Forward
analogWrite(speedPinB, 255);
digitalWrite(dir1PinB, LOW);
digitalWrite(dir2PinB, HIGH);
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
analogWrite(speedPinB, 255);
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
    }else {analogWrite(speedPinA, 0);analogWrite(speedPinB, 0);}
}
      

/* Interruption sur tick de la codeuse */
void compteur(){
    tick_codeuse=tick_codeuse+1;  // On incrémente le nombre de tick de la codeuse
    //Serial.println(tick_codeuse);
}

int convert(int cm){
  int roue=cm/20.5;
  int tick=roue*80*4;
  return tick;
  }
