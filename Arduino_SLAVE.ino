#include <Wire.h>

union Buffer  // definire numar alcatuit din 4 bytes
{
   long longNumber;
   byte longBytes[4];
};
Buffer buffer;  //declarare numar 4 bytes

// Denumire pini
#define PWM1     5
#define PWM2     6
#define PWM21  10
#define PWM22  11
#define encA   2
#define encB   7
#define enc2A  3
#define enc2B  8

volatile long pos = 0;  // Pozitia motorului
volatile long pos2 = 0;
long prevT = 0;
float eprev = 0;
float eprev2 = 0;
float eintegral = 0;
float eintegral2 = 0;

void setup() {
  Wire.begin(); // Pornire comunicare I2C
  Serial.begin(9600); //Pornire seriala cu 9600 bps
  pinMode(PWM1,   OUTPUT);  //definire pini semnal PWM ca si OUTPUT
  pinMode(PWM2,   OUTPUT);
  pinMode(PWM21,   OUTPUT);
  pinMode(PWM22,   OUTPUT);
  pinMode(encA, INPUT_PULLUP);  //definire pini semnal encoder ca si INPUT_PULLUP
  pinMode(encB, INPUT_PULLUP);
  pinMode(enc2A, INPUT_PULLUP);
  pinMode(enc2B, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encA), encoderPulse, RISING); // Se aplica intrerupere pe un pin de la encoder, declarare rutina si tipul de intrerupere RISING
  attachInterrupt(digitalPinToInterrupt(enc2A), encoderPulse2, RISING);
}

void loop() {
  
  int targetPos = 1500;   //Setare pozitie dorita MOTOR 1
  int targetPos2 = -678;     //Setare pozitie dorita MOTOR 2
  float kp = 2.5;     // Declarare cei 3 parametrii pentru PID
  float kd = 0;
  float ki = 0;
  long currT = micros();  // Calcul functie PID
  float deltaT = ((float)(currT-prevT))/1.0e6;
  prevT = currT;
  
  int e = pos - targetPos;  // eroare
  float dedt = (e-eprev)/(deltaT);
  eintegral = eintegral + e*deltaT;
  float u = kp*e + kd*dedt + ki*eintegral;  //functie PID
  float pwm = fabs(u); // Se atribuie valoare absoluta a functiei u pentru semnalul PWM
  if (pwm>255) pwm = 255; // Semnalul analog PWM este pana la 255
  boolean dir = 0;
  if (u<0) dir = 1; // Sensul de rotatie al motorului
  eprev = e;
  
  int e2 = targetPos2 - pos2; // eroare
  float dedt2 = (e2-eprev2)/(deltaT);
  eintegral2 = eintegral2 + e2*deltaT;
  float u2 = kp*e2 + kd*dedt2 + ki*eintegral2;  //functie PID
  float pwm2 = fabs(u2); // Se atribuie valoare absoluta a functiei u pentru semnalul PWM
  if (pwm2>255) pwm2 = 255; // Semnalul analog PWM este pana la 255
  boolean dir2 = 0;
  if (u2<0) dir2 = 1; // Sensul de rotatie al motorului
  eprev2 = e2;
  
  setMotor(pwm,dir); // Setarea motorului cu functia PID
  setMotor2(pwm2,dir2); // Setarea motorului cu functia PID
  
  Serial.print("target : ");
  Serial.print(targetPos);  // Afisarea pozitiei dorite
  Serial.print(", pos : ");
  Serial.print(pos);  // Afisarea pozitiei actuale
  Serial.println("<-MOTOR 1");
  Serial.print("target2: ");
  Serial.print(targetPos2); // Afisarea pozitiei dorite
  Serial.print(", pos2: ");
  Serial.print(pos2); // Afisarea pozitiei actuale
  Serial.println ("<-MOTOR 2"); 
 // Serial.println(analogRead(0));
  buffer.longNumber = pos;  // Memorarea valorii pozitiei sub forma de bytes
  Wire.beginTransmission(1);  // Pornire comunicare I2C cu dispozitivul Master cu ID #1
  Wire.write(buffer.longBytes, 4); // Trimitere valoare pozitie prin I2C sub forma a 4 bytes
  Wire.endTransmission(); //Oprire comunicare I2C
}

void encoderPulse() { // Definire rutina la intrerupere
  if (digitalRead(encB) > 0)  // Verificare daca al doilea senzor de la encoder este LOW sau HIGH
    pos++;  // Modificare pozitie
  else
    pos--;
}
void encoderPulse2() {  // Definire rutina la intrerupere
  if (digitalRead(enc2B) > 0) // Verificare daca al doilea senzor de la encoder este LOW sau HIGH
    pos2++; // Modificare pozitie
  else
    pos2--;
}

void setMotor (int speed,boolean oppDir) {  // Definirea unei functii pentru setarea vitezei si directiei motorului
  if (oppDir == 0){ // In functie de directie se trimite semnal PWM doar pe unul dintre cei doi pin
  analogWrite(PWM1, speed);
  digitalWrite(PWM2, 0);
  }
  else {
  analogWrite(PWM2, speed);
  digitalWrite(PWM1, 0);
  }
}
void setMotor2 (int speed,boolean oppDir) { // Definirea unei functii pentru setarea vitezei si directiei motorului
  if (oppDir == 0){ // In functie de directie se trimite semnal PWM doar pe unul dintre cei doi pin
  analogWrite(PWM21, speed);
  digitalWrite(PWM22, 0);
  }
  else {
  analogWrite(PWM22, speed);
  digitalWrite(PWM21, 0);
  }
}
