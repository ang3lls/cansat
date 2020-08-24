/* CANSAT 2019 SENAI SP                       **
** VER:   1.03   data 20/09/2019              **                                   **
** Receiver for CanSat datas                  **
** CODE: Eike                                 */

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
 
// CE CSN Pin config (NRF24L01)
#define CE_PIN 9
#define CSN_PIN 8
 
//transmission channel config
byte direccion[5] ={'s','p','t','n','k'}; 

// radio module (NRF24L01)
RF24 radio(CE_PIN, CSN_PIN);

// Array for datas
float dados[5];
int linha = 0;
int tent = 0;
int med = 0;
int aux = 0;
int medLinha = 1;

void setup()
{
  radio.begin();
  Serial.begin(9600);
  Serial.println("CLEARDATA");
  Serial.println("LABEL,Hora,Linha,Pressao(PA),Altitude-mar(m),Temperatura(*C),Altitude(m)");
  Serial.println("ROW,SET,4");
  radio.openReadingPipe(1, direccion);
  radio.startListening();
}
 
void loop() 
{ 
  if ( radio.available() )
  {    
    radio.read(dados,sizeof(dados));
    linha++;
    med++;
    if(aux==0)
  {
    Serial.print("==== Mediação N°");
    Serial.print(medLinha);
    Serial.print(" ====");
    Serial.println("");
    aux=1;
  }
    Serial.print("DATA,TIME,");
    Serial.print(med);
    Serial.print(",");
    Serial.print(dados[0]);
    Serial.print(","); 
    Serial.print(dados[1]);
    Serial.print(",");
    Serial.print(dados[2]);
    tent=0;
 }
 else
 {
    Serial.print("Falha na transmissão: tentativa n°");
    tent++;
    Serial.print(tent);
    Serial.println("");
 }

 if(linha == 90)
 {
    linha=0;
    Serial.println("");
    Serial.println("");
    aux=0;
    medLinha++;
 }
 delay(1000);
}
