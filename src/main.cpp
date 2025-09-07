/*INFORMACION DE PROCESO==================================================================
  * PROCESO:
    - NOMBRE  : ......
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
#include "GlobalDef.h"
#include "Task1.h"
#include "Task2.h"
#include "Task3.h"
#include "Task4.h"
#include "Task5.h"
#include "Task6.h"

//----------------------------------------------------------------------------------------
//DECLARACION DE VARIABLES LOCALES--------------------------------------------------------


// Handles reales de las tareas
TaskHandle_t task1Handle = NULL;
TaskHandle_t task2Handle = NULL;
TaskHandle_t task3Handle = NULL;
TaskHandle_t task4Handle = NULL;
TaskHandle_t task5Handle = NULL;
TaskHandle_t task6Handle = NULL;

//----------------------------------------------------------------------------------------
//DECLARACION DE FUNCIONES DE EJECUCION (Setup - Loop) -----------------------------------
void setup() {
  Serial.begin(115200);

  uint64_t chipid = ESP.getEfuseMac();  // obtiene el ID único del chip
  sprintf(DEVICE_ID, "%llX", chipid);   // convierte a string en hexadecimal

  Serial.println("VERSION SUBIDA ... PLATFORMIO .... OTA");
  
  /** Crear tareas en los núcleos
  xTaskCreatePinnedToCore(task1_run, "Task1", 3000, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(task2_run, "Task2", 3000, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(task3_run, "Task3", 8192, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(task4_run, "Task4", 8192, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(task5_run, "Task5", 3000, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(task6_run, "Task6", 8192, NULL, 1, NULL, 1);    */

  // Crear tareas en los núcleos
  xTaskCreatePinnedToCore(task1_run, "Task1", 3000, NULL, 1, &task1Handle, 0);
  xTaskCreatePinnedToCore(task2_run, "Task2", 3000, NULL, 3, &task2Handle, 0);
  xTaskCreatePinnedToCore(task3_run, "Task3", 8192, NULL, 2, &task3Handle, 0);
  xTaskCreatePinnedToCore(task4_run, "Task4", 8192, NULL, 1, &task4Handle, 1);
  xTaskCreatePinnedToCore(task5_run, "Task5", 3000, NULL, 1, &task5Handle, 1);
  xTaskCreatePinnedToCore(task6_run, "Task6", 8192, NULL, 1, &task6Handle, 1);

}

void loop() {}