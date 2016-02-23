/*
File:       Serial.cc
Creation:   2009-05-22
Version:    9.12.26
Author:     Michael Gries   (c)2009
*/

/*
Version history:
2009-05-22 Erstellung
2009-12-26 Bug beseitigt wenn erstes Zeichen FF
2009-12-27 SMSdata hinzu
*/


void Serial_InitVRC(int baud)
{
  // Serial 0 (to PC or TC65Terminal)
  #define TC65T PC
  #define PC 0
  if(baud==1)
  {
      Serial_Init_IRQ(0,buffer0,100,100,SR_8BIT|SR_1STOP|SR_NO_PAR,SR_BD19200);
  }else
  {
      Serial_Init_IRQ(0,buffer0,100,100,SR_8BIT|SR_1STOP|SR_NO_PAR,SR_BD115200);
  }
  // Serial 1  (from iroVIT-VRC interface)
  #define VRC   1
  Serial_Init_IRQ(VRC,buffer1,100,100,SR_8BIT|SR_1STOP|SR_NO_PAR,SR_BD2400);
}

void Serial_HandleCommands(void)
{
  word w; w=Serial_ReadExt(PC); // read TC65T Command-buffer
  if(!(w==0x100))
  {
    switch(w)
    {
        //case 'h':
        //case 'H':
        case '?':   Debug_Help();  break;
        case 'd':   Debug_ModeDeactivate();  break;
        case 'D':   Debug_ModeActivateTest();  break;
        /*
        case 'a':   EEPROM_PrintAussentempMin();  break;
        case 'A':   EEPROM_PrintAussentempMax();  break;
        case 'b':
        case 'B':   EEPROM_PrintBetriebsstunden();  break;
        case 'c':   Clock_PrintTimestamp();  break;
        case 'i':   Debug_Info();  break;
        case 'k':   EEPROM_PrintKesseltempMin();  break;
        case 'K':   EEPROM_PrintKesseltempMax();  break;
        case 'w':   EEPROM_PrintWassertempMin();  break;
        case 'W':   EEPROM_PrintWassertempMax();  break;
        */
        case 't':   Debug_TraceModeDeactivate();  break;
        case 'T':   Debug_TraceModeActivateTest();  break;
        case '@':   Datagram_CSVdata();  break;
        case '~':   Datagram_SMSdata();  break;
        case ':':   Serial_Write(0,'.'); break;  //Heartbeat from/to TC65T
        /*
        case ESC:
        case TAB:   Serial_WriteNewLine(); break;
        case SP:    Serial_WriteMarkLine(); break;
        /*
        case 0x30:  Serial_Write(0,'0'); break;
        case 0x31:  Serial_Write(0,'1'); break;
        case 0x32:  Serial_Write(0,'2'); break;
        case 0x33:  Serial_Write(0,'3'); break;
        case 0x34:  Serial_Write(0,'4'); break;
        case 0x35:  Serial_Write(0,'5'); break;
        case 0x36:  Serial_Write(0,'6'); break;
        case 0x37:  Serial_Write(0,'7'); break;
        case 0x38:  Serial_Write(0,'8'); break;
        case 0x39:  Serial_Write(0,'9'); break;
        default:    Serial_Write(0,w);  // for test purposes only
        */
        default:    DebugCnt=0; TraceCnt=0; break;
    }
  }
}

void Serial_HandleVRCdata(void)
{
    char Text1[40];                             // Array deklariert
    char ausgabe[40];
    int sz;
    int inv; inv=1;
    word wsz; byte bsz;
    unsigned char value[5];
    int dCount;

    wsz=Serial_ReadExt(VRC);    // Puffer auslesen
    if(!(wsz==0x100))           //0x100 == Puffer leer
    {
      Ports_SetLED();
      bsz=wsz;
      datagram[pos++]=bsz;
      if((pos==1) && (bsz==0xFF))  // bekannter Übertragungsfehler
      {
        Serial_ErrorFF();
        Ports_ResetLED();
        pos=0;
      }
      //datagram[count]=wsz;
      message="#";
      //Str_Copy(datagram,message,STR_APPEND);
      //count=count+1;
      if(DebugMode)
      {
        Str_WriteWord(wsz,16,value,0,2);   //formatiert ausgeben
        Serial_WriteText(PC,value);
        Serial_Write(PC,' '); Serial_Write(0,' ');
        // Formatierung nach Datagram-Grenzen (Nr. 1-3,4,5-6,7-8
        if((pos==16)||(pos==31)||(pos==42)||(pos==57))
        {
            Serial_WriteNewLine();
        }
      } else
      {
        if(TraceMode)
        {
            Serial_Write(0,bsz);
        }
      }
      if((wsz==0x22 || wsz==0x23) && (pos>60))
      {
        Ports_ResetLED();
        if(DebugMode)
        {
            Serial_WriteNewLine();
            //wsz=sizeof(datagram)*SIZE;
            message="Anzahl Datagram-Bytes: ";
            Serial_WriteText(0,message);
            Serial_WriteInt(0,pos);
            Serial_WriteNewLine();
            AbsDelay(300);
            //clearDatagram();
            //setDatagram();
            //Serial_WriteText(0,datagram);
            //Datagram_Debug();
        }
        Datagram_Analyse();
        if(DebugMode)
        {
            Datagram_Print();
            AbsDelay(200);
            Serial_WriteMarkLine();
            Serial_WriteNewLine();
        }
        pos=0;
      }
    }   // end serial 1 read
}

void Serial_WriteHex(byte ser, word value)
{
    char sValue[10];
    Str_WriteWord(value,16,sValue,0,4);
    Serial_WriteText(ser,sValue);
}

void Serial_WriteInt(byte ser, word value)
{
    char sValue[10];
    Str_WriteWord(value,10,sValue,0,1);
    Serial_WriteText(ser,sValue);
}

void Serial_WriteNewLine(void)
{
    Serial_Write(0,LF); Serial_Write(0,CR);
}

void Serial_WriteMarkLine(void)
{
   #define TERMINALSIZE 80
   Serial_WriteNewLine();
   Clock_UpdateTimestamp();   // into global variable sTimestamp[]
   char cAuthor[40];  cAuthor=" ";
   Str_Copy(cAuthor,COPYRIGHT,STR_APPEND);
   Str_Copy(cAuthor,", ",STR_APPEND);
   Str_Copy(cAuthor,AUTHOR,STR_APPEND);
   Str_Copy(cAuthor," ",STR_APPEND);
   unsigned int a; a=Str_Len(cAuthor);
   char cVersion[20];  cVersion=" ";
   Str_Copy(cVersion,PRJ,STR_APPEND);
   Str_Copy(cVersion," ",STR_APPEND);
   Str_Copy(cVersion,VERSION,STR_APPEND);
   Str_Copy(cVersion," ---",STR_APPEND);
   unsigned int v; v=Str_Len(cVersion);
   message="--- ";
   Str_Copy(message,sTimestamp,STR_APPEND);
   unsigned int t; t=Str_Len(message);
   unsigned int f; f=TERMINALSIZE-t-v-a-3;
   char cLine[255]; Str_Fill(cLine,'-',f);
   Str_Copy(message,"---",STR_APPEND);
   Str_Copy(message,cAuthor,STR_APPEND);
   Str_Copy(message,cLine,STR_APPEND);
   Str_Copy(message,cVersion,STR_APPEND);
   Serial_WriteText(0,message);
   Serial_WriteNewLine();
}

void Serial_ErrorFF(void)
{
   Serial_WriteNewLine();
   Serial_WriteText(PC,"Bus Error 0xFF at ");
   Clock_UpdateTimestamp();   // into global variable sTimestamp[]
   Serial_WriteText(PC,sTimestamp);
   Serial_WriteNewLine();
    // Abfrage wieviel Zeichen empfangen wurden
   word cntBuffer;
   cntBuffer=Serial_IRQ_Info(VRC,RS232_FIFO_RECV);
        AbsDelay(100);
   Serial_WriteText(PC,"No of received characters: ");
   Serial_WriteInt(PC,cntBuffer);
   Serial_WriteNewLine();

   while(false)      // endlosschleife
   {
     Serial_Write(PC,'.');
     AbsDelay(60000);
   }
}
