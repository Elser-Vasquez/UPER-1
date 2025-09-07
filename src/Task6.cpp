/*INFORMACION DE PROCESO==================================================================
  * PROCESO:
    - NOMBRE  : Task6 - ACTUALIZACION OTA
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
#include "Task6.h"

#include <HTTPClient.h>
#include <WiFiClient.h>
#include <Update.h>
//----------------------------------------------------------------------------------------
//DECLARACION DE VARIABLES LOCALES--------------------------------------------------------
String version = "";
String url = "";
bool update1 = false;
//----------------------------------------------------------------------------------------
//DECLARACION DE FUNCIONES INTERNAS (Alcance local) --------------------------------------


// ===== FUNCIÓN OTA CON PROGRESO =====
bool performOTA() {
  Serial.println("🔄 Iniciando descarga OTA...");

  HTTPClient http;
  http.begin(url);

  int httpCode = http.GET();
  if (httpCode != HTTP_CODE_OK) {
    Serial.printf("❌ Error HTTP: %d\n", httpCode);
    http.end();
    return false;
  }

  int contentLength = http.getSize();
  if (contentLength <= 0) {
    Serial.println("❌ No se pudo obtener tamaño del archivo");
    http.end();
    return false;
  }

  Serial.printf("📦 Tamaño del archivo: %d bytes (%.2f KB)\n", contentLength, contentLength / 1024.0);

  WiFiClient *stream = http.getStreamPtr();

  if (!Update.begin(contentLength)) {
    Serial.println("❌ Error iniciando Update");
    http.end();
    return false;
  }

  uint8_t buff[512];
  int writtenTotal = 0;
  unsigned long lastPrint = millis();

  while (http.connected() && (writtenTotal < contentLength)) {
    size_t sizeAvailable = stream->available();
    if (sizeAvailable) {
      int bytesRead = stream->readBytes(buff, ((sizeAvailable > sizeof(buff)) ? sizeof(buff) : sizeAvailable));
      int written = Update.write(buff, bytesRead);

      if (written > 0) {
        writtenTotal += written;
      }

      // Mostrar progreso cada 500ms para no saturar la consola
      if (millis() - lastPrint > 500) {
        int progress = (writtenTotal * 100) / contentLength;
        Serial.printf("⬇️ Progreso OTA: %d%% (%d/%d bytes)\n", progress, writtenTotal, contentLength);
        lastPrint = millis();
      }
    }
    delay(1); // Cede tiempo al sistema
  }

  if (!Update.end()) {
    Serial.printf("❌ Error OTA: %s\n", Update.errorString());
    http.end();
    return false;
  }

  if (Update.isFinished()) {
    Serial.println("✅ OTA completada, reiniciando...");
    delay(1000);
    ESP.restart();
  } else {
    Serial.println("❌ OTA incompleta");
    return false;
  }

  http.end();
  return true;
}







//----------------------------------------------------------------------------------------
//DECLARACION DE FUNCIONES DE EJECUCION (Setup - Loop) -----------------------------------
void task6_setup() {
  msg(6, "setup", "OTA", "....", "...");


  
}

void task6_loop() {                     //este es el while de trabajos principal de ejecucion de procesos.
  if(update1){
    update1 = false;
    Serial.println("🚀 Task6: Ejecutando OTA");

    // Suspender tareas críticas
    //vTaskSuspend(task1Handle);
    //vTaskSuspend(task2Handle);
    //vTaskSuspend(task3Handle);
    //vTaskSuspend(task4Handle);
    vTaskSuspend(task5Handle);

    Serial.println("🚀 DETENIENDO TAREAS NO NECESARIAS");

    bool ok = performOTA();

    if (!ok) {
      Serial.println("⚠️ OTA fallida, reanudando tareas...");
      //vTaskResume(task1Handle);
      //vTaskResume(task2Handle);
      //vTaskResume(task3Handle);
      //vTaskResume(task4Handle);
      vTaskResume(task5Handle);
    }

  }

  vTaskDelay(1000 / portTICK_PERIOD_MS);
}


//----------------------------------------------------------------------------------------
//DECLARACION DE FUNCIONES EXTERNAS (Exportadas) -----------------------------------------

void input_sub_ota(){
  if (json_rx.containsKey("version")) {
    //version = json_rx["version"];
    version = json_rx["version"].as<String>();


    Serial.print("👉 verion: ");
    Serial.println(version);

      if (json_rx.containsKey("url")) {
        //url = json_rx["url"];
        url = json_rx["url"].as<String>();
        Serial.print("👉 Valor de url: ");
        Serial.println(url);
        update1 = true;
      }
  }

}


//----------------------------------------------------------------------------------------
//DECLARACION DE TAREA FreeRTOS-----------------------------------------------------------
void task6_run(void *param) {
  task6_setup();
  for (;;) task6_loop();
}