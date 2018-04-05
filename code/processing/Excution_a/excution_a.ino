int k = 0;

void setup()
{
  Serial.begin(19200);
  
}
 
void loop()
{
  for(int i = k; i < k+130; i++){
    String angle = String(i);
    String mesure = String(i*0.1 + 3);
    Serial.println(angle+";F: "+mesure+"m 1235");
    delay(3);
  }
  delay(2000);
  k = 130;
}
