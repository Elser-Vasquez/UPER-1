/*INFORMACION DE PROCESO==================================================================
  * PROCESO:
    - NOMBRE  : Task4 - CONN AWS-MQTT-TX
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
#include "Task4.h"


//----------------------------------------------------------------------------------------
//DECLARACION DE VARIABLES LOCALES--------------------------------------------------------


// 📌 Objetos WiFi y MQTT
//WiFiClientSecure wifiClient;
//PubSubClient mqttClient(wifiClient);


//----------------------------------------------------------------------------------------
//DECLARACION DE FUNCIONES INTERNAS (Alcance local) --------------------------------------



//----------------------------------------------------------------------------------------
//DECLARACION DE FUNCIONES DE EJECUCION (Setup - Loop) -----------------------------------
void task4_setup() {
  msg(4, "setup", "load", "CONN AWS MQTT TX", "...");
  

}

void task4_loop() {
 
  //msg(3, "loop", "while", "callback", "...");
  //Serial.print("flag1:"); Serial.print(flag1);
  //Serial.print("  flag2:"); Serial.print(flag2);
  //Serial.print("  flag3:"); Serial.println(flag3);
  
  if(flag3){ send_mqtt(); }

  vTaskDelay(5000 / portTICK_PERIOD_MS);
}


//----------------------------------------------------------------------------------------
//DECLARACION DE FUNCIONES EXTERNAS (Exportadas) -----------------------------------------



//----------------------------------------------------------------------------------------
//DECLARACION DE TAREA FreeRTOS-----------------------------------------------------------
void task4_run(void *param) {
  task4_setup();
  for (;;) task4_loop();
}