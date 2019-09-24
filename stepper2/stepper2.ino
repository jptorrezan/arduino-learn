//#include <Stepper.h>
int passwords[] = {1, 0, 2, 0};


const int pinLedR = 9;
const int pinLedG = 10;
const int pinLedB = 11;

const int pinPOT = A1;

const int pinButton = 2;

int estadoAntigo = LOW;
//const int stepsPerRevolution = 2050;

//Flag para contagem de acertos da senha;
int flag_pass = 0;

unsigned long tempo ;

//Inicializa a biblioteca utilizando as portas de 8 a 11 para
//ligacao ao motor
//Stepper myStepper(stepsPerRevolution, in1,in2,in3,in4);

void setup()
{
  pinMode(pinPOT, INPUT); //DEFINE O PINO COMO ENTRADA

  pinMode(pinButton, INPUT_PULLUP); //PINO DO BOTAO <= ENTRADA

  pinMode(pinLedR, OUTPUT);
  pinMode(pinLedG, OUTPUT);
  pinMode(pinLedB, OUTPUT);

  //Determina a velocidade inicial do motor
  // myStepper.setSpeed(5);
  Serial.begin(9600);
}

void loop()
{
  int valorPotenciometro = analogRead(pinPOT);
  int brilhoLeds  = map(valorPotenciometro, 0, 1023, 0, 765);
  float cores ;
  //Serial.print("Valor lido :");
  Serial.print(brilhoLeds, DEC);
  //Serial.print("Valor velocidade: ");
  // Serial.println(valVel, DEC);
  if (brilhoLeds <= 255) {
    Serial.print(" Vermelho  Pass:");
    digitalWrite(pinLedR, HIGH);
    digitalWrite(pinLedB, LOW);
    digitalWrite(pinLedG, LOW);
  }
  else if (brilhoLeds <= 510) {
    Serial.print(" Verde  Pass:");
    digitalWrite(pinLedR, LOW);
    digitalWrite(pinLedB, LOW);
    digitalWrite(pinLedG, HIGH);
  }
  else if (brilhoLeds <= 765 ) {
    digitalWrite(pinLedR, LOW);
    digitalWrite(pinLedB, HIGH);
    digitalWrite(pinLedG, LOW);
    Serial.print(" Azul  Pass:");
  }
  Serial.println(flag_pass);

  //int estado = readButtonDebounce( digitalRead(pinButton), pinButton );
  int estado = digitalRead(pinButton);
  delay (50);
  if (!estado) {
    //Serial.print("Estado: ");
    // Serial.println(estado, DEC);
    Serial.print("tempo = ");
    Serial.println(tempo, DEC);
    Serial.print("millis() = ");
    Serial.println(millis(), DEC);
    if ( (millis() - tempo ) >= 5000 && flag_pass > 0) {
      Serial.println("Reset");
      flag_pass = 0;

    }
    return ;
  }
  Serial.println("Clicou Botao");

  int passTry  = map(valorPotenciometro, 0, 1023, 0, 765);
  if (passTry <= 255) {
    passTry = 0;
  }
  else if (brilhoLeds <= 510) {
    passTry = 1;
  }
  else if (brilhoLeds <= 765 ) {
    passTry = 2;
  }

  Serial.print("Senha tentada: ");
  Serial.println(passTry, DEC);
  Serial.print("Senha correta: ");
  Serial.println(passwords[flag_pass], DEC);

  if (passTry == passwords[flag_pass]) {
    flag_pass++;
    piscarAcerto();
  }
  else {
    flag_pass = 0;
    piscarErro();
  }

  tempo = millis();










  delay(1000);
}

void piscarAcerto() {
  digitalWrite(pinLedR, LOW);
  digitalWrite(pinLedB, LOW);
  digitalWrite(pinLedG, HIGH);
  delay(250);
  digitalWrite(pinLedR, LOW);
  digitalWrite(pinLedB, LOW);
  digitalWrite(pinLedG, LOW);
  delay(250);
  digitalWrite(pinLedR, LOW);
  digitalWrite(pinLedB, LOW);
  digitalWrite(pinLedG, HIGH);
  delay(250);
  digitalWrite(pinLedR, LOW);
  digitalWrite(pinLedB, LOW);
  digitalWrite(pinLedG, LOW);
}

void piscarErro() {
  digitalWrite(pinLedR, HIGH);
  digitalWrite(pinLedB, LOW);
  digitalWrite(pinLedG, LOW);
  delay(100);
  digitalWrite(pinLedR, LOW);
  digitalWrite(pinLedB, LOW);
  digitalWrite(pinLedG, LOW);
  delay(100);
  digitalWrite(pinLedR, HIGH);
  digitalWrite(pinLedB, LOW);
  digitalWrite(pinLedG, LOW);
  delay(100);
  digitalWrite(pinLedR, LOW);
  digitalWrite(pinLedB, LOW);
  digitalWrite(pinLedG, LOW);
}
boolean readButtonDebounce (boolean estado, const int pinBotao) {
  boolean estadoAgora = digitalRead(pinBotao);
  if (estado ==  estadoAgora) {
    return estadoAgora;
  }
  else {
    delay (10);
    estadoAgora =  digitalRead(pinBotao);
    return estadoAgora;
  }
}
