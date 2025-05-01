// Importar bibliotecas necessárias
#include <WiFi.h>

// Instalar as duas bibliotecas e todas as dependências
#include <ESPAsyncWebServer.h>

// Nome ---> "DHT sensor library"
#include <DHT.h>

// Substitua pelas credenciais da sua rede
const char* ssid = "SUA REDE WIFI";
const char* password = "SUA SENHA WIFI";

// Informações do sensor:
// Conexão do pino DATA do sensor no módulo ESP32
#define DHTPIN 27     
// Tipo de sensor
#define DHTTYPE DHT11  
// Instancia o objeto DHT
DHT dht(DHTPIN, DHTTYPE);

// Servidor na porta 80
AsyncWebServer server(80);

// O trecho abaixo será usado quando ligarmos o sensor de temperatura e umidade DHT11

// Função para ler a temperatura do sensor DHT
String readDHTTemperature() {
  // Ler temperatura em Celsius (padrão)
  
  // Usar no exemplo:
  // float t = 23.4; 

  // Usar quando o sensor estiver conectado:   
  // float t = dht.readTemperature();
      
  // Ler temperatura em Fahrenheit (isFahrenheit = true)
  // float t = dht.readTemperature(true);

  // Testa se algum valor foi retornado:
  if(isnan(t)) {    
    Serial.println("Falha ao ler do sensor DHT!");
    return "--";
  }
  else {
    Serial.println(t);
    return String(t);
  }
}

// Função para ler a umidade do sensor DHT
String readDHTHumidity() {      
  // Usar no exemplo:
  // float h = 88;
  
  // Usar quando o sensor estiver conectado:
  // float h = dht.readHumidity();
  
  // Testa se algum valor foi retornado:
  if(isnan(h)) {
    Serial.println("Falha ao ler do sensor DHT!");
    return "--";
  }
  else {
    Serial.println(h);
    return String(h);
  }
}

// Página HTML principal que será armazenada na memória flash
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  <style>
    html {
     font-family: Arial;
     display: inline-block;
     margin: 0px auto;
     text-align: center;
    }
    h2 { font-size: 3.0rem; }
    p { font-size: 3.0rem; }
    .units { font-size: 1.2rem; }
    .dht-labels{
      font-size: 1.5rem;
      vertical-align: middle;
      padding-bottom: 15px;
    }
  </style>
</head>
<body>
  <h2>Servidor ESP32 DHT</h2>
  <p>
    <i class="fas fa-thermometer-half" style="color:#059e8a;"></i> 
    <span class="dht-labels">Temperatura</span> 
    <span id="temperature">%TEMPERATURE%</span>
    <sup class="units">&deg;C</sup>
  </p>
  <p>
    <i class="fas fa-tint" style="color:#00add6;"></i> 
    <span class="dht-labels">Umidade</span>
    <span id="humidity">%HUMIDITY%</span>
    <sup class="units">&percnt;</sup>
  </p>
</body>
<script>
setInterval(function () {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("temperature").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/temperature", true);
  xhttp.send();
}, 10000);

setInterval(function () {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("humidity").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/humidity", true);
  xhttp.send();
}, 10000);
</script>
</html>)rawliteral";

// Função para substituir os espaços reservados por valores do DHT
String processor(const String& var){
  //Serial.println(var);
  if(var == "TEMPERATURE"){
    return readDHTTemperature();
  }
  else if(var == "HUMIDITY"){
    return readDHTHumidity();
  }
  return String();
}

void setup(){  
  Serial.begin(115200);

  dht.begin();
  
  // Conectar ao Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1500);
    Serial.println("Conectando ao Wi-Fi..");
  }

  // Exibir o endereço IP local do ESP32
  Serial.println(WiFi.localIP());

  // Rota para a página inicial
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  // Rota para retornar a temperatura
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTTemperature().c_str());
  });

  // Rota para retornar a umidade
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTHumidity().c_str());
  });

  // Iniciar o servidor
  server.begin();
}

void loop(){
  
}
