/*INFORMACION DE PROCESO==================================================================
  * PROCESO:
    - NOMBRE  : Task1 - CRUD DATA EEPROM
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
#include "Task1.h"


//----------------------------------------------------------------------------------------
//DECLARACION DE VARIABLES LOCALES--------------------------------------------------------



//----------------------------------------------------------------------------------------
//DECLARACION DE FUNCIONES INTERNAS (Alcance local) --------------------------------------



//----------------------------------------------------------------------------------------
//DECLARACION DE FUNCIONES DE EJECUCION (Setup - Loop) -----------------------------------
void task1_setup() {
  msg(1, "setup", "load", "eeprom", "...");
  flag1 = true;    //activar solo despues de leer memoria

}

void task1_loop() {
  
  msg(1, "loop", "while", "deviceId", String(DEVICE_ID));
  //vTaskDelay(50 / portTICK_PERIOD_MS);
  vTaskDelete(NULL); // Finaliza la tarea
}


//----------------------------------------------------------------------------------------
//DECLARACION DE FUNCIONES EXTERNAS (Exportadas) -----------------------------------------



//----------------------------------------------------------------------------------------
//DECLARACION DE TAREA FreeRTOS-----------------------------------------------------------
void task1_run(void *param) {
  task1_setup();
  for (;;) task1_loop();
}

