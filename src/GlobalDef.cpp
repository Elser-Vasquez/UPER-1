#include "GlobalDef.h"


//----------------------------------------------------------------------------------------
//DECLARACION PARA PROCESOS INTERNOS (NO MODIFICAR) --------------------------------------
char DEVICE_ID[32]; 


//----------------------------------------------------------------------------------------
//DECLARACION DE VARIABLES GLOBALES ------------------------------------------------------
bool flag1 = false;
bool flag2 = false;  
bool flag3 = false;   

char ssid[3][30]     = {"ONU PRUEBA", "evasquez", "RED-DETINY"};             //3 credenciales -> 0 codigo - 1-2 eeprom
char password[3][30] = {"12345678A", "123456789", "12345678"};

StaticJsonDocument<256> json_rx;     //json reservado para rx mqtt
//----------------------------------------------------------------------------------------
//DECLARACION DE FUNCIONES GLOBALES-------------------------------------------------------
void msg( int N_pross, String Name_Function, String Action, String Sujeto, String Response){
  String j1 = "(";
  String j2 = ")-->  ";
  String j3 = "  -->  ";
  String j4 = "  >>  ";
  String msg_str = j1 + N_pross + j2 + Name_Function + j3 + Action + j4 + Sujeto + j3 + Response ;
  Serial.println(msg_str);
}


//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
