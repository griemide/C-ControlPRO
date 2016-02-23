/*
File:       Ports.cc
Creation:   2009-05-03
Version:    9.6.6
Author:     Michael Gries   (c)2009
*/

/*
Version history:
9.5.3   LED feature added
9.5.23  Mode feature added
9.6.6   pre-processor define statements added:
        concatenated: e.g. MODE -> PD5 -> 29(MEGA128)
*/

#define MODE PD5  // Mode (0=19k2 oder 1=115k2)
#define LED  PG3  // LED  (Datagram Empfang)

#ifdef MEGA128
  #define PD5 29  // Mode (0=19k2 oder 1=115k2)
  #define PG3 51  // LED  (Datagram Empfang)
#endif


void Ports_InitVRC (void)
{
    Port_DataDirBit(MODE,PORT_IN);   // Mode
    Port_WriteBit  (MODE,1);         // Mode (Pull-up aktivieren)
    Port_DataDirBit(LED,PORT_OUT);   // LED
}

byte Ports_GetMode(void)
{
    return Port_ReadBit(MODE);       // Betriebsart lesen
}

void Ports_SetLED(void)
{
    Port_WriteBit(LED,PORT_ON);     // LED an (active low)
}

void Ports_ResetLED(void)
{
    Port_WriteBit(LED,PORT_OFF);    // LED aus (active high)
}
