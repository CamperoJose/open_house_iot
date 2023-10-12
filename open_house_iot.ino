// Importamos las librerías
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
// Sustituye los datos de tu red WIFI ( el nombre y la contraseña )
#include "config.h"
#include "fix_matrices.h"
#include "face_generator.h"

#include <Adafruit_NeoPixel.h>

#define PIN_NEO_PIXEL 23
#define NUM_PIXELS 40

//Declarar el objeto NeoPixel
Adafruit_NeoPixel NeoPixel(NUM_PIXELS, PIN_NEO_PIXEL, NEO_GRB + NEO_KHZ800);

// Creamos el servidor AsyncWebServer en el puerto 80
AsyncWebServer server(80);

// leemos la temperatura y la mostramos
String getTemperature() {
    float adc = analogRead(A0);
    Serial.println(adc);
    return String(adc);
}

// leemos la presion y la mostramos
String getPressure() {
    float rssi = WiFi.RSSI();
    Serial.println(rssi);
    return String(rssi);
}

String processor(const String& var)
{
    
    if (var == "ADC") {
        return getTemperature();
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


void showSmileyFace(){
  Serial.println("Cara feliz");
  NeoPixel.clear();
  NeoPixel.show();
  
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {           // para cada led
    Serial.print(happy[pixel/8][pixel%8]);  
    Serial.print("  ");
    if (pixel%8 == 7) Serial.println(".");
    NeoPixel.setPixelColor(pixel, NeoPixel.Color(happy[pixel/8][pixel%8], happy[pixel/8][pixel%8], 0)); // actualizando el estado de los leds
    NeoPixel.show(); 
    delay(10);
  }
  //NeoPixel.show();
  Serial.println("Fin Cara feliz");  
}

void showSadFace(){
  Serial.println("Cara Sad");
  NeoPixel.clear();
  NeoPixel.show();
  
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {           // para cada led
    Serial.print(sad[pixel/8][pixel%8]);  
    Serial.print("  ");
    if (pixel%8 == 7) Serial.println(".");
    NeoPixel.setPixelColor(pixel, NeoPixel.Color(0, 0, sad[pixel/8][pixel%8])); // actualizando el estado de los leds
    NeoPixel.show(); 
    delay(10);
  }
  //NeoPixel.show();
  Serial.println("Fin Cara Sad");  
}

void showNeutralFace(){
  /*NeoPixel.clear();
  NeoPixel.show();
  reverseOddRows(SmileyFace, 8);
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {           // para cada led
    NeoPixel.setPixelColor(pixel, NeoPixel.Color(SmileyFace[pixel%8][pixel/8], SmileyFace[pixel%8][pixel/8], 0));  // 
    NeoPixel.show();                                           // actualizando el estado de los leds
  }*/
}

void setup()
{
  // Establecemos la velocidad de conexión por el puerto serie
  Serial.begin(115200);
  NeoPixel.begin();//
  
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


server.on("/smileyFace", HTTP_GET, [](AsyncWebServerRequest *request){
            //obtener imagen seleccionada
            showSmileyFace();
            request->send(SPIFFS, "/index.html", String(), false, processor);
            });

server.on("/sadFace", HTTP_GET, [](AsyncWebServerRequest *request){
            //obtener imagen seleccionada
            showSadFace();
            request->send(SPIFFS, "/index.html", String(), false, processor);
            });
/*
server.on("/smileyFace", HTTP_GET, [](AsyncWebServerRequest *request){
            //obtener imagen seleccionada
            showNeutralFace();
            });
*/



// Inicio del servidor
  server.begin();
}

void loop(){

}
