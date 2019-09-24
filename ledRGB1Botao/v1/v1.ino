
const int pinBotao = 2;  // pino definido para o botao

const int pinLedR  = 8;  // pino definido para o led Vermelho
const int pinLedG  = 9;  // pino definido para o led Verde
const int pinLedB  = 10; // pino definido para o led Azul


int estadoBotao = 0;
int corLed = 0;  //Flag para a cor do LED: 0=Desligado; 1=Vermelho; 2=Verde; 3 = Azul;

void setup() {
  // put your setup code here, to run once:
  //Configuração dos pinos dos Leds como saídas
  pinMode(pinLedR, OUTPUT);
  pinMode(pinLedG, OUTPUT);
  pinMode(pinLedB, OUTPUT);
  
  //Config do pino do botao como entrada
  pinMode(pinBotao, INPUT_PULLUP);

  Serial.begin(9600);
}



void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("Start");
  estadoBotao = readButtonDebounce(estadoBotao, pinBotao);
  //Poderia ser em uma função, porém maior eficiencia se for em código
  if(estadoBotao == HIGH ){
    delay(100);
    Serial.print("Botao pressionado ");
    
    corLed++;
    Serial.print(corLed, DEC );
    switch(corLed){
      case 0:
        digitalWrite(pinLedR, LOW);
        digitalWrite(pinLedG, LOW);
        digitalWrite(pinLedB, LOW);
        Serial.println(" Apagado");
      break;
      case 1:
        digitalWrite(pinLedB, LOW ); 
        digitalWrite(pinLedR, HIGH);
        Serial.println(" Vermelho");
      break;
      case 2:
        digitalWrite(pinLedG, HIGH);
        Serial.println(" Laranja");
      break;
      case 3:
        digitalWrite(pinLedR, LOW);
        Serial.println(" Verde");
      break;
      case 4:
        digitalWrite(pinLedB, HIGH);
        Serial.println(" Ciano");
      break;
      case 5:
        digitalWrite(pinLedG, LOW);
        Serial.println(" Azul");
      break;
      case 6:
        digitalWrite(pinLedR, HIGH);
        corLed = -1;
      break;
      corLed++;
      
    }
  }
  
delay(50); 
}

boolean readButtonDebounce (boolean estado, const int pinBotao){
   boolean estadoAgora = digitalRead(pinBotao);
   if(estado ==  estadoAgora){
        return estadoAgora;    
    }
    else{
      delay (10);
      estadoAgora =  digitalRead(pinBotao);
      return estadoAgora;
      }
  }
