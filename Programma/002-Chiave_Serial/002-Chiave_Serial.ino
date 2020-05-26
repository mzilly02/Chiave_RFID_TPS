
/*
PINOUT:
RC522 MODULE    Uno/Nano    
SDA             D10
SCK             D13
MOSI            D11
MISO            D12
IRQ             N/A
GND             GND
RST             D9
3.3V            3.3V
*/
#include <SPI.h>
#include <RFID.h>
//Vengono definiti PIN del RFID reader
#define SDA_DIO 10 
#define RESET_DIO 9
#define delayRead 1000 //tempo attesa tra due letture consecutive

//vengono definite le variabili Stringa in cui vengono memorizzati i seriali dei tag RFID
String SerialIDRead, SerialID1, SerialID2;
 
//Viene creata una istanza della libreria RFID
RFID RC522(SDA_DIO, RESET_DIO); 
 
void setup()
{ 
  Serial.begin(9600);
  Serial.println("Inizializzazione");
  //Abilita SPI
  SPI.begin(); 
  //Inizializzazione RFID reader
  RC522.init();
  //Codici Seriali RFID di Tag1 e Tag2
  SerialID1 = String("");
  SerialID2 = String("");
  Serial.println("inizializzazione completata");
}
 
void loop()
{
  //variabile "i" per contatore codice tag
  byte i;
   
  //Se viene letta una tessera
  if (RC522.isCard())
  {
    //Viene letto il codice presente 
    RC522.readCardSerial();
    String SerialIDRead ="";
    Serial.println("Seriale RFID letto:");
     
    // Viene caricato il seriale della tessera all'interno di una Stringa
    for(i = 0; i <= 4; i++)
    {
      SerialIDRead+= String (RC522.serNum[i],HEX);
      SerialIDRead.toUpperCase();
    }

    //stampa su monitor seriale il codice esadecimale della tessera
    Serial.print(SerialIDRead);
    Serial.println();
    Serial.println();
    delay(delayRead);
  }
}
