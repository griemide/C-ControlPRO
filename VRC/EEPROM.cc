/*
File:       EEPROM.cc
Creation:   2009-04-19
Version:    9.6.14
Author:     Michael Gries   (c)2009
*/

/*
Version history:
9.4.19  Betriebstunden added
9.5.22  Aussen-/Kesseltemperatur added
9.6.14  Warmwassertemperatur added
*/

// EEPROM: Datenspeicherung im internen EEPROM
// erforderliche Library: IntFunc_Lib.cc

// Globale Parameter
// Datenaufzeichnung alle 10 Sekunden
// *6[==min]*60[==h]*24[==d] = 8640 Datensätze pro Tag -> Speichergröße: word

#define adrBetriebsstunden  0x1000  // Datentyp float
#define adrAussentempMin    0x1010  // Datentyp float
#define adrAussentempMax    0x1020  // Datentyp float
#define adrWassertempMin    0x1030  // Datentyp float
#define adrWassertempMax    0x1040  // Datentyp float
#define adrKesseltempMin    0x1050  // Datentyp float
#define adrKesseltempMax    0x1060  // Datentyp float


word Datensatz;
float fBetriebsstunden; // max 65535[h] = 2730[D] = 91[M] = 7[Y]
float fAussentempMin;   // -40.0 ... +80.0 °C
float fAussentempMax;   // -40.0 ... +80.0 °C
float fWassertempMin;   // +10.0 ... +70.0 °C
float fWassertempMax;   // +10.0 ... +70.0 °C
float fKesseltempMin;   // +32.0 ... +95.0 °C
float fKesseltempMax;   // +32.0 ... +95.0 °C

void EEPROM_Init(void)
{
 //adrBetriebsstunden=0x1000;
 float fData;
 char sData[80];
 fData = EEPROM_GetBetriebsstunden();
 fData = fData/10;
 Str_WriteFloat(fData,1,sData,0);
 char sUnit[8]; sUnit = " [h]";
 Str_Copy(sData,sUnit,STR_APPEND);
 Debug_Println(adrBetriebsstunden,sData);
}

void EEPROM_Reset(void)
{
    EEPROM_SetBetriebsstunden(0.0);
    EEPROM_SetAussentempMin(0.0);
    EEPROM_SetAussentempMax(0.5);
    EEPROM_SetWassertempMin(0.0);
    EEPROM_SetWassertempMax(0.5);
    EEPROM_SetKesseltempMin(0.0);
    EEPROM_SetKesseltempMax(0.5);
}


void EEPROM_SetBetriebsstunden(float value)
{
    EEPROM_WriteFloat(adrBetriebsstunden,value);
}

float EEPROM_GetBetriebsstunden(void)
{
    fBetriebsstunden=EEPROM_ReadFloat(adrBetriebsstunden);
    return fBetriebsstunden;
}

void EEPROM_PrintBetriebsstunden(void)
{
    #define DIVIDER 60  // in minutes -> set in hours
    #define OFFSET 0.0
    float fData; fData = EEPROM_GetBetriebsstunden();
    fData = fData/DIVIDER+OFFSET;
    char sData[80]; sData="Betriebsstunden: ";
    Str_WriteFloat(fData,3,sData,STR_APPEND);
    char sUnit[8]; sUnit = " [h]";
    Str_Copy(sData,sUnit,STR_APPEND);
    //println(adrBetriebsstunden,sData);
    Debug_Send(adrBetriebsstunden,sData);
}

void EEPROM_SetAussentempMin(float value)
{
    EEPROM_WriteFloat(adrAussentempMin,value);
}

void EEPROM_SetAussentempMax(float value)
{
    EEPROM_WriteFloat(adrAussentempMax,value);
}

float EEPROM_GetAussentempMin(void)
{
    fAussentempMin=EEPROM_ReadFloat(adrAussentempMin);
    return fAussentempMin;
}

float EEPROM_GetAussentempMax(void)
{
    fAussentempMax=EEPROM_ReadFloat(adrAussentempMax);
    return fAussentempMax;
}

void EEPROM_PrintAussentempMin(void)
{
    float fData; fData = EEPROM_GetAussentempMin();
    char sData[30]; sData="AussentempMin: ";
    Str_WriteFloat(fData,1,sData,STR_APPEND);
    char sUnit[8]; sUnit = " [`C]";
    Str_Copy(sData,sUnit,STR_APPEND);
    //println(adrAussentempMin,sData);
    Debug_Send(adrAussentempMin,sData);
}

void EEPROM_PrintAussentempMax(void)
{
    float fData; fData = EEPROM_GetAussentempMax();
    char sData[30]; sData="AussentempMax: ";
    Str_WriteFloat(fData,1,sData,STR_APPEND);
    char sUnit[8]; sUnit = " [`C]";
    Str_Copy(sData,sUnit,STR_APPEND);
    //println(adrAussentempMax,sData);
    Debug_Send(adrAussentempMax,sData);
}

void EEPROM_SetWassertempMin(float value)
{
    EEPROM_WriteFloat(adrWassertempMin,value);
}

void EEPROM_SetWassertempMax(float value)
{
    EEPROM_WriteFloat(adrWassertempMax,value);
}

float EEPROM_GetWassertempMin(void)
{
    fWassertempMin=EEPROM_ReadFloat(adrWassertempMin);
    return fWassertempMin;
}

float EEPROM_GetWassertempMax(void)
{
    fWassertempMax=EEPROM_ReadFloat(adrWassertempMax);
    return fWassertempMax;
}

void EEPROM_PrintWassertempMin(void)
{
    float fData; fData = EEPROM_GetWassertempMin();
    char sData[20]; sData="WassertempMin: ";
    Str_WriteFloat(fData,1,sData,STR_APPEND);
    char sUnit[8]; sUnit = " [`C]";
    Str_Copy(sData,sUnit,STR_APPEND);
    //println(adrWassertempMin,sData);
    Debug_Send(adrWassertempMin,sData);
}

void EEPROM_PrintWassertempMax(void)
{
    float fData; fData = EEPROM_GetWassertempMax();
    char sData[20]; sData="WassertempMax: ";
    Str_WriteFloat(fData,1,sData,STR_APPEND);
    char sUnit[8]; sUnit = " [`C]";
    Str_Copy(sData,sUnit,STR_APPEND);
    //println(adrWassertempMax,sData);
    Debug_Send(adrWassertempMax,sData);
}

void EEPROM_SetKesseltempMin(float value)
{
    EEPROM_WriteFloat(adrKesseltempMin,value);
}

void EEPROM_SetKesseltempMax(float value)
{
    EEPROM_WriteFloat(adrKesseltempMax,value);
}

float EEPROM_GetKesseltempMin(void)
{
    fKesseltempMin=EEPROM_ReadFloat(adrKesseltempMin);
    return fKesseltempMin;
}

float EEPROM_GetKesseltempMax(void)
{
    fKesseltempMax=EEPROM_ReadFloat(adrKesseltempMax);
    return fKesseltempMax;
}

void EEPROM_PrintKesseltempMin(void)
{
    float fData; fData = EEPROM_GetKesseltempMin();
    char sData[20]; sData="KesseltempMin: ";
    Str_WriteFloat(fData,1,sData,STR_APPEND);
    char sUnit[8]; sUnit = " [`C]";
    Str_Copy(sData,sUnit,STR_APPEND);
    //println(adrKesseltempMin,sData);
    Debug_Send(adrKesseltempMin,sData);
}

void EEPROM_PrintKesseltempMax(void)
{
    float fData; fData = EEPROM_GetKesseltempMax();
    char sData[20]; sData="KesseltempMax: ";
    Str_WriteFloat(fData,1,sData,STR_APPEND);
    char sUnit[8]; sUnit = " [`C]";
    Str_Copy(sData,sUnit,STR_APPEND);
    //println(adrKesseltempMax,sData);
    Debug_Send(adrKesseltempMax,sData);
}


void EEPROM_WriteTimestamp(unsigned int adr)
{
    EEPROM_Write(adr+4+1,Jahr);
    EEPROM_Write(adr+4+2,Monat);
    EEPROM_Write(adr+4+3,Tag);
    EEPROM_Write(adr+4+4,Std);
    EEPROM_Write(adr+4+5,Min);
    EEPROM_Write(adr+4+6,Sek);
}