/*
File:       Datagram.cc
Creation:   2009-05-24
Version:    10.3.7
Author:     Michael Gries   (c)2009
*/

/*
Version history:
9.5.24  Datagram analysis added
9.6.6   Char parameterInfo[] added -> Parameter interpretaion
9.6.14  X-Parameter added (veränderlicher unbekannter Parameter)
9.6.16  Wochentag encoding added
9.6.21  Wassertemp Min/Max added
9.12.13 bug fix negative temperature
9.12.27 Datagram_SMSdata() hinzu
10.3.7  Datagram_CSVdata() hinzu
*/


#define SIZE 67

#define posSTATUS   18       // Position Heizstatus
#define posDCF      21       // DCF77 Status
#define posSEK      22       // Sekunden (BCD)
#define posMIN      23       // Minute (BCD)
#define posSTD      24       // Stunde (BCD)
#define posWO       25       // Wochentag (0-6 = M0-S0)
#define posTAG      26       // Tag (BCD)
#define posMON      27       // Monat (BCD)
#define posJAH      28       // Jahr (BCD-zweistellig)
#define posAT       32       // Position Aussentemp
#define posWT       35       // Position Wassertemp
#define posKT       38       // Position Kesseltemp
#define posHK       47       // Position Heizkurve
#define posXPara    52       // Position unbekannter Parameter
#define posWB       64       // Position Winterbetrieb

byte datagram[SIZE];
char parameterInfo[60];
char datavalueInfo[60];
char SMSdata[162];
char SMSdata1[81];
char SMSdata2[81];
char CSVdata[200];
unsigned int pos;

word Status;
word Brenner; word BrennerLast; word BrennerDauer;
byte DCFstatus;
byte Sek;   byte Min;      byte Std;
byte Tag;   byte Monat;    byte Jahr;
byte Wochentag;  char WOT[3];
word ATemp; word ATempMin; word ATempMax;
word WTemp; word WTempMin; word WTempMax;
word KTemp; word KTempMin; word KTempMax;
word HKurve;
word Betriebsart;
word XPara;

void Datagram_Clear(void)
{
    for(pos=0;pos<SIZE;pos++) datagram[pos]=0;
}

void Datagram_Set(void)
{
    for(pos=0;pos<SIZE;pos++) datagram[pos]=0x23;  // '#'
}

void Datagram_Debug(void)
{
    word w; char s[5];
    for(pos=0;pos<SIZE;pos++)
    {
        w=datagram[pos];
        Str_WriteWord(w,16,s,0,2);
        Serial_WriteText(0,s);
        AbsDelay(10);   // wichtig: Verzögerung  TODO: tuning
    }
}

void Datagram_Analyse(void)
{
   Status=      Datagram_Word(posSTATUS);
   DCFstatus=   Datagram_Byte(posDCF);
   Sek=         Datagram_Byte(posSEK);
   Min=         Datagram_Byte(posMIN);
   Std=         Datagram_Byte(posSTD);
   Wochentag=   Datagram_Byte(posWO);
   Tag=         Datagram_Byte(posTAG);
   Monat=       Datagram_Byte(posMON);
   Jahr=        Datagram_Byte(posJAH);
   ATemp=       Datagram_Word(posAT);
   WTemp=       Datagram_Word(posWT);
   KTemp=       Datagram_Word(posKT);
   HKurve=      Datagram_Word(posHK);
   XPara=       Datagram_Word(posXPara);
   Betriebsart= Datagram_Word(posWB);
   Datagram_TestATemp();
   Datagram_TestKTemp();
   Datagram_TestWTemp();
   Datagram_TestBetriebsstunden();
 }

void Datagram_Print(void)
{
   AbsDelay(500);   // wichtig: Verzögerung  TODO: tuning

   message="\r\nVRC-Status : ";
   Serial_WriteText(0,message);
   Serial_WriteHex(0,Status);
   Datagram_InfoStatus();
   Serial_WriteText(0,parameterInfo);

   message="\r\nBrenndauer : ";
   Serial_WriteText(0,message);
   Serial_WriteHex(0,BrennerDauer);
   Datagram_InfoBrennerDauer();
   Serial_WriteText(0,parameterInfo);

   message="\r\nDCF-Status : ";
   Serial_WriteText(0,message);
   Serial_WriteHex(0,DCFstatus);
   Datagram_InfoDCF();
   Serial_WriteText(0,parameterInfo);

   AbsDelay(500);   // wichtig: Verzögerung  TODO: tuning

   message="\r\nDCF77 Zeit : ";
   Serial_WriteText(0,message);
   Datagram_InfoWochentag();
   Str_Printf(message,"20%02d-%02d-%02d %s %02d:%02d:%02d ",
                Jahr,Monat,Tag,WOT,Std,Min,Sek);
   Serial_WriteText(0,message);
   Clock_SetDCF77();

   message="\r\nAussentemp.: ";
   Serial_WriteText(0,message);
   Serial_WriteHex(0,ATemp);
   Datagram_InfoTemp(ATemp);
   Serial_WriteText(0,parameterInfo);

   message="\r\nWassertemp.: ";
   Serial_WriteText(0,message);
   Serial_WriteHex(0,WTemp);
   Datagram_InfoTemp(WTemp);
   Serial_WriteText(0,parameterInfo);

   message="\r\nKesseltemp.: ";
   Serial_WriteText(0,message);
   Serial_WriteHex(0,KTemp);
   Datagram_InfoTemp(KTemp);
   Serial_WriteText(0,parameterInfo);

   message="\r\nHeiz-Kurve : ";
   Serial_WriteText(0,message);
   Serial_WriteHex(0,HKurve);
   Datagram_InfoTemp(HKurve);
   Serial_WriteText(0,parameterInfo);

   message="\r\nX-Parameter: ";
   Serial_WriteText(0,message);
   Serial_WriteHex(0,XPara);
   //Datagram_InfoTemp(XPara);
   //Serial_WriteText(0,parameterInfo);

   AbsDelay(500);   // wichtig: Verzögerung  TODO: tuning

   message="\r\nBetriebsart: ";
   Serial_WriteText(0,message);
   Serial_WriteHex(0,Betriebsart);
   Datagram_InfoBetriebsart();
   Serial_WriteText(0,parameterInfo);
   Serial_WriteNewLine();
   Serial_WriteNewLine();
}

word Datagram_Word(unsigned int ind)
{
  word wh; word wl;
  wh=datagram[ind];  wh=wh<<8;
  wl=datagram[ind+1];
  return wh+wl;
}

byte Datagram_Byte(unsigned int ind)
{ // 9.6.7
  byte b;
  b=datagram[ind];
  return b;
}


void Datagram_InfoBetriebsart(void)
{ // 9.6.6
    parameterInfo=" ";
    switch(Betriebsart)
    {
        case 0x00:  parameterInfo=" = Sommerbetrieb"; break;
        case 0x01:  parameterInfo=" = Winterbetrieb"; break;
    }
}

void Datagram_InfoStatus(void)
{ // 9.6.6
    parameterInfo=" ";
    switch(Status)
    {
        case 0x0000:  parameterInfo=" = Bereitschaft";break;
        case 0x0001:  parameterInfo=" = Heizbetrieb"; break;
        case 0x0002:  parameterInfo=" = Warmwasser"; break;
        case 0x0400:  parameterInfo=" = Warmwasser (Pumpenachlauf)"; break;
        case 0x0402:  parameterInfo=" = Warmwasser (und Pumpe)"; break;
    }
}

void Datagram_InfoBrennerDauer(void)
{ // 9.6.6
    parameterInfo=" ";
    if(BrennerDauer)
    {
        parameterInfo=" = Brenner aktiv";
    } else
    {
        parameterInfo=" = Brenner aus";
    }
}

void Datagram_InfoDCF(void)
{ // 9.6.6
    parameterInfo=" ";
    switch(DCFstatus)
    {
        case 0x00:  parameterInfo=" = kein Empfang"; break;
        case 0x01:  parameterInfo=" = Empfang"; break;
        case 0x02:  parameterInfo=" = Synchonisierung"; break;
        case 0x03:  parameterInfo=" = Signal gueltig"; break;
    }
}

void Datagram_InfoWochentag(void)
{ // 9.6.16
    WOT="--";
    switch(Wochentag)
    {
        case 0x00:  WOT="Mo"; break;
        case 0x01:  WOT="Di"; break;
        case 0x02:  WOT="Mi"; break;
        case 0x03:  WOT="Do"; break;
        case 0x04:  WOT="Fr"; break;
        case 0x05:  WOT="Sa"; break;
        case 0x06:  WOT="So"; break;
    }
}

void Datagram_InfoTemp(word temp)
{ // 9.6.6
    #define DIVIDER 16
    #define OFFSET 0.0
    int g; g=temp;   // due to 16bit value signed
    float f; f=g;
    f=f/DIVIDER+OFFSET;
    Str_Printf(parameterInfo," (%03.1f'C)",f);
    Str_Printf(datavalueInfo,"%03.1f'C ",f);
    // note: char ''' (0x27) used instead of '°'
    // due to valid ascii range 0..128 and char of GSM 03.38 alphabet
}

void Datagram_TestATemp(void)
{ // 9.6.7
    #define DIVIDER 16
    #define OFFSET 0.0
    /*
    Serial_WriteHex(0,ATemp);
    Serial_WriteHex(0,ATempMin);
    Serial_WriteHex(0,ATempMax);
    */
    float f; f=ATemp; f=f/DIVIDER+OFFSET;
    if(ATemp<ATempMin)
    {
        EEPROM_SetAussentempMin(f);
        ATempMin=ATemp;
    }
    if(ATemp>ATempMax)
    {
        EEPROM_SetAussentempMax(f);
        ATempMax=ATemp;
    }
}

void Datagram_TestKTemp(void)
{ // 9.6.7
    #define DIVIDER 16
    #define OFFSET 0.0
    /*
    Serial_WriteHex(0,KTemp);
    Serial_WriteHex(0,KTempMin);
    Serial_WriteHex(0,KTempMax);
    */
    float f; f=KTemp; f=f/DIVIDER+OFFSET;
    if(KTemp<KTempMin)
    {
        EEPROM_SetKesseltempMin(f);
        KTempMin=KTemp;
    }
    if(KTemp>KTempMax)
    {
        EEPROM_SetKesseltempMax(f);
        KTempMax=KTemp;
    }
}


void Datagram_TestWTemp(void)
{ // 9.6.21
    #define DIVIDER 16
    #define OFFSET 0.0
    /*
    Serial_WriteHex(0,WTemp);
    Serial_WriteHex(0,WTempMin);
    Serial_WriteHex(0,WTempMax);
    */
    float f; f=WTemp; f=f/DIVIDER+OFFSET;
    if(WTemp<WTempMin)
    {
        EEPROM_SetWassertempMin(f);
        WTempMin=WTemp;
    }
    if(WTemp>WTempMax)
    {
        EEPROM_SetWassertempMax(f);
        WTempMax=WTemp;
    }
}

void Datagram_TestBetriebsstunden(void)
{ // 9.6.21
    #define DIVIDER 60 //hex value in seconds -> set to minutes
    #define OFFSET 0.0
    Brenner = Status & 0x000F;  // !=0 wenn aktiv
    if(!Brenner && BrennerLast)  // Wechsel auf Brenner aus
    {
        float f; f=BrennerDauer; f=f/DIVIDER+OFFSET;
        float b;
        b = EEPROM_GetBetriebsstunden();
        b =  b + f;
        EEPROM_SetBetriebsstunden(b);
        BrennerDauer=0;
    }
    if(Brenner && !BrennerLast)  // Wechsel auf Brenner an
    {
        BrennerDauer=0;
    }
    if (Brenner && BrennerLast)  // Brenner noch aktiv
    {
        BrennerDauer = BrennerDauer + 0x000A;
    }
    BrennerLast  = Brenner;
}

void Datagram_SMSdata(void)
{   // 9.12.27
    #define SMSMAXLENGTH 160
    SMSdata="Status Heizung (";
    Str_Copy(SMSdata,PRJ,STR_APPEND);
    Str_Copy(SMSdata,".",STR_APPEND);
    Str_Copy(SMSdata,VERSION,STR_APPEND);
    Str_Copy(SMSdata,")",STR_APPEND);
    Str_Copy(SMSdata,"\r\nAussentemperatur: ",STR_APPEND);
    Datagram_InfoTemp(ATemp);
    Str_Copy(SMSdata,datavalueInfo,STR_APPEND);
    Str_Copy(SMSdata,"\r\nWassertemperatur: ",STR_APPEND);
    Datagram_InfoTemp(WTemp);
    Str_Copy(SMSdata,datavalueInfo,STR_APPEND);
    Str_Copy(SMSdata,"\r\nKesseltemperatur: ",STR_APPEND);
    Datagram_InfoTemp(KTemp);
    Str_Copy(SMSdata,datavalueInfo,STR_APPEND);
    /*
    Str_Copy(SMSdata,"\r\nAussen: ",STR_APPEND);
    Datagram_InfoTemp(ATempMin);
    Str_Copy(SMSdata,datavalueInfo,STR_APPEND);
    Datagram_InfoTemp(ATemp);
    Str_Copy(SMSdata,datavalueInfo,STR_APPEND);
    Datagram_InfoTemp(ATempMax);
    Str_Copy(SMSdata,datavalueInfo,STR_APPEND);
    */
    word l; l=Str_Len(SMSdata);
    if(l>SMSMAXLENGTH)
    {
        Serial_WriteText(PC,"Maximum number of SMS characters exceeded");
    }else
    {
        /*
        Str_Printf(SMSdata1,"%20s",SMSdata);
        Str_Copy(SMSdata2,SMSdata,30);
        Serial_WriteText(PC,SMSdata1);
        AbsDelay(1000);   // wichtig: Verzögerung  TODO: tuning
        Serial_WriteText(PC,"\r\n");
        AbsDelay(1000);   // wichtig: Verzögerung  TODO: tuning
        Serial_WriteText(PC,SMSdata2);
        */
        Serial_WriteText(PC,SMSdata);
    }
}

void Datagram_CSVdata(void)
{   // 10.3.7
    CSVdata="\r\nCSV;";
    Str_Copy(CSVdata,PRJ,STR_APPEND);
    Str_Copy(CSVdata,";",STR_APPEND);
    Str_Copy(CSVdata,VERSION,STR_APPEND);
    Str_Copy(CSVdata,";",STR_APPEND);
    Str_Copy(CSVdata,LIBRARY,STR_APPEND);
    Str_Copy(CSVdata,";",STR_APPEND);
    Str_Copy(CSVdata,TARGET,STR_APPEND);
    Str_Copy(CSVdata,";",STR_APPEND);
    Str_Copy(CSVdata,sTimestamp,STR_APPEND);
    Str_Copy(CSVdata,";\r\n",STR_APPEND);
    Datagram_InfoTemp(ATemp);
    Str_Copy(CSVdata,datavalueInfo,STR_APPEND);
    Str_Copy(CSVdata,";",STR_APPEND);
    Datagram_InfoTemp(WTemp);
    Str_Copy(CSVdata,datavalueInfo,STR_APPEND);
    Str_Copy(CSVdata,";",STR_APPEND);
    Datagram_InfoTemp(KTemp);
    Str_Copy(CSVdata,datavalueInfo,STR_APPEND);
    Str_Copy(CSVdata,";\r\n",STR_APPEND);

    /*
    Datagram_InfoTemp(ATempMin);
    Str_Copy(CSVdata,datavalueInfo,STR_APPEND);
    Str_Copy(CSVdata,";",STR_APPEND);
    Datagram_InfoTemp(ATemp);
    Str_Copy(CSVdata,datavalueInfo,STR_APPEND);
    Str_Copy(CSVdata,";",STR_APPEND);
    Datagram_InfoTemp(ATempMax);
    Str_Copy(CSVdata,datavalueInfo,STR_APPEND);
    Str_Copy(CSVdata,";",STR_APPEND);
    */
    Serial_WriteText(PC,CSVdata);
    AbsDelay(100);   // wichtig: Verzögerung  TODO: tuning
 }
