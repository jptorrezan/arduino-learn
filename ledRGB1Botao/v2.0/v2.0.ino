//Funcao Fade adicionada
const int pinBotao = 2;  // pino definido para o botao

const int pinLedR  = 8;  // pino definido para o led Vermelho
const int pinLedG  = 9;  // pino definido para o led Verde
const int pinLedB  = 10; // pino definido para o led Azul


int estadoBotao = 0;
int corLed = 0;  //Flag para a cor do LED: 0=Desligado; 1=Vermelho; 2=Verde; 3 = Azul;

int brightnessR = 0;    // how bright the LED is  (ESTADO ATUAL DA SAIDA)
int brightnessG = 0;    // how bright the LED is  (ESTADO ATUAL DA SAIDA)
int brightnessB = 0;    // how bright the LED is  (ESTADO ATUAL DA SAIDA)

int velocidadeFade = 5;    // how many points to fade the LED by (VELOCIDADE DO FADE)

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

void manipulacaoCores();

void i_OnOff();

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
        fadeColors(pinLedB, pinLedR, LOW, LOW);
        
        Serial.println(" Apagado");
      break;
      case 1:
        fadeSingleColor(pinLedR, HIGH);
        Serial.println(" R");
      break;
      case 2:
        fadeSingleColor(pinLedG, HIGH);
        Serial.println(" R + G");
      break;
      case 3:
        fadeSingleColor(pinLedR, LOW);
        Serial.println(" G");
      break;
      case 4:
        fadeSingleColor(pinLedB, HIGH);
        Serial.println(" G + B");
      break;
      case 5:
        fadeSingleColor(pinLedG, LOW);
        Serial.println(" B");
      break;
      case 6:
        fadeSingleColor(pinLedR, HIGH);
        Serial.println(" B + R");
        corLed = -1;
      break;
      corLed++;
      
    }
  }
  delay(50);
 // aaa

}
void fadeSingleColor (const int pinLed, int estado){
  int brilho = 255 * (1 - estado);
  Serial.print("BRILHO INICIAL = ");
  Serial.println(brilho, DEC);
  Serial.print("[ ");
  int i = 0;
  while(brilho != 255 * estado){
    i++;
    brilho += (2 * estado - 1) * velocidadeFade ;
    Serial.print((2 * estado - 1), DEC);
    
    if(brilho > 255 )     brilho = 255;
    else if (brilho < 0)   brilho = 0;
     
     analogWrite(pinLed, brilho);
     delay(30);
     Serial.print(" ");
    }
     Serial.print("] ");
     Serial.println(i, DEC);
  }
void fadeColors(const int pinLedA, const int pinLedB, int estadoA, int estadoB){
  int brilhoA = 255 *( 1 - estadoA);
  int brilhoB = 255 *( 1 - estadoB);
  Serial.println("");
  Serial.print("BRILHO INICIAL A = ");
  Serial.println(brilhoA, DEC);
  Serial.print("BRILHO INICIAL B = ");
  Serial.println(brilhoB, DEC);
  Serial.print("[ ");
  
  while( ( brilhoA != 255 * estadoA ) && ( brilhoB != 255 * estadoB ) ){
  
    brilhoA += (2 * estadoA - 1) * velocidadeFade ;
    brilhoB += (2 * estadoB - 1) * velocidadeFade ;
    Serial.print((2 * estadoA - 1), DEC);
   
    if(brilhoA > 255 )     brilhoA = 255;
    else if (brilhoA < 0)  brilhoA = 0;
      
    if(brilhoB > 255)    brilhoB = 255 ;
    else if(brilhoB < 0) brilhoB =   0 ;
   
    analogWrite(pinLedA, brilhoA);
    analogWrite(pinLedB, brilhoB);

   Serial.print(" ");
    delay(10);
  }
  Serial.println("] ");  
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
