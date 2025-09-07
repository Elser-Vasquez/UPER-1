#ifndef _GlobalDef_h_
#define _GlobalDef_h_

#include "Arduino.h"

// Incluir ArduinoJson con configuración específica para ESP32
#define ARDUINOJSON_NAMESPACE ArduinoJson
#define ARDUINOJSON_ENABLE_STD_STREAM 0
#define ARDUINOJSON_ENABLE_STD_STRING 0
#define ARDUINOJSON_ENABLE_PROGMEM 0

#include <ArduinoJson.h>
//----------------------------------------------------------------------------------------
//DECLARACION DE VARIABLES INTERNAS (NO MODIFICAR)----------------------------------------
extern char DEVICE_ID[32];



//----------------------------------------------------------------------------------------
//DECLARACION DE FUNCIONES INTERNAS (NO MODIFICAR)----------------------------------------



//----------------------------------------------------------------------------------------
//DECLARACION DE VARIABLES GLOBALES ------------------------------------------------------
extern bool flag1;           
extern bool flag2;
extern bool flag3;

extern char ssid[3][30];
extern char password[3][30];

extern StaticJsonDocument<256> json_rx;  //rx json


extern TaskHandle_t task1Handle;      // Handles de las tareas
extern TaskHandle_t task2Handle;
extern TaskHandle_t task3Handle;
extern TaskHandle_t task4Handle;
extern TaskHandle_t task5Handle;
extern TaskHandle_t task6Handle;

//----------------------------------------------------------------------------------------
//DECLARACION DE FUNCIONES GLOBALES-------------------------------------------------------
extern void msg( int N_pross, String Name_Function, String Action, String Sujeto, String Response);


#endif