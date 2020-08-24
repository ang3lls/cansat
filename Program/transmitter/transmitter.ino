/* CANSAT 2019 SENAI SP                       **
** VER:   1.03   data 20/09/2019              **                                
** Transmitter for CanSat datas               **
** CODE: Eike                                 */

#include <Adafruit_Sensor.h>  
#include <Adafruit_BMP280.h>  
#include <Wire.h>
#include <SPI.h>
#include <nRF24L01.h>         
#include <RF24.h>           

// CE CSN Pin config (NRF24L01)
#define CE_PIN 9  
#define CSN_PIN 8

// Barometric pressure and temperature sensor (BMP280)
Adafruit_BMP280 bmp; 

//transmission channel config
byte direccion[5] ={'s','p','t','n','k'};

// radio module (NRF24L01)
RF24 radio(CE_PIN, CSN_PIN);

// Array for datas
float dados[3];

void setup()
{
  radio.begin();
  Serial.begin(9600); 
  radio.openWritingPipe(direccion);
  Serial.println("Conectando bmp180....");  
  Wire.begin();
  
  if (!bmp.begin(0x76))
  { 
    Serial.println("Erro no Sensor BMP180 - Verifique as conexões");
    while(1);
  }   
  Serial.println("CLEARDATA");
  Serial.println("LABLE, Hora,Temperatura,Humidade,linha");
  delay(1000);
}
 
void loop()
{ 
  float Temperatura = bmp.readTemperature();
  float Pressao = bmp.readPressure();
  float Altitude = bmp.readAltitude();

  Serial.print("Pressão:\t"); 
  Serial.print(Pressao); 
  Serial.println(" Pa");
  Serial.print("Altitude:\t"); 
  Serial.print(Altitude);
  Serial.println(" m");  
  Serial.print("Temperatura:\t"); 
  Serial.print(Temperatura); 
  Serial.println(" *C");
  
  dados[0]= Pressao;
  dados[1]= Altitude;
  dados[2]= Temperatura;

  bool ok = radio.write(dados, sizeof(dados));
  
  if(ok)
  {
     Serial.println("-----------------------------------------");
     Serial.println("Dados enviados com sucesso!");
     Serial.println("-----------------------------------------"); 
  }
  else
  {
     Serial.println("-----------------------------------------");
     Serial.println("Dados não enviados ! Falha no transmissor");
     Serial.println("-----------------------------------------");
  }
  delay(1000);
}
