/*INFORMACION DE PROCESO==================================================================
  * PROCESO:
    - NOMBRE  : Task5 - PERIFERICOS ACCTIONS
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
#include "Task5.h"


//----------------------------------------------------------------------------------------
//DECLARACION DE VARIABLES LOCALES--------------------------------------------------------
#define LED_PIN 2

int tt = 500;
//----------------------------------------------------------------------------------------
//DECLARACION DE FUNCIONES INTERNAS (Alcance local) --------------------------------------



//----------------------------------------------------------------------------------------
//DECLARACION DE FUNCIONES DE EJECUCION (Setup - Loop) -----------------------------------
void task5_setup() {
  msg(5, "setup", "Perifericos", "....", "...");

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // iniciar apagado
  
}

void task5_loop() {                     //este es el while de trabajos principal de ejecucion de procesos.
  if(flag3){
    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(tt / portTICK_PERIOD_MS);
    digitalWrite(LED_PIN, LOW);
    vTaskDelay(tt / portTICK_PERIOD_MS);


  }

}


//----------------------------------------------------------------------------------------
//DECLARACION DE FUNCIONES EXTERNAS (Exportadas) -----------------------------------------

void input_sub_cmd(){

}
void input_sub_config(){

}

void input_sub_control(){
  if (json_rx.containsKey("led")) {
    bool ledState = json_rx["led"];

    Serial.print("👉 Valor de LED: ");
    Serial.println(ledState ? "ON" : "OFF");

    // Controlar el LED físico
    digitalWrite(LED_PIN, ledState ? HIGH : LOW);
  }

  if (json_rx.containsKey("tt")) {
    tt = json_rx["tt"];
    Serial.print("👉 Valor de tt: ");
    Serial.println(tt);
  }
}


//----------------------------------------------------------------------------------------
//DECLARACION DE TAREA FreeRTOS-----------------------------------------------------------
void task5_run(void *param) {
  task5_setup();
  for (;;) task5_loop();
}