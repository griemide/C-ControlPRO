/*
File:       Clock.cc
Creation:   2009-05-24
Version:    9.5.24
Author:     Michael Gries   (c)2009
*/

// Interpreter Funktionen ab IDE 2.00 (14.05.2009):
// Clock_GetVal();
// Clock_SetDate();
// Clock_SetTime();


char sTimestamp[30];   // Format: "YYYY-MM-DD hh.mm.ss "


void Clock_InitVRC(void)
{   // 9.5.24
    Clock_SetDate(24,05,09);
    Clock_SetTime(21,34,55,0);
}

void Clock_UpdateTimestamp(void)
{
    byte Y; byte M; byte D;
    byte h; byte m; byte s;
    Y=Clock_GetVal(CLOCK_YEAR);
    M=Clock_GetVal(CLOCK_MON);
    D=Clock_GetVal(CLOCK_DAY);
    h=Clock_GetVal(CLOCK_HOUR);
    m=Clock_GetVal(CLOCK_MIN);
    s=Clock_GetVal(CLOCK_SEC);
    sTimestamp="no clock";
    Str_Printf(sTimestamp,"20%02d-%02d-%02d %02d:%02d:%02d ",Y,M,D,h,m,s);
}

void Clock_PrintTimestamp(void)
{
    Clock_UpdateTimestamp();   // into global variable sTimestamp[]
    Serial_WriteText(0,sTimestamp);
}

void Clock_SetDCF77(void)
{
    if(DCFstatus==3)
    {
      Clock_SetDate(Tag,Monat,Jahr);
      Clock_SetTime(Std,Min,Sek,0);
    }
}

