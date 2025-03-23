//Parte Web 1

/*


#include <Arduino.h>
#include <WiFi.h> 
#include <WebServer.h> 
void handle_root();
// SSID & Password 
const char* ssid = "Nautilus";  // Enter your SSID here 
const char* password = "20000Leguas";  //Enter your Password here 
WebServer server(80);  // Object of WebServer(HTTP port, 80 is defult) 
void setup() { 
 Serial.begin(115200); 
 Serial.println("Try Connecting to "); 
 Serial.println(ssid); 
 // Connect to your wi-fi modem 
 WiFi.begin(ssid, password); 
 // Check wi-fi is connected to wi-fi network 
 while (WiFi.status() != WL_CONNECTED) { 
 delay(1000); 
 Serial.print("."); 
 } 
 Serial.println(""); 
 Serial.println("WiFi connected successfully"); 
 Serial.print("Got IP: "); 
 Serial.println(WiFi.localIP());  //Show ESP32 IP on serial 
 server.on("/", handle_root); 
 server.begin(); 
 Serial.println("HTTP server started"); 
 delay(100);  
} 
void loop() { 
 server.handleClient(); 
} 
// HTML & CSS contents which display on web server 
String HTML = "<!DOCTYPE html>\ 
<html>\ 
<body>\ 
<h1>My Primera Pagina con ESP32 - Station Mode &#128522;</h1>\ 
</body>\ 
</html>"; 
// Handle root url (/) 
void handle_root() { 
 server.send(200, "text/html", HTML); 
}

// Parte Web 2

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

void handle_root();

// SSID & Password 
const char* ssid = "Nautilus";  // Enter your SSID here 
const char* password = "20000Leguas";  //Enter your Password here 

WebServer server(80);  // Object of WebServer(HTTP port, 80 is default) 

void setup() { 
  Serial.begin(115200); 
  Serial.println("Try Connecting to "); 
  Serial.println(ssid); 

  WiFi.begin(ssid, password); 

  while (WiFi.status() != WL_CONNECTED) { 
    delay(1000); 
    Serial.print("."); 
  } 

  Serial.println(""); 
  Serial.println("WiFi connected successfully"); 
  Serial.print("Got IP: "); 
  Serial.println(WiFi.localIP());  // Show ESP32 IP on serial 
  
  server.on("/", handle_root); 
  server.begin(); 
  Serial.println("HTTP server started"); 
  delay(100);  
} 

void loop() { 
  server.handleClient(); 
} 

// HTML & CSS with animation
String HTML = "<!DOCTYPE html>\
<html>\
<head>\
<style>\
@keyframes bounce {\
  0% { transform: scale(1); }\
  50% { transform: scale(1.5); }\
  100% { transform: scale(1); }\
}\
.circle {\
  width: 100px;\
  height: 100px;\
  background-color: red;\
  border-radius: 50%;\
  position: absolute;\
  top: 50%;\
  left: 50%;\
  transform: translate(-50%, -50%);\
  animation: bounce 2s infinite ease-in-out;\
}\
</style>\
</head>\
<body>\
<h1 style='text-align:center;'>Animación con ESP32 &#128640;</h1>\
<div class='circle'></div>\
</body>\
</html>";

// Handle root URL (/)
void handle_root() { 
  server.send(200, "text/html", HTML); 
}




*/






 

 // Parte Bluetooth para ESP32








 /* 
 
 
 


//This example code is in the Public Domain (or CC0 licensed, at your option.) 
//By Evandro Copercini - 2018 
//This example creates a bridge between Serial and Classical Bluetooth (SPP) 
//and also demonstrate that SerialBT have the same functionalities of a normal Serial 

#include "BluetoothSerial.h" 
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED) 
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable 
it 
#endif 
BluetoothSerial SerialBT; 
void setup() { 
  Serial.begin(115200); 
  SerialBT.begin("ESP32test"); //Bluetooth device name 
  Serial.println("The device started, now you can pair it with 
bluetooth!"); 
} 
void loop() { 
  if (Serial.available()) { 
    SerialBT.write(Serial.read()); 
  } 
  if (SerialBT.available()) { 
    Serial.write(SerialBT.read()); 
  } 
  delay(20); 
}
  

 

*/




// Parte Bluetooth para ESP32-S3







/*






#include <Arduino.h>
#include <NimBLEDevice.h>

// Definir UUIDs para el servicio y la característica
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

NimBLEServer* pServer = nullptr;
NimBLECharacteristic* pCharacteristic = nullptr;

void setup() {
    Serial.begin(115200);
    Serial.println("Iniciando BLE con NimBLE!");

    // Inicializar el dispositivo BLE con un nombre
    NimBLEDevice::init("ESP32-NimBLE");

    // Crear el servidor BLE
    pServer = NimBLEDevice::createServer();

    // Crear el servicio BLE
    NimBLEService* pService = pServer->createService(SERVICE_UUID);

    // Crear la característica BLE con permisos de lectura y escritura
    pCharacteristic = pService->createCharacteristic(
                          CHARACTERISTIC_UUID,
                          NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE
                      );

    // Establecer un valor inicial para la característica
    pCharacteristic->setValue("Hola desde ESP32 NimBLE");

    // Iniciar el servicio
    pService->start();

    // Iniciar la publicidad para que otros dispositivos puedan encontrar el servidor
    NimBLEAdvertising* pAdvertising = NimBLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06);
    pAdvertising->setMinPreferred(0x12);
    NimBLEDevice::startAdvertising();

    Serial.println("¡Servidor BLE NimBLE activo!");
}

void loop() {
    delay(2000); // Pequeña pausa en el loop
}
 



 */




// Parte de Mejora 1 (Pagina Web)




/*





#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

void handle_root();
// Configuración del Access Point (AP)
const char* ssid = "Nautilus";    // Nombre de la red WiFi creada por el ESP32
const char* password = "20000Leguas"; // Contraseña del AP (mínimo 8 caracteres)

WebServer server(80); // Servidor web en el puerto 80

// Página HTML que se mostrará en el navegador
String HTML = "<!DOCTYPE html>\
<html>\
<head><title>ESP32 Access Point</title></head>\
<body>\
<h1>ESP32 en Modo AP</h1>\
<p>Estás conectado al ESP32 en modo Access Point.</p>\
</body>\
</html>";

// Manejo de la raíz "/"
void handle_root() {
    server.send(200, "text/html", HTML);
}

void setup() {
    Serial.begin(115200);
    Serial.println("Iniciando Access Point...");

    // Configurar el ESP32 como Access Point (sin conexión a internet)
    WiFi.softAP(ssid, password);

    // Mostrar la dirección IP del AP
    Serial.print("AP IP address: ");
    Serial.println(WiFi.softAPIP());

    // Configurar el servidor web
    server.on("/", handle_root);
    server.begin();
    Serial.println("Servidor web iniciado en modo AP.");
}

void loop() {
    server.handleClient(); // Manejar solicitudes de clientes
}





*/





// Parte de Mejora 2 (Bluetooth)





/*





#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// Definir UUIDs para el servicio y la característica
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando trabajo con BLE!");

  // Inicializar el dispositivo BLE con un nombre
  BLEDevice::init("MyESP32");

  // Crear el servidor BLE
  BLEServer *pServer = BLEDevice::createServer();

  // Crear el servicio BLE
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Crear la característica BLE con permisos de lectura y escritura
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  // Establecer un valor inicial para la característica
  pCharacteristic->setValue("Hola Mundo desde ESP32");
  
  // Iniciar el servicio
  pService->start();

  // Iniciar la publicidad para que otros dispositivos puedan encontrar el servidor
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // Funciones que ayudan con problemas de conexión en iPhone
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();

  Serial.println("¡Característica definida! Ahora puedes leerla en tu dispositivo.");
}

void loop() {
  // Código principal que se ejecuta repetidamente
  delay(2000);
}






*/