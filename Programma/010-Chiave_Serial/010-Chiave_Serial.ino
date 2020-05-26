#include <SPI.h>
#include <RFID.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//Vengono definiti PIN del RFID reader
#define SDA_DIO 10 
#define RESET_DIO 9
#define delayLed 5000 //tempo accensione led stato
#define delayDoor 10000 //tempo di attivazione rele' sblocco porta
#define PinPass 2
#define PinDenied 3
#define PinDoor 4

LiquidCrystal_I2C lcd(0x3F,16,2);

//vengono definite le variabili Stringa in cui vengono memorizzati i seriali dei tag RFID
String SerialIDRead, SerialID1, SerialID2;
 
//Viene creata una istanza della libreria RFID
RFID RC522(SDA_DIO, RESET_DIO); 
 
void setup()
{
  lcd.init();
  Wire.begin();
  Serial.begin(9600);
  Serial.println("Inizializzazione");
  //Abilita SPI
  SPI.begin(); 
  //Inizializzazione RFID reader
  RC522.init();
  //impostazione Pin sblocco porta e LED stato come uscite
  pinMode (PinPass, OUTPUT);
  pinMode (PinDenied, OUTPUT);
  pinMode (PinDoor, OUTPUT);
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
     
    // Viene caricato il seriale della tessera all'interno di una Stringa
    for(i = 0; i <= 4; i++)
    {
      SerialIDRead+= String (RC522.serNum[i],HEX);
      SerialIDRead.toUpperCase();
    }

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
  lcd.backlight();
  lcd.setCursor(5, 0);
  lcd.print("ACCESSO");
  lcd.setCursor(3, 1);
  lcd.print("CONSENTITO");
  digitalWrite(PinPass, HIGH);
  digitalWrite(PinDoor, HIGH);
  delay(delayDoor);
  digitalWrite(PinPass, LOW);
  digitalWrite(PinDoor, LOW);
  lcd.noBacklight();
  lcd.clear();
}

//funzione che notifica in caso di tessera non autorizzata
void RFID_Denied(){
  lcd.backlight();
  lcd.setCursor(5, 0);
  lcd.print("ACCESSO");
  lcd.setCursor(5, 1);
  lcd.print("NEGATO");
  digitalWrite(PinDenied, HIGH);
  delay (delayLed);
  digitalWrite(PinDenied, LOW);
  lcd.noBacklight();
  lcd.clear();
}
