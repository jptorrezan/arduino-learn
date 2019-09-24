#include <Stepper.h> 

const int in1 = 11;
const int in2 = 10;
const int in3 = 9;
const int in4 = 8;
const int pinPOT = A1;
const int pinLED = 05;
const int stepsPerRevolution = 2050; 
  
//Inicializa a biblioteca utilizando as portas de 8 a 11 para 
//ligacao ao motor 
Stepper myStepper(stepsPerRevolution, in1,in2,in3,in4); 

void setup() 
{ 
  pinMode(pinPOT, INPUT); //DEFINE O PINO COMO ENTRADA
  pinMode(pinLED, OUTPUT); //DEFINE O PINO COMO SAÍDA  
 //Determina a velocidade inicial do motor 
 myStepper.setSpeed(50);
 Serial.begin(9600);
} 
  
void loop() 
{ 
 int valor = analogRead(pinPOT);
 int valPot  = map(valor,0,1023,0,255);

 int valVel  = map(valor,0,1023,0,60);

 Serial.print("Valor lido :");
 Serial.println(valor,DEC);
 Serial.print("Valor velocidade: ");
 Serial.println(valVel, DEC);
 analogWrite(pinLED, valPot);
 
 
 myStepper.setSpeed(5);
 myStepper.step(1025);
 
 delay(3000); 
}
