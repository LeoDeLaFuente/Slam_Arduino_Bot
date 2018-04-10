unsigned char dta[100];
unsigned char len = 0;

void setup()
{
    Serial1.begin(115200);
    Serial.begin(115200);
}

void loop()
{
    while(Serial1.available()>=9)
    {
        if((0x59 == Serial1.read()) && (0x59 == Serial1.read())) //Byte1 & Byte2
        {
            unsigned int t1 = Serial1.read(); //Byte3
            unsigned int t2 = Serial1.read(); //Byte4

            t2 <<= 8;
            t2 += t1;
            Serial.print(t2);
            Serial.print('\t');

            t1 = Serial1.read(); //Byte5
            t2 = Serial1.read(); //Byte6

            t2 <<= 8;
            t2 += t1;
            Serial.println(t2);

            for(int i=0; i<3; i++) 
            { 
                Serial1.read(); ////Byte7,8,9
            }
        }
    }
    Serial.println("passé");
}
