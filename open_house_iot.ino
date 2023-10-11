// Importamos las librerías
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
// Sustituye los datos de tu red WIFI ( el nombre y la contraseña )
#include "config.h"
#include "fix_matrices.h"

// Puesta de LED GPIO
const int ledPin = 2;
int PinLedR = 22;
int PinLedG = 21;
int PinLedB = 19;  
// Para guardar el estado del LED                
int estadoR = LOW;                          //Definimos la variable que va a recoger el estado del LED
int estadoG = LOW; 
int estadoB = LOW; 
String ledStateG;
int estado = LOW;                         //Definimos la variable que va a recoger el estado del LED
int pulsador = 23;                        // Estado del pulsador
int contador = 0;

// Creamos el servidor AsyncWebServer en el puerto 80
AsyncWebServer server(80);

// leemos la temperatura y la mostramos
String getTemperature() {
    float adc = analogRead(A0);
    Serial.println(adc);
    return String(adc);
}
// leemos la humedad y la mostramos
String getHumidity() {
    float boton = digitalRead(pulsador);
    Serial.println(boton);
    return String(boton);
}
// leemos la presion y la mostramos
String getPressure() {
    float rssi = WiFi.RSSI();
    Serial.println(rssi);
    return String(rssi);
}

String processor(const String& var)
{
    Serial.print(var + " : ");
    if (var == "ESTADO") {
        if (digitalRead(PinLedG)) {
            ledStateG = "ON";
        }
        else {
            ledStateG = "OFF";
        }
        Serial.println(ledStateG);
        return ledStateG;
    }
    else if (var == "ADC") {
        return getTemperature();
    }
    else if (var == "PULSADOR") {
        return getHumidity();
    }
    else if (var == "RSSI") {
        return getPressure();
    }
    // Agrega más condiciones para las nuevas variables aquí
    else if (var == "IP_LOCAL") {
        return WiFi.localIP().toString();
    }
    else if (var == "HOST_NAME") {
        return WiFi.getHostname();
    }
    else if (var == "STATUS") {
        return (WiFi.status() == WL_CONNECTED) ? "Conectado" : "Desconectado";
    }
    else if (var == "SSID") {
        return WiFi.SSID();
    }
    else if (var == "PSK") {
        return WiFi.psk();
    }
    else if (var == "BSSID") {
        return WiFi.BSSIDstr();
    }
    else if (var == "RSSI_VALUE") {
        return String(WiFi.RSSI());
    }

    return String(); // Si la variable no coincide, devolvemos una cadena vacía
}




void setup()
{
  // Establecemos la velocidad de conexión por el puerto serie
  Serial.begin(115200);
  // Ponemos a  ledPin  como salida
  pinMode(ledPin, OUTPUT);
  pinMode(PinLedG, OUTPUT);                //Inicializamos el GPIO2 como salida
  digitalWrite(PinLedG, LOW);              //Dejamos inicialmente el GPIO2 apagado
  pinMode(pulsador,INPUT);
  // Iniciamos  SPIFFS
  if(!SPIFFS.begin())
     { Serial.println("ha ocurrido un error al montar SPIFFS");
       return; }
  // conectamos al Wi-Fi
  WiFi.begin(ssid, password);
  // Mientras no se conecte, mantenemos un bucle con reintentos sucesivos
  while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      // Esperamos un segundo
      Serial.println("Conectando a la red WiFi..");
    }
  Serial.println();
  Serial.println(WiFi.SSID());
  Serial.print("Direccion IP:\t");
  // Imprimimos la ip que le ha dado nuestro router
  Serial.println(WiFi.localIP());
  
  // Ruta para cargar el archivo index.html
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
            request->send(SPIFFS, "/index.html", String(), false, processor);
            });
            
  // Ruta para cargar el archivo style.css
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
            request->send(SPIFFS, "/style.css", "text/css");
            });
            
// lectura de botones  
  // Ruta para poner el GPIO alto
  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request){
            digitalWrite(PinLedG, HIGH);
            request->send(SPIFFS, "/index.html", String(), false, processor);
            });
  
  // Ruta para poner el GPIO bajo
  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request){
            digitalWrite(PinLedG, LOW);
            request->send(SPIFFS, "/index.html", String(), false, processor);
            });
// Refresco de datos enla pagina mediante script  
  server.on("/adc", HTTP_GET, [](AsyncWebServerRequest *request){
            request->send_P(200, "text/plain", getTemperature().c_str());
            });
  server.on("/pulsador", HTTP_GET, [](AsyncWebServerRequest *request){
            request->send_P(200, "text/plain", getHumidity().c_str());
            });
  server.on("/RSSI", HTTP_GET, [](AsyncWebServerRequest *request){
            request->send_P(200, "text/plain", getPressure().c_str());
            });

// Ruta para cargar una imagen desde SPIFFS
server.on("/assets/bateria1.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/assets/bateria1.png", "image/png");
});

server.on("/assets/bateria2.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/assets/bateria2.png", "image/png");
});

server.on("/assets/bateria3.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/assets/bateria3.png", "image/png");
});

server.on("/assets/bateria4.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/assets/bateria4.png", "image/png");
});

server.on("/assets/logo_empresa.jpeg", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/assets/logo_empresa.jpeg", "image/jpeg");
});

server.on("/assets/logo_ucb.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/assets/logo_ucb.png", "image/png");
});

server.on("/assets/red1.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/assets/red1.png", "image/png");
});

server.on("/assets/red2.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/assets/red2.png", "image/png");
});

server.on("/assets/red3.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/assets/red3.png", "image/png");
});

server.on("/assets/red4.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/assets/red4.png", "image/png");
});

server.on("/assets/1.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/assets/1.png", "image/png");
});


server.on("/assets/2.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/assets/2.png", "image/png");
});


server.on("/assets/3.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/assets/3.png", "image/png");
});

server.on("/assets/mypic.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/assets/mypic.png", "image/png");
});




// Inicio del servidor
  server.begin();
}

void loop(){

}
