/*INFORMACION DE PROCESO==================================================================
  * PROCESO:
    - NOMBRE  : Task3 - CONN AWS-MQTT-RX
    - VERSION : v1.0.0
  * DESCRIPCIÓN:
    - Proceso con funciones . . . 
  * FUNCIONES:
    - 
  * DEVELOPER:
    - NOMBRE  : Elser Vasquez Vargas
    - EMAIL   : vasquez.95.elser@gmail.com
  * FECHA : 06/08/2025
========================================================================================*/


//----------------------------------------------------------------------------------------
//IMPORTACION DE LIBRERIAS----------------------------------------------------------------
#include "Task3.h"


//----------------------------------------------------------------------------------------
//DECLARACION DE VARIABLES LOCALES--------------------------------------------------------

const char* AWS_ENDPOINT = "a162v7g8my7r6m-ats.iot.sa-east-1.amazonaws.com";  // endpoint de AWS IoT
const int AWS_PORT = 8883;

//const char* DEVICE_ID = "esp32_1";  //esta ya globalmente

const char* TOPIC_PUBLISH   = "esp32/pub";   // Para enviar datos a AWS IoT

const char* TOPIC_PUB_1 = "/telemetry";     //Datos periódicos de sensores y monitoreo.
const char* TOPIC_PUB_2 = "/status";        //Reporte periódico de estado del dispositivo.
const char* TOPIC_PUB_3 = "/event";         //Evento puntual (alarma o acción ejecutada).
const char* TOPIC_PUB_4 = "/logs";          //Dantos relacionados con logs del dispocitivo.

const char* TOPIC_SUB_1 = "/cmd";           //Comandos específicos enviados al dispositivo (ej. "reboot", "update_fw", "set_threshold").
const char* TOPIC_SUB_2 = "/config";        //Configuración dinámica enviada desde el servidor: intervalos de muestreo, parámetros de sensores, thresholds.
const char* TOPIC_SUB_3 = "/ota";           //Canal dedicado a actualizaciones OTA (URL del firmware, checksum, trigger de update).
const char* TOPIC_SUB_4 = "/control";       //Acciones de control remoto directas (ej. encender LED, activar relé, abrir/cerrar válvula).

// Buffers para almacenar los tópicos completos (DEVICE_ID + sufijo)
char topic_sub_cmd[50];
char topic_sub_config[50];
char topic_sub_ota[50];
char topic_sub_control[50];

char topic_pub_telemetry[50];
char topic_pub_status[50];
char topic_pub_event[50];
char topic_pub_logs[50];

static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";

static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWTCCAkGgAwIBAgIUXo8ug6Ijm8xrZqdbO+5sj+goc8cwDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTI1MDgyNDE3MzYx
N1oXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAOm2S863XwqZqDe+0vX1
BrMvIlk250m12BnTHXohSGldmgRlBpgtW863dCGfyAoyF7TOe5q/AesT2g7X46F8
Qul3fxU0j1gOLuQA6uuX9lDVffHq+ubnrY7RveIU8Va5WC0ZhGvEgw1+klj2GcJe
9W06Wmg3+vlRgCNc8pSxDED+mSVB5oJKbJ6jhHZmv8HA9cb3ql24YrjEpPXBVkQY
fdlNSWRnWaERIixRLsDlAz1MGlseZ5xFYnjpSTolVYQzV8FZ3ftuRFe4blKD2UuL
EWkQGmxkmrL/K2BGfe4voXMobhPVLvgqdNKw+S6gYTEjSGmZt4Hh2bo5yGT90VQP
+FMCAwEAAaNgMF4wHwYDVR0jBBgwFoAU+PyzmMPD4G50hI7qeL4t7X1EcxMwHQYD
VR0OBBYEFDT+1iQ97OetI5AGZHwrXNo+U5nQMAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQCrN8D6nfmWSouiA2NnkIHfjGuo
+Yr2SjZdxRdv7j9kFMaCieW/tDQ9CREtH7thaxO3tuEQ79p4BmkIcUERr0PteGUV
OkKYbfpZJjW/ORKfLuZUpMOAhm4924txg9WD12YJCzukBjYy45dCcaysXWL3thkL
czaUXoNGIQCuq2KGVNKfIKqQ+trPUX8KUXvY8LDbdl2Qy8zkm64t+VHibLM5BM/q
SEnR3ocOSfkC9YBfpUWeljKl/qSv94IeQkzfBga7w5gjiLBGpTUrjw54EpO0abGJ
tozThU0gyd7BncSzp2zdyxjqkD9CpHgOOnK+ha+ewM+MiR9RRUUUeJqijgyi
-----END CERTIFICATE-----
)KEY";

static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEpAIBAAKCAQEA6bZLzrdfCpmoN77S9fUGsy8iWTbnSbXYGdMdeiFIaV2aBGUG
mC1bzrd0IZ/ICjIXtM57mr8B6xPaDtfjoXxC6Xd/FTSPWA4u5ADq65f2UNV98er6
5uetjtG94hTxVrlYLRmEa8SDDX6SWPYZwl71bTpaaDf6+VGAI1zylLEMQP6ZJUHm
gkpsnqOEdma/wcD1xveqXbhiuMSk9cFWRBh92U1JZGdZoREiLFEuwOUDPUwaWx5n
nEVieOlJOiVVhDNXwVnd+25EV7huUoPZS4sRaRAabGSasv8rYEZ97i+hcyhuE9Uu
+Cp00rD5LqBhMSNIaZm3geHZujnIZP3RVA/4UwIDAQABAoIBABS2QyGevp2B4JaQ
IsIJZP6cPr8JTpYJt40SWJpqOLCdyvh4u4zg+DHpsDEKp/+/ULqFUg70vobGy5xl
JZc6G/P00x5d+hYjq6QpMKiQXxPq166I1JOCFK+DhwByOrEk29ujV0j1sWeQwAeC
R+Yh5D453ak+zM8rmd+IbTcgOaXIvwy7bgVkH2VQZ8M/B+KxOi3tHCGoPQCwyEpN
amMuaC0N64kXlWtK++sx53DVE7X/bjGierAyuCytWTzRe2NEWNDGrqbXi1fojJTp
Yrb4n3a/Rvnk/O6QY/cxmuBsKbTZuXFZxGWhQsHmi34YL3ozGLUjnhEedvgXGZK7
tezW3AECgYEA+X/PeV9q2x1SklRaPwQDH+wu6qXsr2whFilb+TXLihmPOiLiu0mi
Vx8Suc6G94VnHK/CG8K14cq4hdjorZlD8NkMaXUoQz0rWZpNGImx/5yJzAo4EQhB
VPk6IgKwjIScycewCh3rlYVPxX2ri+AbP5DhazEdzj6qe1rS7QOfZXMCgYEA780u
9IFHu2c7NmE4cSZrdfrnVfy3TsM3QtmLPUtEsagzdIAlej9v4sHhP+7+o4+OxH+b
OWVPqZxQ8XonIx/W5DabDl/q7sqwJQ1IwL3ScFP8Lj5iijczgAeYnAHA7WTfo88t
WnoVmVhA4ETkuEv7NlLjLROQNM1zuTZdSX23aaECgYEA2/jgvnzu5DLNGzB9xLNP
4fRFRSJ3NA7ceQKMEYNpad+xFKuvRTrdg3xk8SbyfgbC61rWg80+uM0XtQKR2oSX
jyB+PfhKQEYNE1nkgS7dnaSxJREZb4LcvwNhSp0edTVyWsDRJ4pLq682rsNm3NMA
kyG0bOKICc/cVRe1gbxA65sCgYEAlaWUAd2TqC151CvDj0kMkqmrKAv3UN2eZMdh
jzSjf8KZqcA2ox1nczjOmplIq0VxMMr5UU4Z8pysHqW+Orsp3Wz+QnA1KiOu3NB3
cGCFLLgcjbc8w0hDiUg0QlcN0Je8wHsPsICzbeiXQ916ZlB0SqhbQMwOmAUGjLSS
bsRXa0ECgYAwERYX1MQYd6sDa5bOQ8BjcF0uR45qLFUP+R8HzTCUMnnxoYpleWIU
yti+qfqUM3QqertXZpp9jB0c+IrEM3zWzFyO2blOugmGq8A3YTKPLMdZy2SPqHdL
Cq7OW6PxIi4StvQAx7Rlkg2coHtzCsGE7vBskOLsIzisTlFx5+Xlxg==
-----END RSA PRIVATE KEY-----
)KEY";

// 📌 Objetos WiFi y MQTT
WiFiClientSecure wifiClient;
PubSubClient mqttClient(wifiClient);


//----------------------------------------------------------------------------------------
//DECLARACION DE FUNCIONES INTERNAS (Alcance local) --------------------------------------

// Callback para mensajes MQTT
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("📩 Mensaje en [");
  Serial.print(topic);
  Serial.println("]: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // 1️⃣ Crear un buffer temporal con el payload (añadir '\0' al final para seguridad)
  char buffer[length + 1];
  memcpy(buffer, payload, length);
  buffer[length] = '\0';

  // 3️⃣ Parsear el JSON
  DeserializationError error = deserializeJson(json_rx, buffer);
  if (error) {
    Serial.print("❌ Error al parsear JSON: ");
    Serial.println(error.c_str());
    return;
  }else {
    if (strcmp(topic, topic_sub_cmd) == 0) {
      input_sub_cmd();
    } 
    else if (strcmp(topic, topic_sub_config) == 0) {
      input_sub_config();
    } 
    else if (strcmp(topic, topic_sub_ota) == 0) {
      input_sub_ota();
    } 
    else if (strcmp(topic, topic_sub_control) == 0) {
      input_sub_control();
    } 
    else {
      Serial.println("→ Topic desconocido");
    }


    //update_io();   //aqui se procesa y se actua respecto a los datos de entrada.
  }


}

void connectAWS() {
  wifiClient.setCACert(AWS_CERT_CA);
  wifiClient.setCertificate(AWS_CERT_CRT);
  wifiClient.setPrivateKey(AWS_CERT_PRIVATE);

  mqttClient.setServer(AWS_ENDPOINT, AWS_PORT);
  mqttClient.setCallback(callback);

  Serial.println("🔐 Conectando a AWS IoT...");
  if (!mqttClient.connected()) {
    if (mqttClient.connect(DEVICE_ID)) {
      Serial.println("✅ Conectado a AWS IoT!");

      // Suscribir a múltiples tópicos
      mqttClient.subscribe(topic_sub_cmd);
      mqttClient.subscribe(topic_sub_config);
      mqttClient.subscribe(topic_sub_ota);
      mqttClient.subscribe(topic_sub_control);

      Serial.println("📡 Suscrito a:");
      Serial.println(topic_sub_cmd);
      Serial.println(topic_sub_config);
      Serial.println(topic_sub_ota);
      Serial.println(topic_sub_control);

      flag3 = true;
    } else {
      Serial.print("❌ Error conectando MQTT, rc=");
      Serial.println(mqttClient.state());
      flag3 = false;
    }
  }
}



//----------------------------------------------------------------------------------------
//DECLARACION DE FUNCIONES DE EJECUCION (Setup - Loop) -----------------------------------
void task3_setup() {
  msg(3, "setup", "load", "CONN AWS MQTT", "...");

  // Construir los tópicos dinámicos usando DEVICE_ID
  snprintf(topic_sub_cmd, sizeof(topic_sub_cmd), "%s%s", DEVICE_ID, TOPIC_SUB_1);
  snprintf(topic_sub_config, sizeof(topic_sub_config), "%s%s", DEVICE_ID, TOPIC_SUB_2);
  snprintf(topic_sub_ota, sizeof(topic_sub_ota), "%s%s", DEVICE_ID, TOPIC_SUB_3);
  snprintf(topic_sub_control, sizeof(topic_sub_control), "%s%s", DEVICE_ID, TOPIC_SUB_4);

  snprintf(topic_pub_telemetry, sizeof(topic_pub_telemetry), "%s%s", DEVICE_ID, TOPIC_PUB_1);
  snprintf(topic_pub_status, sizeof(topic_pub_status), "%s%s", DEVICE_ID, TOPIC_PUB_2);
  snprintf(topic_pub_event, sizeof(topic_pub_event), "%s%s", DEVICE_ID, TOPIC_PUB_3);
  snprintf(topic_pub_logs, sizeof(topic_pub_logs), "%s%s", DEVICE_ID, TOPIC_PUB_4);

}

void task3_loop() {

  if (flag2){
    if (!mqttClient.connected()) {
      connectAWS();
    }

    if (flag3){
      mqttClient.loop();
    }
  }
  
  //msg(3, "loop", "while", "callback", "...");
  vTaskDelay(100 / portTICK_PERIOD_MS);
}


//----------------------------------------------------------------------------------------
//DECLARACION DE FUNCIONES EXTERNAS (Exportadas) -----------------------------------------
void send_mqtt() {
  int randomValue = random(0, 100); // número aleatorio entre 0-99
  String message = "{ \"data\": " + String(randomValue) + "}";
  mqttClient.publish(topic_pub_telemetry, message.c_str());
  Serial.println("📤 Publicado en " + String(topic_pub_telemetry) + ": " + message);

}


//----------------------------------------------------------------------------------------
//DECLARACION DE TAREA FreeRTOS-----------------------------------------------------------
void task3_run(void *param) {
  task3_setup();
  for (;;) task3_loop();
}