# PRACTICA 3: WIFI Y BLUETOOTH

En esta práctica hemos tenido como objetivo comprender y trabajar con el funcionamiento de wifi y bluetooth de nuestro microprocesador ESP32-S3. Así pues como objetivo tenemos generar un web server utilizando el microprocesador además de realizar una conexión serie con una aplicación móvil vía bluetooth.


## Practica A

En esta parte de la práctica hemos generado un codigo que convierte nuestro ESP32-S3 en un servidor web en modo estación, lo que permite que cualquier dispositivo en la misma red WiFi acceda a la página web alojada en el microprocesador. En el código se importan dos librerías (“WiFi.h” y ”WebServer.h”) que permiten tanto conectar el  ESP32 a una red wifi como crear un servidor web simple en el mismo. Gracias a la función “WebServer server(80)”  se crea un servidor en el puerto 80 (el puerto HTTP por defecto). Una vez el usuario accede a la dirección IP del microprocesador desde un navegador (conectado a la misma red que el ESP32-S3), se carga la página web con un mensaje de bienvenida.

```
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

```

Una vez generado el código anterior, lo hemos modificado de manera que incluya css dentro del html del código, generando así que en la página web creada por el dispositivo ESP32-S3 se muestre una animación de un círculo rojo que rebota. En este segundo código hemos usado el mismo tipo de función que en el código anterior.

```
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
```
En los dos casos al acceder al serial monitor obtenemos:
![image](https://github.com/user-attachments/assets/717aa1df-110a-426f-b571-f4c12021cabb)

## Practica B

En esta segunda parte de la práctica hemos generado un código que convierte el ESP32 en un servidor bluetooth low energy (BLE) dado que el código que obtuvimos en el guión de prácticas no era compatible con nuestro microprocesador ESP32-S3. Así pues en nuestro código propuesto se configura un servidor BLE en el ESP32-SE con la librería NimBLE. Primero se definen las UUIDS (“SERVICE_UUID” y “CHARASATERISTIC_UUID”) las cuales identifican el servicio BLE creado por el dispositivo ESP32 e identifican la característica BLE dentro del servicio. Una vez definidas las UUIDS se inicializa el BLE en el setup(), para a continuación crear el servidor BLE.

```
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
 
```

## Practica Extra 1 (Web)

En este ejercicio extra hemos generado un código que convierte nuestro ESP32-S3 en un punto de acceso WiFi (Access Point - AP) y aloja un servidor web que muestra una página HTML cuando un usuario se conecta a su red. En nuestro código primero se define la SSID y la contraseña para posteriormente iniciar un servidor Web en el ESP32-S3 en el puerto 80 (puerto estándar). Una vez el usuario entre en la página web se muestra un mensaje que indica que la ESP32 está funcionando como Access Point.

```
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
```

## Practica Extra 2 (BLE)

En este segundo ejercicio extra hemos desarrollado un código similar al de la práctica B solo que en lugar de usar la librería NimBLE hemos usado la librería BLEDevice. Las funciones en el código son prácticamente las mismas. Se definen las UUIDS para luego inicializar el BLE en el setup() y finalmente crear el servidor BLE.

```
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
```
