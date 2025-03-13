// Atribui nomes aos pinos de I/O

#define BT1 9
#define BT2 11
#define ledR 2
#define ledW 3
#define ledB 4

// Declaração de varíaveis 
bool statusBT1;

void setup() {
  // Habilita porta de comunicação serial
  // Baud Rate -> 9600 bits/s
  Serial.begin(9600);
  
  // Configura pinos de I/O como INPUT ou OUTPUT:
  pinMode(BT1, INPUT);
  pinMode(BT2, INPUT);
  pinMode(ledR, OUTPUT);
  pinMode(ledW, OUTPUT);
  pinMode(ledB, OUTPUT);
}

/*
Exemplo 1
Botão:
LOW -> Desligado -> ledW piscando em intervalos de 350ms
HIGH -> Ligado -> os LEDs ledR e ledB piscam alternadamente em intervalos de 350ms
*/

void loop() {
  if (digitalRead(BT1) == HIGH){
    Serial.println("BT1 ligado");
    digitalWrite(ledR, HIGH);
    digitalWrite(ledB, LOW);
    delay(250);

    digitalWrite(ledR, LOW);
    digitalWrite(ledB, HIGH);
    delay(250);
  } else if (digitalRead(BT2) == HIGH){
    Serial.println("BT2 ligado");
    digitalWrite(ledR, HIGH);
    digitalWrite(ledB, HIGH);
    digitalWrite(ledW, HIGH);
    delay(500);
    
    digitalWrite(ledR, LOW);
    digitalWrite(ledB, LOW);
    digitalWrite(ledW, LOW);
    delay(500);
    
  } else {
    digitalWrite(ledB, LOW);
    digitalWrite(ledW, HIGH);
    delay(350);

    digitalWrite(ledW, LOW);
    delay(350);
  }

}
