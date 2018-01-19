void setup()
{
  Serial.begin(9600);
  
}
 
void loop()
{ digitalWrite(13,LOW);
  static unsigned int i=0;
  if (i==1023) i=0;
          else i++;
  Serial.println(i);
  delay(100);
  digitalWrite(13,HIGH);
  delay(100);
}
