double distance;
int angle = 0;

void setup()
{
  Serial.begin(19200);
}
 
void loop()
{
 for(int i = 0; i< 120; i++){
    distance = 2;
    distance += i/7;
    angle = i-60;
    Serial.print(angle);
    Serial.print(";F: ");
    Serial.print();
    Serial.println("m 1235");
    delay(100);
 }
}
