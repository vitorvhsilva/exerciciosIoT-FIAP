// Atribui nomes aos pinos de I/O

#define BT1 9
#define BT2 11
#define ledB 4
#define ledW 3
#define ledR 2

bool statusBT1, statusBT2, flag1, flagQuestao10, flagQuestao12;
int contador;

void setup() {
  Serial.begin(9600);

  pinMode(BT1, INPUT);
  pinMode(BT2, INPUT);
  pinMode(ledR, OUTPUT);
  pinMode(ledW, OUTPUT);
  pinMode(ledB, OUTPUT);
}

void loop() {
  questao11();
}

void questao01() {
  digitalWrite(ledR, 1);
  digitalWrite(ledW, 1);
  digitalWrite(ledB, 1);
  
  delay(3000);
  
  digitalWrite(ledR, 0);
  digitalWrite(ledW, 0);
  digitalWrite(ledB, 0);
  
  delay(3000);
}

void exemploFlag(){
  statusBT1 = digitalRead(BT1);
  delay(100);
  if (statusBT1 == 1 && flag1 == 0) {
  	flag1 = 1;
    delay(100);
    // detecção da borda de subida
  }
  
  if (statusBT1 == 0 && flag1 == 1) {
  	flag1 = 0;
    delay(100);
    // detecção da borda de descida
  }
}

void questao10() {
  /* 
  Faça um dos LEDs acender quando houver um pulso 
  em um dos botões e apagar quando houver um pulso 
  em outro botão
  */
  
  statusBT1 = digitalRead(BT1);
  statusBT2 = digitalRead(BT2);
  
  if (statusBT1 && !flagQuestao10) {
  	flagQuestao10 = 1;
  }
  
  if (statusBT2 && flagQuestao10) {
  	flagQuestao10 = 0;
  }
      
  if (flagQuestao10) {
    digitalWrite(ledR, 1);
  } else {
  	digitalWrite(ledR, 0);
  }
        
}

void questao11() {
  /*
  Crie um contador, usando um variável do tipo int. 
  Faça o contador ser incrementado a 
  cada 2 segundos e zerado quando chegar a 10.
  (Utilize Serial.print para ver o valor do contador)
  */
  
  for (int i = 0; i < 10; i++) {
  	contador++;
    Serial.println(contador);
    delay(2000);
  }
  
  contador = 0;
}

void questao12() {
  /*
  Crie um contador que seja incrementado a cada pulso de 
  um dos botões e zerado por um segundo botão.
  (Utilize Serial.print para ver o valor do contador)
  */
  
  statusBT1 = digitalRead(BT1);
  statusBT2 = digitalRead(BT2);
  
  if (statusBT1) {
  	flagQuestao12 = 1;
  }
  
}
