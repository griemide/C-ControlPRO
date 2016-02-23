
void AbsDelay               $opc(0x00)(word val);
void Port_DataDir           $opc(0x01)(byte port,byte val);
void Port_Write             $opc(0x02)(byte port,byte val);
byte Port_Read              $opc(0x03)(byte port);
#ifdef MEGA32
void Timer_T0CNT            $opc(0x04)(void);
byte Timer_T0GetCNT         $opc(0x05)(void);
#endif
word Timer_T1GetCNT         $opc(0x06)(void);
void Timer_T1CNT            $opc(0x07)(void);
void Timer_T1CNT_Int        $opc(0x08)(word limit);
void Timer_T0Start          $opc(0x09)(byte prescaler);
void Timer_T0Stop           $opc(0x0A)(void);
void Timer_T0FRQ            $opc(0x0B)(byte Period,byte PS);
void Timer_T0PWM            $opc(0x0C)(byte PW,byte PS);
void Timer_T0PW             $opc(0x0D)(byte PW);
void Timer_T1Start          $opc(0x0E)(byte prescaler);
void Timer_T1Stop           $opc(0x0F)(void);
void Timer_T1FRQ            $opc(0x10)(word Period,byte PS);
void Timer_T1FRQX           $opc(0x11)(word Period,word skew,byte PS);
void Timer_T1PWM            $opc(0x12)(word Period,word PW0,byte PS);
void Timer_T1PWA            $opc(0x13)(word PW0);
void Timer_T1PWMX           $opc(0x14)(word Period,word PW0,word PW1,byte PS);
void Timer_T1PWB            $opc(0x15)(word PW1);
void LCD_SubInit            $opc(0x16)(void);
word Key_Scan               $opc(0x17)(void);
void LCD_WriteRegister      $opc(0x18)(byte x,byte c);
byte LCD_TestBusy           $opc(0x19)(void);
word ADC_Read               $opc(0x1A)(void);
word ADC_ReadInt            $opc(0x1B)(void);
void ADC_Set                $opc(0x1C)(byte v_ref,byte channel);
void ADC_SetInt             $opc(0x1D)(byte v_ref,byte channel);
void ADC_StartInt           $opc(0x1E)(void);
void ADC_Disable            $opc(0x1F)(void);
void Msg_WriteChar          $opc(0x20)(char c);
void Msg_WriteInt           $opc(0x21)(int val);
void Msg_WriteWord          $opc(0x22)(word val);
void Msg_WriteHex           $opc(0x23)(word val);
void I2C_Init               $opc(0x24)(byte I2C_BR);
void I2C_Start              $opc(0x25)(void);
void I2C_Stop               $opc(0x26)(void);
void I2C_Write              $opc(0x27)(byte data);
byte I2C_Read_ACK           $opc(0x28)(void);
byte I2C_Read_NACK          $opc(0x29)(void);
byte I2C_Status             $opc(0x2A)(void);
void Port_DataDirBit        $opc(0x2B)(byte portbit,byte val);
void Port_WriteBit          $opc(0x2C)(byte portbit,byte val);
byte Port_ReadBit           $opc(0x2D)(byte portbit);
void Serial_Write           $opc(0x2E)(byte serport,byte val);
byte Serial_Read            $opc(0x2F)(byte serport);
void Serial_Init            $opc(0x30)(byte serport,byte par,word divider);
word Serial_ReadExt         $opc(0x31)(byte serport);
void Timer_Disable          $opc(0x32)(byte timer);
void Irq_SetVect            $opc(0x33)(byte irqnr,float vect);
byte Irq_GetCount           $opc(0x34)(byte irqnr);
void Thread_Start           $opc(0x35)(byte thread,float func);
void Thread_Kill            $opc(0x36)(byte thread);
void EEPROM_Write           $opc(0x37)(word pos,byte val);
byte EEPROM_Read            $opc(0x38)(word pos);
void Timer_T0Time           $opc(0x39)(byte Time, byte PS);
void Timer_T1Time           $opc(0x3A)(word Time, byte PS);
void Timer_T1PM             $opc(0x3B)(byte Mode, byte PS);
word Timer_T1GetPM          $opc(0x3C)(void);
byte AComp                  $opc(0x3D)(byte BG);
void Ext_IntEnable          $opc(0x3E)(byte IRQ,byte Mode);
void Ext_IntDisable         $opc(0x3F)(byte IRQ);
void Thread_Delay           $opc(0x40)(word delay);
void Thread_Lock            $opc(0x41)(byte lock);
void Thread_Wait            $opc(0x42)(byte Thread, byte signal);
void Thread_Resume          $opc(0x43)(byte thread);
void Thread_Signal          $opc(0x44)(byte signal);
void Thread_Cycles          $opc(0x45)(byte thread, word cycles);
#ifdef MEGA128
float sqrt                  $opc(0x46)(float val);
float floor                 $opc(0x47)(float val);
float ceil                  $opc(0x48)(float val);
float ldexp                 $opc(0x49)(float val,int expn);
float fabs                  $opc(0x4A)(float val);
float ln                    $opc(0x4B)(float val);
float log                   $opc(0x4C)(float val);
float sin                   $opc(0x4D)(float val);
float asin                  $opc(0x4E)(float val);
float cos                   $opc(0x4F)(float val);
float acos                  $opc(0x50)(float val);
float tan                   $opc(0x51)(float val);
float atan                  $opc(0x52)(float val);
float pow                   $opc(0x53)(float x,float y);
float exp                   $opc(0x54)(float val);
#endif
void Msg_WriteText          $opc(0x55)(char text[]);
void Serial_WriteText       $opc(0x56)(byte serport,char text[]);
void Str_WriteInt           $opc(0x57)(int n,char text[],word offset);
void Str_WriteFloat         $opc(0x58)(float n,byte decimal,char text[],word offset);
word Str_Len                $opc(0x59)(char text[]);
void Str_Copy               $opc(0x5A)(char dest[],char source[],word offset);
char Str_Comp               $opc(0x5B)(char str1[],char str2[]);
void Msg_WriteFloat         $opc(0x5C)(float val);
void Str_WriteWord          $opc(0x5D)(word n,byte base,char text[],word offset,byte minwidth);
word Thread_Info            $opc(0x5E)(byte info);
word Thread_MemFree         $opc(0x5F)(void);
void SPI_Disable            $opc(0x60)(void);
void Serial_Disable         $opc(0x61)(byte serport);
#ifdef MEGA128
word Timer_T3GetCNT         $opc(0x62)(void);
void Timer_T3CNT            $opc(0x63)(void);
void Timer_T3CNT_Int        $opc(0x64)(word limit);
void Timer_T3Start          $opc(0x65)(byte PS);
void Timer_T3Stop           $opc(0x66)(void);
void Timer_T3FRQ            $opc(0x67)(word Period,byte PS);
void Timer_T3FRQX           $opc(0x68)(word Period,word skew,byte PS);
void Timer_T3PWM            $opc(0x69)(word Period,word PW0,byte PS);
void Timer_T3PWA            $opc(0x6A)(word PW0);
void Timer_T3PWMX           $opc(0x6B)(word Period,word PW0,word PW1,byte PS);
void Timer_T3PWMY           $opc(0x6C)(word Period,word PW0,word PW1,word PW2,byte PS);
void Timer_T3PWB            $opc(0x6D)(word PW1);
void Timer_T3Time           $opc(0x6E)(word Time, byte PS);
void Timer_T3PM             $opc(0x6F)(byte Mode, byte PS);
word Timer_T3GetPM          $opc(0x70)(void);
void Timer_T1PWMY           $opc(0x71)(word Period,word PW0,word PW1,word PW2,byte PS);
#endif
word Timer_TickCount        $opc(0x72)(void);
void Serial_Init_IRQ        $opc(0x73)(byte serport,byte ramaddr[],byte recvfifolen,byte sendfifolen,byte par,word divider);
byte Serial_IRQ_Info        $opc(0x74)(byte serport,byte info);
word EEPROM_ReadWord        $opc(0x75)(word pos);
float EEPROM_ReadFloat      $opc(0x76)(word pos);
void EEPROM_WriteWord       $opc(0x77)(word pos,word val);
void EEPROM_WriteFloat      $opc(0x78)(word pos,float val);
byte OneWire_Reset          $opc(0x79)(byte pin);
void OneWire_Write          $opc(0x7A)(byte data);
byte OneWire_Read           $opc(0x7B)(void);
byte SPI_Read               $opc(0x7C)(void);
void SPI_Write              $opc(0x7D)(byte data);
void SPI_ReadBuf            $opc(0x7E)(byte buf[], byte length);
void SPI_WriteBuf           $opc(0x7F)(byte buf[], byte length);
void SPI_Enable             $opc(0x80)(byte ctrl);
#ifdef MEGA128
float round                 $opc(0x81)(float val);
#endif
void Sleep				 	$opc(0x82)(byte ctrl);
void Clock_SetTime		 	$opc(0x83)(byte hour, byte min, byte sec, char corr);
void Clock_SetDate		 	$opc(0x84)(byte day, byte mon, byte year);
byte Clock_GetVal		 	$opc(0x85)(byte indx);
void Port_Toggle		 	$opc(0x86)(byte port);
void Port_ToggleBit		 	$opc(0x87)(byte portbit);
byte DirAcc_Read	   	    $opc(0x88)(byte reg);
void DirAcc_Write		 	$opc(0x89)(byte reg, byte val);
void RC5_Init               $opc(0x8A)(byte	pin);
void RC5_Write              $opc(0x8B)(word data);
word RC5_Read               $opc(0x8C)(void);
void Servo_Set              $opc(0x8D)(byte portbit, word pos);
void Str_Printf             $opc(0x8E)(char str[], char format[], ...);
word Str_ReadNum            $opc(0x8F)(char str[], byte base);
int Str_ReadInt             $opc(0x90)(char str[]);
float Str_ReadFloat         $opc(0x91)(char str[]);
void Servo_Init             $opc(0x92)(byte servo_cnt, byte servo_interval, byte ramaddr[], byte timer);
// mathematische Definitionen
#define PI 3.1415926


// Interrupt Definitionen
#define INT_0         0
#define INT_1         1
#define INT_2         2
#define INT_TIM1CAPT  3
#define INT_TIM1CMPA  4
#define INT_TIM1CMPB  5
#define INT_TIM1OVF   6
#define INT_TIM0COMP  7
#define INT_TIM0OVF   8
#define INT_ANA_COMP  9
#define INT_ADC       10
#define INT_TIM2COMP  11
#define INT_TIM2OVF   12

#ifdef MEGA128
#define INT_3         13
#define INT_4         14
#define INT_5         15
#define INT_6         16
#define INT_7         17
#define INT_TIM3CAPT  18
#define INT_TIM3CMPA  19
#define INT_TIM3CMPB  20
#define INT_TIM3CMPC  21
#define INT_TIM3OVF   22
#endif

// Deklaration der ADC Referenzspannung (max. Eingangsspannung)
#define ADC_VREF_BG  0xC0               // 2,56V interne Referenzspannung
#define ADC_VREF_VCC 0x40               // 5V Referenzspannung
#define ADC_VREF_EXT 0x00               // externe Referenzspannung
                                        // an PAD3 /links neben PortB)
// Deklaration der ADC Kanäle
#define ADC0 0
#define ADC1 1
#define ADC2 2
#define ADC3 3
#define ADC4 4
#define ADC5 5
#define ADC6 6
#define ADC7 7

//differencial input, ADC2 = negativ input
//diff.input +/-9 bit resolution
//bit9=1 => result negativ (two's complement)
//ADC22... können zur Offsetmessung verwendet werden
//Verstärkung: x1, x10, x200
#define ADC22x10    0x0C
#define ADC23x10    0x0D
#define ADC22x200   0x0E
#define ADC23x200   0x0F
#define ADC20x1     0x18
#define ADC21x1     0x19
#define ADC22x1     0x1A
#define ADC23x1     0x1B
#define ADC24x1     0x1C
#define ADC25x1     0x1D


// Port Definitionen
#define PortA 0
#define PortB 1
#define PortC 2
#define PortD 3

#ifdef MEGA128
#define PortE 4
#define PortF 5
#define PortG 6
#endif


// Bit Rate fuer  I2C
#define I2C_100kHz   72
#define I2C_400kHz   12

// String Definitionen
#define STR_APPEND   0xffff


// serielle Schnittstelle
#define SR_5BIT   0x80
#define SR_6BIT   0x82
#define SR_7BIT   0x84
#define SR_8BIT   0x86

#define SR_1STOP  0x00
#define SR_2STOP  0x08

#define SR_NO_PAR     0x00
#define SR_EVEN_PAR   0x20
#define SR_ODD_PAR    0x30


// Baud Rate definitions Oszillatorfrequenz 14,7456MHz
#define SR_BD2400   383    // baudrate    2400bps
#define SR_BD4800   191    // baudrate    4800bps
#define SR_BD9600    95    // baudrate    9600bps
#define SR_BD14400   63    // baudrate   14400bps
#define SR_BD19200   47    // baudrate   19200bps
#define SR_BD28800   31    // baudrate   28800bps
#define SR_BDMIDI    0x8039// baudrate   31250bps MIDI
#define SR_BD38400   23    // baudrate   38400bps
#define SR_BD57600   15    // baudrate   57600bps
#define SR_BD76800   11    // baudrate   76800bps
#define SR_BD115200   7    // baudrate  115200bps
#define SR_BD230400   3    // baudrate  230400bps


// Deklaration der Timer Prescaler Variablen
// ueber den Timer Prescaler wird das Teilungsverhältnis (Oszillatorfrequenz/ps)
// festgelegt. (14,7456MHz/ps)
#define PS_1      1
#define PS_8      2
#define PS_64     3
#define PS_256    4
#define PS_1024   5


// Deklaration der Timer Prescaler Variablen
// ueber den Timer Prescaler wird das Teilungsverhältnis (Oszillatorfrequenz/ps)
// festgelegt. (14,7456MHz/ps)
#ifdef MEGA32
#define PS0_1      1
#define PS0_8      2
#define PS0_64     3
#define PS0_256    4
#define PS0_1024   5
#endif // MEGA32


// Deklaration der Timer Prescaler Variablen für Timer 0 beim MEGA128
// ueber den Timer Prescaler wird das Teilungsverhältnis (Oszillatorfrequenz/ps)
// festgelegt. (14,7456MHz/ps)
#ifdef MEGA128
#define PS0_1      1
#define PS0_8      2
#define PS0_32     3
#define PS0_64     4
#define PS0_128    5
#define PS0_256    6
#define PS0_1024   7
#endif // MEGA128

// Thread_Info  Deklarationen
#define TI_THREADNUM 0
#define TI_STACKSIZE 1
#define TI_CYCLES    2


// RS232 Definitionen
#define RS232_FIFO_RECV 0
#define RS232_FIFO_SEND 1


// Deklaration der I/O Variablen
// die PortPins werden von 0 bis 31 angesprochen (4 Ports a 8 Pins)
// Beispiele: 0=PortA.0, 9=PortB.1
#ifdef MEGA32
#define PORT_LED1 30
#define PORT_LED2 31
#endif


#ifdef MEGA128
//  Application Board PortG
//  LED1=PortG.3, LED2=PortG.4
//  alle ADCs können genutzt werden
#define PORT_LED1 51
#define PORT_LED2 52
#endif

#define PORT_ON    0
#define PORT_OFF   1
#define PORT_OUT   1
#define PORT_IN    0


#ifdef MEGA32
#define PORT_SW1 26
#define PORT_SW2 27
#endif

#ifdef MEGA128
#define PORT_SW1 36
#define PORT_SW2 38
#endif


// Clock
#define CLOCK_SEC  0
#define CLOCK_MIN  1
#define CLOCK_HOUR 2
#define CLOCK_DAY  3
#define CLOCK_MON  4
#define CLOCK_YEAR 5
#define CLOCK_TICK 6

