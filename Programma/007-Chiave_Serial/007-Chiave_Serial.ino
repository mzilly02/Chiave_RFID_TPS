
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
#define delayLed 2000 //tempo accensione led stato
#define delayDoor 10000 //tempo di attivazione rele' sblocco porta
#define PinPass 2
#define PinDenied 3
#define PinDoor 4
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
  SerialID1 = String("365DB22DF4");
  SerialID2 = String("4B9F192BE6");
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
    //Serial.println("Seriale RFID letto:");
     
    // Viene caricato il seriale della tessera all'interno di una Stringa
    for(i = 0; i <= 4; i++)
    {
      SerialIDRead+= String (RC522.serNum[i],HEX);
      SerialIDRead.toUpperCase();
    }

    delay(delayRead);

    //Controllo se il seriale letto e' uguale a uno dei due seriali autorizzati
    if (SerialIDRead.equals(SerialID1)){
      RFID_Pass();
    }
    if(SerialIDRead.equals(SerialID2)){
      RFID_Denied();
    }
  }
}

//funzione che sblocca la porta in caso di tessera autorizzata
void RFID_Pass(){
  Serial.print("ACCESSO CONSENTITO");
  digitalWrite(PinPass, HIGH);
  digitalWrite(PinDoor, HIGH);
  delay(delayDoor);
  digitalWrite(PinPass, LOW);
  digitalWrite(PinDoor, LOW);
  Serial.println();
}

//funzione che notifica in caso di tessera non autorizzata
void RFID_Denied(){
  Serial.print("ACCESSO NEGATO");
  digitalWrite(PinDenied, HIGH);
  delay (delayLed);
  digitalWrite(PinDenied, LOW);
  Serial.println();
}
