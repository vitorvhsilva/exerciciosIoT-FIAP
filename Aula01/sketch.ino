/*
PINOS DIGITAIS (I/O --- INPUT / OUTPUT)

0 Volts ---> 0, Low, False
5 Volts ---> 1, High, True


SV ---> 2V (LED) + 3V (DIVISOR DE TENSÃO)

*/

// O LED (PINO 10) DEVERA PISCAR EM INTERVALO DE MEIO SEGUNDO

// Atribui o nome LED ao Pino 10
#define LED 10

void setup() {
  //configura pino 10 (LED) como uma saída (OUTPUT)
  pinMode(LED, OUTPUT);

}

void loop() {
  // liga o LED (pino recebe 5V)
  digitalWrite(LED, HIGH);

  delay(500);

  // desliga o LED (pino recebe 0V)
  digitalWrite(LED, LOW);

  delay(500);

}
