#include <WiFi.h>
#include <ThingSpeak.h> 

#define SECRET_SSID "vitor"		
#define SECRET_PASS "vitor123"	

#define SECRET_CH_ID 2903184	 //	Preencha o número do seu canal do ThingSpeak	
#define SECRET_WRITE_APIKEY "EB20U8EL34Z1S82N"   // Preencha a API Key do seu canal

char ssid[] = SECRET_SSID;   
char pass[] = SECRET_PASS;   
int keyIndex = 0;            
WiFiClient  client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

int number = 0;

void setup() {
  Serial.begin(115200);  
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  
}

void loop() {

  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Tentando conectar ao SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass); 
      Serial.print(".");
      delay(1000);     
    } 
    Serial.println("\nConectado.");
  }

  int x = ThingSpeak.writeField(myChannelNumber, 1, number, myWriteAPIKey);
  if(x == 200){
    Serial.println("Canal atualizado com sucesso.");
  }
  else{
    Serial.println("Erro ao atualizar o canal. HTTP error code: " + String(x));
  }
  
  // Exemplo: gerando um número aleatório de 0 a 99
  number++;
  if(number > 99){
    number = 0;
  }
  
  delay(20000); // Aguarda 20 segundos para atualizar o canal.
}
