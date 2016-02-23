/*
File:       DirectAccess.cc
Creation:   2009-12-26
Version:    9.12.26
Author:     Michael Gries   (c)2009
*/

/*
Interpreter Funktionen ab IDE 2.0:
byte DirAcc_Read(byte register);
void DirAcc_Write(byte register, byte val);

for register details see section
'Register Summary' in ATmega128_datasheet.pdf
*/

#define OSCCAL 0x6F

byte DirectAccess_Frequency(void)
{   // 9.12.26
    byte bReg;
    bReg = DirAcc_Read(OSCCAL);
    return(bReg);
}

