# Chiave_RFID_TPS
Sistema di accessi a 6 stanze tramite tag RFID.

L'accesso alla stanza è controllato da un lettore RFID RC522 ed un Arduino Uno R3 con Display LCD 16x2; il quale comunica con un server centrale tramite ethernet.

Nel server centrale è presente un interfaccia per la gestione centralizzata degli accessi.

Tutto il Sistema è protetto all'interno di un case stampato in 3D in ABS.

Nel programma di test (nessuna comunicazione con il server centrale) viene eseguita come prova la scansione di solamente due tag, uno affermativo e l'altro negativo.

Sul display LCD viene visualizzato "ACCESSO CONSENTITO" oppure "ACCESSO NEGATO".
