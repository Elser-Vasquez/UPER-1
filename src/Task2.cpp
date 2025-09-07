/*INFORMACION DE PROCESO==================================================================
  * PROCESO:
    - NOMBRE  : Task2 - CONN WIFI
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
#include "Task2.h"


//----------------------------------------------------------------------------------------
//DECLARACION DE VARIABLES LOCALES--------------------------------------------------------
int tk1_n1 = 0;             //variable auxiliar
int tk1_n2 = 0;             //variable auxiliar >> escoger redes
int n_red = 0;              //variable auxiliar escoger red wifi
bool aux_wifi = true;       //variable de enclavamiento de sms de connecion


//----------------------------------------------------------------------------------------
//DECLARACION DE FUNCIONES INTERNAS (Alcance local) --------------------------------------



//----------------------------------------------------------------------------------------
//DECLARACION DE FUNCIONES DE EJECUCION (Setup - Loop) -----------------------------------
void task2_setup() {
  msg(2, "setup", "read", "wifi", "scan");

}

void task2_loop() {
  
  if ( WiFi.status() == WL_CONNECTED ) {
    tk1_n1 = 0;
    if ( aux_wifi ){ flag2 = true; aux_wifi = false; msg(1, "Wifi", "connect", ssid[n_red], "Successful"); }  
  }else { flag2 = false; aux_wifi = true; }

  if ( !flag2 ) {
    tk1_n1++;
    if ( tk1_n1 == 1 ) { 
      msg(1, "Wifi", "connect", ssid[n_red], password[n_red]);    //modificar clave
      WiFi.mode(WIFI_STA);
      WiFi.disconnect(true);         // corta cualquier conexión previa
      vTaskDelay(100 / portTICK_PERIOD_MS); // 100 ms pero NO bloquea
      WiFi.begin(ssid[n_red], password[n_red]);

    }else if( tk1_n1 > 10 ){
      tk1_n1 = 0;
      n_red++; 
      if(n_red >= 3){n_red = 0;}
    }   
  }
  
  //Serial.print(WiFi.status()); Serial.print("  nivel:");
  //Serial.println(WiFi.RSSI());
  vTaskDelay(1000 / portTICK_PERIOD_MS);
}


//----------------------------------------------------------------------------------------
//DECLARACION DE FUNCIONES EXTERNAS (Exportadas) -----------------------------------------



//----------------------------------------------------------------------------------------
//DECLARACION DE TAREA FreeRTOS-----------------------------------------------------------
void task2_run(void *param) {
  task2_setup();
  for (;;) task2_loop();
}
