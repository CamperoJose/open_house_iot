#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include "config.h"
#include "face_generator.h"

#include <Adafruit_NeoPixel.h>


#define PIN_NEO_PIXEL 23
#define NUM_PIXELS 40

//Declarar el objeto NeoPixel
Adafruit_NeoPixel NeoPixel(NUM_PIXELS, PIN_NEO_PIXEL, NEO_GRB + NEO_KHZ800);

// Creamos el servidor AsyncWebServer en el puerto 80
AsyncWebServer server(80);

// leemos la temperatura y la mostramos
float getTemperature() {
    float adc = analogRead(A0);
    Serial.println(adc);
    return adc;
}

void showSmileyFace(){
  NeoPixel.clear();
  NeoPixel.show();
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {           // para cada led
    NeoPixel.setPixelColor(pixel, NeoPixel.Color(happy[pixel/8][pixel%8], happy[pixel/8][pixel%8], 0)); // actualizando el estado de los leds
    NeoPixel.show(); 
    delay(10);
  }
}

void showSadFace(){
  NeoPixel.clear();
  NeoPixel.show();
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {           // para cada led
    NeoPixel.setPixelColor(pixel, NeoPixel.Color(0, 0, sad[pixel/8][pixel%8])); // actualizando el estado de los leds
    NeoPixel.show(); 
    delay(10);
  } 
}

void showNeutralFace(){
  NeoPixel.clear();
  NeoPixel.show();
  
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {           // para cada led
    NeoPixel.setPixelColor(pixel, NeoPixel.Color(neutral[pixel/8][pixel%8],neutral[pixel/8][pixel%8],neutral[pixel/8][pixel%8])); // actualizando el estado de los leds
    NeoPixel.show(); 
    delay(10);
  }
}

void showLaughFace(){
  NeoPixel.clear();
  NeoPixel.show();
  
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {           // para cada led
    NeoPixel.setPixelColor(pixel, NeoPixel.Color(laughR[pixel/8][pixel%8],laughGB[pixel/8][pixel%8],laughGB[pixel/8][pixel%8])); // actualizando el estado de los leds
    NeoPixel.show(); 
    delay(10);
  } 
}

void showAngryFace(){
  Serial.println("Cara Enojada");
  NeoPixel.clear();
  NeoPixel.show();
  
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {           // para cada led
    NeoPixel.setPixelColor(pixel, NeoPixel.Color(madR[pixel/8][pixel%8],madG[pixel/8][pixel%8],0)); // actualizando el estado de los leds
    NeoPixel.show(); 
    delay(10);
  }
}

void showSurprisedFace(){
  Serial.println("Cara sorprendida");
  NeoPixel.clear();
  NeoPixel.show();
  
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {           // para cada led
    NeoPixel.setPixelColor(pixel, NeoPixel.Color(surpriseR[pixel/8][pixel%8],surpriseR[pixel/8][pixel%8],surpriseR[pixel/8][pixel%8])); // actualizando el estado de los leds
    NeoPixel.show(); 
    delay(10);
  } 
}

void showHeartFace(){
  Serial.println("Cara de corazón");
  NeoPixel.clear();
  NeoPixel.show();
  
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {           // para cada led
    NeoPixel.setPixelColor(pixel, NeoPixel.Color(heartR[pixel/8][pixel%8],0,0)); // actualizando el estado de los leds
    NeoPixel.show(); 
    delay(10);
  }
}

void showCoolFace(){
  NeoPixel.clear();
  NeoPixel.show();
  
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {           // para cada led
    NeoPixel.setPixelColor(pixel, NeoPixel.Color(coolRGB[pixel/8][pixel%8],coolRGB[pixel/8][pixel%8],coolRGB[pixel/8][pixel%8])); // actualizando el estado de los leds
    NeoPixel.show(); 
    delay(10);
  }
}

void showNerdFace(){
  NeoPixel.clear();
  NeoPixel.show();
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {           // para cada led
    NeoPixel.setPixelColor(pixel, NeoPixel.Color(nerdR[pixel/8][pixel%8],nerdG[pixel/8][pixel%8],nerdB[pixel/8][pixel%8])); // actualizando el estado de los leds
    NeoPixel.show(); 
    delay(10);
  } 
}

void showUcbFace(){
  NeoPixel.clear();
  NeoPixel.show();
  
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {           // para cada led
    if((pixel/8)%2==0) {
      NeoPixel.setPixelColor(pixel, NeoPixel.Color(ucbR[pixel/8][pixel%8],ucbG[pixel/8][pixel%8],ucbB[pixel/8][pixel%8])); // actualizando el estado de los leds
    } else {
      NeoPixel.setPixelColor(pixel, NeoPixel.Color(ucbR[pixel/8][7-pixel%8],ucbG[pixel/8][7-pixel%8],ucbB[pixel/8][7-pixel%8])); // actualizando el estado de los leds
    }
    NeoPixel.show(); 
    delay(10);
  }
}

int opcion = 0; //0 para seleccionar imagenes y 1 para potenciometro
int selected = -1;

/////////////********************** OPCIONES PARA VOZ **********************/////////////
void shbocaCerrada(){
  NeoPixel.clear();
  NeoPixel.show();
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {           // para cada led
    NeoPixel.setPixelColor(pixel, NeoPixel.Color(bocaCerrada[pixel/8][pixel%8],bocaCerrada[pixel/8][pixel%8],bocaCerrada[pixel/8][pixel%8])); // actualizando el estado de los leds
    NeoPixel.show(); 
    delay(10);
  } 
}

void shbocaLinea(){
  NeoPixel.clear();
  NeoPixel.show();
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {           // para cada led
    NeoPixel.setPixelColor(pixel, NeoPixel.Color(bocaLinea[pixel/8][pixel%8],bocaLinea[pixel/8][pixel%8],bocaLinea[pixel/8][pixel%8])); // actualizando el estado de los leds
    NeoPixel.show(); 
    delay(10);
  } 
}

void shbocaAbierto1(){
  NeoPixel.clear();
  NeoPixel.show();
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {           // para cada led
    NeoPixel.setPixelColor(pixel, NeoPixel.Color(llbocaAbierto1[pixel/8][pixel%8],llbocaAbierto1[pixel/8][pixel%8],llbocaAbierto1[pixel/8][pixel%8])); // actualizando el estado de los leds
    NeoPixel.show(); 
    delay(10);
  } 
}
void shbocaAbierto2(){
  NeoPixel.clear();
  NeoPixel.show();
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {           // para cada led
    NeoPixel.setPixelColor(pixel, NeoPixel.Color(llbocaAbierto2[pixel/8][pixel%8],llbocaAbierto2[pixel/8][pixel%8],llbocaAbierto2[pixel/8][pixel%8])); // actualizando el estado de los leds
    NeoPixel.show(); 
    delay(10);
  } 
}

/////////////******************** FIN OPCIONES PARA VOZ **********************/////////////


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
            request->send(SPIFFS, "/index.html", String(), false);
            });
            
  // Ruta para cargar el archivo style.css
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
            request->send(SPIFFS, "/style.css", "text/css");
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



server.on("/assets/faces/angryface.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/assets/faces/angryface.png", "image/png");
});

server.on("/assets/faces/coolface.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/assets/faces/coolface.png", "image/png");
});

server.on("/assets/faces/happyface.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/assets/faces/happyface.png", "image/png");
});

server.on("/assets/faces/heartface.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/assets/faces/heartface.png", "image/png");
});

server.on("/assets/faces/laughingface.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/assets/faces/laughingface.png", "image/png");
});

server.on("/assets/faces/nerdface.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/assets/faces/nerdface.png", "image/png");
});

server.on("/assets/faces/neutralface.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/assets/faces/neutralface.png", "image/png");
});

server.on("/assets/faces/sadface.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/assets/faces/sadface.png", "image/png");
});

server.on("/assets/faces/surprisedface.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/assets/faces/surprisedface.png", "image/png");
});





server.on("/smileyFace", HTTP_GET, [](AsyncWebServerRequest *request){
            //obtener imagen seleccionada
            opcion = 0;
            showSmileyFace();
            request->send(SPIFFS, "/index.html", String(), false);
            });

server.on("/sadFace", HTTP_GET, [](AsyncWebServerRequest *request){
            //obtener imagen seleccionada
            opcion = 0;
            showSadFace();
            request->send(SPIFFS, "/index.html", String(), false);
            });


server.on("/neutralFace", HTTP_GET, [](AsyncWebServerRequest *request){
            //obtener imagen seleccionada
            opcion = 0;
            showNeutralFace();
            request->send(SPIFFS, "/index.html", String(), false);
            });

server.on("/surprisedFace", HTTP_GET, [](AsyncWebServerRequest *request){
            //obtener imagen seleccionada
            opcion = 0;
            showSurprisedFace();
            request->send(SPIFFS, "/index.html", String(), false);
            });

server.on("/heartFace", HTTP_GET, [](AsyncWebServerRequest *request){
            //obtener imagen seleccionada
            opcion = 0;
            showHeartFace();
            request->send(SPIFFS, "/index.html", String(), false);
            });

server.on("/laughFace", HTTP_GET, [](AsyncWebServerRequest *request){
            //obtener imagen seleccionada
            opcion = 0;
            showLaughFace();
            request->send(SPIFFS, "/index.html", String(), false);
            });

server.on("/angryFace", HTTP_GET, [](AsyncWebServerRequest *request){
            //obtener imagen seleccionada
            opcion = 0;
            showAngryFace();
            request->send(SPIFFS, "/index.html", String(), false);
            });


server.on("/nerdFace", HTTP_GET, [](AsyncWebServerRequest *request){
            //obtener imagen seleccionada
            opcion = 0;
            showNerdFace();
            request->send(SPIFFS, "/index.html", String(), false);
            });

            

server.on("/coolFace", HTTP_GET, [](AsyncWebServerRequest *request){
            //obtener imagen seleccionada
            showCoolFace();
            request->send(SPIFFS, "/index.html", String(), false);
            });

server.on("/ucbFace", HTTP_GET, [](AsyncWebServerRequest *request){
            //obtener imagen seleccionada
            opcion = 0;
            showUcbFace();
            request->send(SPIFFS, "/index.html", String(), false);
            });



            server.on("/images", HTTP_GET, [](AsyncWebServerRequest *request){
            //obtener imagen seleccionada
            opcion=0;
            request->send(SPIFFS, "/index.html", String(), false);
            });

            server.on("/voice", HTTP_GET, [](AsyncWebServerRequest *request){
            //obtener imagen seleccionada
            opcion=1;
            request->send(SPIFFS, "/index.html", String(), false);
            });


// Inicio del servidor
  server.begin();
}

void loop(){
  
  if(opcion==1){
    Serial.println(getTemperature());
    
     if(getTemperature()>0 && getTemperature()<=1000 && selected!=1){
      selected=1;
      shbocaCerrada();
    }
    
    if(getTemperature()>1000 && getTemperature()<=2100 && selected!=2){
      selected=2;
      shbocaLinea();
    }

    if(getTemperature()>2100 && getTemperature()<=3000 && selected!=3){
      selected=3;
      shbocaAbierto1();
    }

    if(getTemperature()>3000 && getTemperature()<=4100 && selected!=4){
      selected=4;
      shbocaAbierto2();
    }


    
  }

}
