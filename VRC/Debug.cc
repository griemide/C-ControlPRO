/*
File:       Debug.cc
Creation:   2009-04-19
Version:    9.12.26
Author:     Michael Gries   (c)2009
*/

/*
Version history:
2009-04-19 Erstellung
2009-05-21 Debug_help() hinzu
2009-12-26 Debug_info() hinzu
*/



#ifdef MEGA128
    #pragma Warning "Counter Funktionen nicht bei Timer0 und Mega128"
#endif

//#ifdef __DEBUG__
#pragma Message __DATE__
#pragma Message __TIME__

int DebugCnt;
int DebugMode;
int TraceCnt;
int TraceMode;

void Debug_ModeActivateTest(void)
{
    if(++DebugCnt > 2)
    {
        Debug_ModeActivate(); DebugCnt=0;
    }
}

void Debug_ModeActivate(void)
{
    DebugMode=1;
    message="\r\nDebug mode activated ! - for deactivation press 'd'\r\n";
    Serial_WriteText(0,message);
}

void Debug_ModeDeactivate(void)
{
    message="\r\nDebug mode deactivated ! - for activation press 'DDD'\r\n";
    Serial_WriteText(0,message);
    DebugMode=0;
}

void Debug_TraceModeActivateTest(void)
{
    if(++TraceCnt > 2)
    {
        Debug_TraceModeActivate(); TraceCnt=0;
    }
}

void Debug_TraceModeActivate(void)
{
    TraceMode=1;
    message="\r\nTrace mode activated ! - for deactivation press 't'\r\n";
    Serial_WriteText(0,message);
}

void Debug_TraceModeDeactivate(void)
{
    message="\r\nTrace mode deactivated ! - for activation press 'TTT'\r\n";
    Serial_WriteText(0,message);
    TraceMode=0;
}

void Debug(char sLine[], char sFunction[], char sMessage[])
{
  char txt[81];
  //Str_Fill(txt,' ',80);
  Str_Copy(txt,sLine,0);
  AbsDelay(1000);
  Msg_WriteText(txt);  // Zeilennummer ausgeben
  Msg_WriteChar('-');
  //Str_Copy(txt,sFunction,STR_APPEND);
  Str_Copy(txt,sFunction,0);
  Msg_WriteText(txt);  // Funktionsnamenausgeben
  Msg_WriteChar(':'); Msg_WriteChar(' ');
  //Str_Copy(txt,sMessage,12);
  Str_Copy(txt,sMessage,0);
  Msg_WriteText(txt);  // Nachricht ausgeben
  Msg_WriteChar(13);   // LF
  AbsDelay(1000);
}

void Debug_Print(word adr, byte data)
{
    Msg_WriteHex(adr);              // Ausgabe der Adresse
    Msg_WriteChar(':');             // Ausgabe: :
    Msg_WriteHex(data);             // Ausgabe des Adressinhaltes
    Msg_WriteChar(0x20);            // Ausgabe: Leerzeichen
}

void Debug_Println(word adr, char data[])
{
    char mem[15]; mem="EEPROM-0x";
    Msg_WriteText(mem);             // Ausgabe des Adressinhaltes
    Msg_WriteHex(adr);              // Ausgabe der Adresse
    Msg_WriteChar(':');             // Ausgabe: :
    Msg_WriteChar(' ');            // CR
    Msg_WriteText(data);             // Ausgabe des Adressinhaltes
    Msg_WriteChar(0x20);            // Ausgabe: Leerzeichen
    Msg_WriteChar('\r');            // CR
    Msg_WriteChar('\n');            // LF
}

void Debug_Send(word adr, char data[])
{
    Serial_Write(0,CR);            // CR
    Serial_Write(0,LF);            // LF
    char mem[15]; mem="EEPROM-0x";
    Serial_WriteText(0,mem);             // Ausgabe des Adressinhaltes
    Serial_WriteHex(0,adr);              // Ausgabe der Adresse
    Serial_Write(0,':');             // Ausgabe: :
    Serial_Write(0,' ');            // CR
    Serial_WriteText(0,data);             // Ausgabe des Adressinhaltes
    Serial_Write(0,0x20);            // Ausgabe: Leerzeichen
    //Serial_Write(0,'\r');            // CR
}

void Debug_Help(void)
{
   Serial_WriteNewLine();
   message="VRC-Monitor Helpmenue \r\n";
   Serial_WriteText(0,message);
   AbsDelay(100);   // wichtig: Verzögerung  TODO: tuning
   message="?   - this menue \r\n";
   Serial_WriteText(0,message);
   AbsDelay(100);   // wichtig: Verzögerung  TODO: tuning
   message="i   - program info \r\n";
   Serial_WriteText(0,message);
   AbsDelay(100);   // wichtig: Verzögerung  TODO: tuning
   message=":   - heartbeat stimulation (returns '.') \r\n";
   Serial_WriteText(0,message);
   AbsDelay(100);   // wichtig: Verzögerung  TODO: tuning
   message="DDD - debug mode activation \r\n";
   Serial_WriteText(0,message);
   AbsDelay(100);   // wichtig: Verzögerung  TODO: tuning
   message="d   - debug mode deactivation (default)\r\n";
   Serial_WriteText(0,message);
   AbsDelay(100);   // wichtig: Verzögerung  TODO: tuning
   message="TTT - trace mode activation \r\n";
   Serial_WriteText(0,message);
   AbsDelay(100);   // wichtig: Verzögerung  TODO: tuning
   message="t   - trace mode deactivation (default)\r\n";
   Serial_WriteText(0,message);
   AbsDelay(100);   // wichtig: Verzögerung  TODO: tuning
   message="a   - Aussentemperatur min \r\n";
   Serial_WriteText(0,message);
   message="A   - Aussentemperatur max \r\n";
   Serial_WriteText(0,message);
   AbsDelay(100);   // wichtig: Verzögerung  TODO: tuning
   message="k   - Kesseltemperatur min \r\n";
   Serial_WriteText(0,message);
   message="K   - Kesseltemperatur max \r\n";
   Serial_WriteText(0,message);
   AbsDelay(100);   // wichtig: Verzögerung  TODO: tuning
   message="w   - Wassertemperatur min \r\n";
   Serial_WriteText(0,message);
   message="W   - Wassertemperatur max \r\n";
   Serial_WriteText(0,message);
   AbsDelay(100);   // wichtig: Verzögerung  TODO: tuning
   message="b   - Betriebsstunden \r\n";
   Serial_WriteText(0,message);
   Serial_WriteNewLine();
}


void Debug_Info(void)
{  //9.12.26
   Serial_WriteNewLine();
   Serial_WriteText(PC,PROJECT); Serial_WriteText(PC," version: ");
   Serial_WriteText(PC,VERSION); Serial_WriteText(PC,CRLF);
        AbsDelay(100);   // wichtig: Verzögerung  TODO: tuning
   Serial_WriteText(PC,"Compilation: "); Serial_WriteText(PC,__DATE__);
   Serial_WriteText(PC,"_");
   Serial_WriteText(PC,__TIME__); Serial_WriteText(PC,CRLF);
        AbsDelay(100);   // wichtig: Verzögerung  TODO: tuning
   Serial_WriteText(PC,"Directory: ");
   Serial_WriteText(PC,filename); Serial_WriteText(PC,CRLF);
        AbsDelay(100);   // wichtig: Verzögerung  TODO: tuning
   Serial_WriteText(PC,"Library: ");
   Serial_WriteText(PC,LIBRARY); Serial_WriteText(PC,CRLF);
        AbsDelay(100);   // wichtig: Verzögerung  TODO: tuning
   Serial_WriteText(PC,"Target: ");
   Serial_WriteText(PC,TARGET); Serial_WriteText(PC,CRLF);
        AbsDelay(100);   // wichtig: Verzögerung  TODO: tuning
   byte bFreq;
   bFreq=DirectAccess_Frequency();
    //MEGA128   14,7456MHz
    #define OSC 14.7456
   char cValue[20];
   Str_Printf(cValue,"%2.4f MHz\r\n",OSC);
   Serial_WriteText(PC,"Frequency: "); Serial_WriteText(PC,cValue);
   Serial_WriteNewLine();
        AbsDelay(100);   // wichtig: Verzögerung  TODO: tuning
   Serial_WriteText(PC,COPYRIGHT); Serial_WriteText(PC,", ");
   Serial_WriteText(PC,AUTHOR); Serial_WriteText(PC,CRLF);
}


