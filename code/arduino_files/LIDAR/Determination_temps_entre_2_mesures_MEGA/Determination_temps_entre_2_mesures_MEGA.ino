/* This program is a parsing routine of TF02 product standard output protocol on Arduino.

The format of data package is 0x59 0x59 Dist_L Dist_H Strength_L Strength_H Sequence_L Sequence_H CheckSum_L

Refer to the product specification for detailed description.

For Arduino board with one serial port, use software to virtualize serial port’s functions: such as UNO board.

*/



/*For Arduino board with multiple serial ports such as DUE board, comment out the above two codes, and directly use Serial1 port*/

int dist;// LiDAR actually measured distance value
int strength;// LiDAR signal strength
int check;// check numerical value storage
int i;
unsigned long temps=0;
int uart[9];// store data measured by LiDAR
const int HEADER=0x59;// 0x signifie qu'on cherche le mote Haxadécomal 59

void setup(){
    Serial1.begin(115200);
    Serial.begin(115200);
}

void loop(){

  if (Serial1.available())//check whether the serial port has data input
  {
    if(Serial1.read()==HEADER)// determine data package frame header 0x59
    {
      uart[0]=HEADER;
      delay(1);
      if(Serial1.read()==HEADER)//determine data package frame header 0x59
      {
        uart[1]=HEADER;
        for(i=2;i<9;i++)// store data to array
        {
          uart[i]=Serial1.read();
         }
      check=uart[0]+uart[1]+uart[2]+uart[3]+uart[4]+uart[5]+uart[6]+uart[7];
      if(uart[8]==(check&0xff))// check the received data as per protocols
      {
        dist=uart[2]+uart[3]*256;// calculate distance value
        strength=uart[4]+uart[5]*256;// calculate signal strength value
        Serial.print(millis()-temps);      
        Serial.print("  dist = ");
        Serial.print(dist);// output LiDAR tests distance value
        Serial.print('\t');
        Serial.print("strength = ");
        Serial.print(strength);// output signal strength value
        Serial.print('\n');
        temps=millis();
       }
     }
   }
 }
 }
