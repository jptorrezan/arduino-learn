
int pinosLinhas[]  = {11,10,9,8};

int pinosColunas[] = {6,5,4,3};
//Teclas correspondentes aos numeros 
char teclas[4][4] = {{'0','F','E','D'},
                     {'C','B','A','9'},
                     {'8','7','6','5'},
                     {'4','3','2','1'}};


void setup()
{
  //Pinos ligados aos pinos 1, 2, 3 e 4 do teclado - Linhas
  
  //Pinos ligados aos pinos 5, 6, 7 e 8 do teclado - Colunas
  for (int nL = 0; nL <= 3; nL++) {
     pinMode(pinosLinhas[nL], OUTPUT);
     digitalWrite(pinosLinhas[nL], HIGH);
  }
  
 //Pinos ligados aos pinos 1, 2, 3 e 4 do teclado - Linhas
  for (int nC = 0; nC <= 3; nC++) {
     pinMode(pinosColunas[nC], INPUT_PULLUP);
  } 
   
  Serial.begin(9600);
  Serial.println("Aguardando acionamento das teclas...");
  Serial.println();
}
 
void loop()
{ 
    //Serial.println("\nEntrou loop");
    for (int nL = 0; nL <= 3; nL++)
    {
      digitalWrite(pinosLinhas[nL], LOW);
      
      //faz varredura em todas as colunas verificando se tem algum botao apertado
      for (int nC = 0; nC <= 3; nC++) {
        if (digitalRead(pinosColunas[nC]) == LOW)
        {
          Serial.print("Tecla: ");
          Serial.println(teclas[nL][nC]);
          while(digitalRead(pinosColunas[nC]) == LOW){}
        }
      }

      digitalWrite(pinosLinhas[nL], HIGH);
    }
   delay(10);
}
 
void imprime_linha_coluna(int x, int y)
{
       Serial.print("Linha : ");
       Serial.print(x);
       Serial.print(" x Coluna : ");
       Serial.print(y);
       delay(10);
       Serial.println();
}
