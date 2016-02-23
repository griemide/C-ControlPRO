/*
File:       VRC.cc
Creation:   2009-04-19
Version:    10.3.8  (change #DEFINE VERSION below)
Author:     Michael Gries   (c)2009
IDE-Lib:    2.01 (27.06.2009)
*/

/*
Version history:
2009-04-19 Erstellung
2009-06-14 X-Parameter hinzu
2009-12-13 Versionsangabe im Zeitstempel

*/

// Generic Preprozessor: http://nothingisreal.com/gpp/gpp.html

//------------------------------------------------------------------------------
// Hauptprogramm
//

/*
Verwendete Module (in config entsprechender Reihenfolge):
VRC.cc          Hauptprogramm
Serial.cc       2xRS232 (Kommandointerpreter von TC65 Terminal)
Datagram.cc     Datagramm-Anylsyse von iroVIT-Signal
Ports.cc        Def. benutzter Mega128 Prots der C-Control Pro
Clock.cc        internes Zeitmanagement
EEPROM.cc       internes EEProm handling
Debug.cc        Diagnoseprozeduren
DirectAccess.cc direkter Zugriff auf die Register des MEGA128
String_Lib.cc   (explicit), d.h. nicht als Interpreter Lib eingebunden
ascii.ch        (include Datei), ascii Zeichen
*/

/*
Signature Bytes
All Atmel microcontrollers have a three-byte signature code
which identifies the device. This code can be read in both serial and
parallel mode, also when the device is locked.

The three bytes reside in a separate address space.
For the ATmega128 the signature bytes are:
1. $000: $1E (indicates manufactured by Atmel)
2. $001: $97 (indicates 128KB Flash memory)
3. $002: $02 (indicates ATmega128 device when $001 is $97)
*/



#include ascii.ch   // ASCII Steuerzeichen

#define PRJ         "VRC"
#define PROJECT     "VRC-Monitor"
#define VERSION     "10.3.8"
#define AUTHOR      "Michael Gries"
#define COPYRIGHT   "(c)2009"
#define LIBRARY     "2.01 (27.06.2009)"
#ifdef MEGA128
  #define TARGET    "Atmel Mega128"
#else
  #define TARGET    "Atmel Mega32"
#endif



#define TRACE       false

char buffer0[255];
char buffer1[255];
char message[255];
char filename[128];
char function[128];


void main(void)
{
    int sz;
    int inv; inv=1;
    word wsz;
    byte bsz;
    word ws0;
    byte bs0;
    unsigned char value[5];
    int count;

    byte mode;
    /*
    Initialisierungen
    */
    Ports_InitVRC();
    Clock_InitVRC();
    DebugCnt=0; TraceCnt=0;
    DebugMode=0;     // Debug mode deactivated - press 'D' for activation
    TraceMode=0;     // default: Trace mode deactived if Heartbeat from TC65T
    //TraceMode=1;     // Trace mode activated - press 'T' for deactivation

    ATempMin=0x0555;
    ATempMax=0x0016;
    KTempMin=0x0666;
    KTempMax=0x0022;
    WTempMin=0x0777;
    WTempMax=0x0011;
    Brenner=0x0000; BrennerDauer=0x0000;

    mode = Ports_GetMode();
    int baud;  baud=mode;
    message="\r\nMode: ";
    Str_WriteInt(baud,message,STR_APPEND);
    Serial_WriteText(0,message);                  // Text über RS232 ausgeben
    char sline[8];
    filename=__FILE__;
    function=__FUNCTION__;
    char nachricht[100]; nachricht=PROJECT; sline=__LINE__;  //an dieser Stelle
    //debug(__LINE__,__FILE__,"Test");
    //EEPROM_Init();
    //resetEEPROM(); // auskommentieren nach Produktstionsstart
    Serial_InitVRC(baud);

    //prnBetriebsstunden();

    float bs;

    /*     Test EEProm
    bs = EEPROM_GetBetriebsstunden(); bs=bs+0.16;
    EEPROM_SetBetriebsstunden(bs);
    */
    Debug(sline,function,nachricht);

    char para2[10]; Str_WriteWord(SR_BD19200,10,para2,0,6);
    Str_Copy(nachricht,para2,0); sline=__LINE__;
    Debug(sline,function,nachricht);

    /*
    message="\r\nWait 2 seconds ...\r\n";
    Serial_WriteText(0,message); // Text über RS232 ausgeben
    AbsDelay(1000);                 // 1 Sek. Wartezeit

    // Abfrage wieviel Zeichen empfangen wurden
    count=Serial_IRQ_Info(0,RS232_FIFO_RECV);

    // Die Anzahl der Zeichen wird als Meldung ausgegeben
    Msg_WriteWord(count);
    Serial_WriteHex(0,count);
    message=" Zeichen im IRQ-Modus empfangen\r\n\n";
    Msg_WriteText(message);
    Serial_WriteText(0,message);
    */

    Debug_Info();
    AbsDelay(1000);                 // 1 Sek. Wartezeit
    Debug_ModeDeactivate();
    Debug_TraceModeDeactivate();

    while(true)   // Endlosschleife
    {
        Serial_HandleVRCdata();    // periodische Daten von der iroVIT-Anlage

        Serial_HandleCommands();   // Statusabfragen vom PC oder TC65T

    } // end while
}

