#include <Wire.h>
union Buffer  // Definire numar alcatuit din 4 bytes
{
   long longNumber;
   byte longBytes[4];
};

Buffer buffer;  // Declarare numar 4 bytes

void setup()
{
  Wire.begin(1);  // Conectare I2C cu ID #1 - Master
  Wire.onReceive(receiveEvent); // Declarare functie eveniment I2C
  Serial.begin(9600); // Pornire seriala la 9600 bps
}   

void loop()
{
  
}

void receiveEvent(int howMany)  // Definire functie eveniment I2C
{
  if (Wire.available() > 0) // In caz ca Slave trimite mai putini bytes
   {
      buffer.longBytes[0] = Wire.read();  // Citire date primit byte cu byte
      buffer.longBytes[1] = Wire.read();
      buffer.longBytes[2] = Wire.read();
      buffer.longBytes[3] = Wire.read();
      Serial.println(buffer.longNumber, DEC); // Afisare numar primit
   }
}
