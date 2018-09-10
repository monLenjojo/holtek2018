// PROGRAM	: RGBV2.c								2018.0601
// FUNCTION	: RGB LED Simple Control By BT			By Steven
// Note: 兩組對接進行測試 (PA1(A)-->PA3(B),
//						   PA3(A)-->PA1(B),
//						   GND(A)-->GND(B))
#include <HT66F70A.h>
#include "MyType.H"
#define  KeyPort	_pg
#define  KeyPortC	_pgc
#define  KeyPortPU	_pgpu
#define	_TX			_pa1							//連接至藍芽RX (Yellow)
#define	_TXC		_pac1
#define	_RX			_pa3							//連接至藍芽TX (Blue)
#define	_RXC		_pac3
#define _Relay		_pd6
#define _RelayC		_pdc6
#define _RelayPU	_pdpu6
#define	fSYS		8000000	
#define	BaudRate	9600	
#define	BITC		(fSYS/BaudRate)					//Bit Interval Time Constant
void UARTTxData(u8);
void delay(u16);
double g1,g2,g3,g4,h1,h2,j1,j2,u1,u2,c1,c2,A,dx1,dx2,dx3,ax1,ax2,ax3,y1,y2,y3,y1n,y2n,y3n;
void chaosMath();
void doMath();
void intiChaos();
u8 ScanKey(void);
volatile u8	RxData; 
volatile _Bool b_RX;
int switchCaseNum;
struct SetIEEE754{
	unsigned s:1;
	u8 e;
	unsigned long m:23;
	};//32bit
struct sendFormatIEEE754{
	unsigned k:2;
	unsigned j:3;
	unsigned i:3;
	unsigned h:3;
	unsigned g:3;
	unsigned f:3;
	unsigned e:3;
	unsigned d:3;
	unsigned c:3;
	unsigned b:3;
	unsigned a:3;
	};//32bit
union IEEE754{
	//struct SetIEEE754 setByte;
	struct sendFormatIEEE754 Byte;
	u32 allBit;
	double Val;
};
volatile u8 key;
volatile union IEEE754 u1Val;
void main()
{
	s16 R=0,G=0,B=0;
	_wdtc=0b10101111;								//關閉WDT
	_RXC=1; _integ=0x02; _int0e=1;					//INT0負源觸發
	_TX=1; _TXC=0;									//_TX為輸出模式(輸出Hi)	
	_tm0c0=0b00010000;								//For Bit Rate,fINT=fSYS
	_tm0c1=0b11000001;								//T/C, TM0A Match Clear
	
	_tm1c0=0b00110000;								//fINT=fSYS/64,T1RP=000
	_tm1c1=0b10101000;								//PWM G, Act Hi,TM1RP Match Clear
	_tm1c2=0b10101000;								//PWM B, Act Hi,Edge Aligned
	_tm1al=0; _tm1ah=0;								//Initial 0 Duty(G)
	_tm1bl=0; _tm1bh=0;								//Initial 0 Duty(B)
	
	_tm3c0=0b00110000;								//fINT=fSYS/64,T3RP=000
	_tm3c1=0b10101000;								//PWM R, Act Hi,TM3RP for Period
	_tm3al=0; _tm3ah=0;								//Initial 0 Duty(R)

	_pcs3=0x10;										//Enable PC7 as TP1A (G)	
	_pcs0=0x10;										//Enable PC1 as TP1B (B)	
	_pds0=0x01;										//Enable Pd0 as TP3	 (R)

 	_emi=1;    										//致能中斷
 	b_RX=0;  			
	_t1on=1; _t3on=1;
	
	_RelayC = 0;
	_RelayPU = 0;
	_Relay = 0;
	
	intiChaos();
	volatile int doOnce = 0;
	//while(1){
		//doMath();
		//doOnce++;
		//if(x1n==y1n){
			_pd6 = 1;
			delay(1000);
			_pd6 = 0;
//			break;
		//}
	//}
	volatile union IEEE754 IEEE754Val, *ptr;
	volatile double *valPtr,Dval;
	ptr =& IEEE754Val;
	valPtr =& IEEE754Val;
/*	ptr->s = 0b0;
	ptr->e = 0b10000010;
	ptr->m = 0b10010000000000000000000;
*/
	IEEE754Val.allBit = 0b01000001010010000000000000000000;
	IEEE754Val.Byte.a = IEEE754Val.Byte.a|0x07;
	//unsigned long val = IEEE754Val;
	while(1)
	{	if(b_RX)
		{	key=RxData; b_RX=0;			
			_pd6 = 1;
			delay(1000);
			_pd6 = 0;
		//doMath();
			switch(switchCaseNum){
				case 1:
					u1Val.Byte.a|key;
					switchCaseNum++;
					break;
				case 2:
					u1Val.Byte.b|key;
					switchCaseNum++;
					break;
				case 3:
					u1Val.Byte.c|key;
					switchCaseNum++;
					break;
				case 4:
					u1Val.Byte.d|key;
					switchCaseNum++;
					break;
				case 5:
					u1Val.Byte.e|key;
					switchCaseNum++;
					break;
				case 6:
					u1Val.Byte.f|key;
					switchCaseNum++;
					break;
				case 7:
					u1Val.Byte.g|key;
					switchCaseNum++;
					break;
				case 8:
					u1Val.Byte.h|key;
					switchCaseNum++;
					break;
				case 9:
					u1Val.Byte.i|key;
					switchCaseNum++;
					break;
				case 10:
					u1Val.Byte.j|key;
					switchCaseNum++;
					break;
				case 11:
					u1Val.Byte.k|key;
					switchCaseNum=1;
					break;
			}
		}
		else
		{	key=ScanKey();
			if(key!=12) 
			{ 	UARTTxData(key);
				UARTTxData(IEEE754Val.Byte.a);
				UARTTxData(IEEE754Val.Byte.b);
				UARTTxData(IEEE754Val.Byte.c);
				UARTTxData(IEEE754Val.Byte.d);
				UARTTxData(IEEE754Val.Byte.e);
				UARTTxData(IEEE754Val.Byte.f);
				UARTTxData(IEEE754Val.Byte.g);
				UARTTxData(IEEE754Val.Byte.h);
				UARTTxData(IEEE754Val.Byte.i);
				UARTTxData(IEEE754Val.Byte.j);
				UARTTxData(IEEE754Val.Byte.k);
				delay(200);
			}

		}
	}
}
DEFINE_ISR(ISR_ExtINT0,0x04)
{	u8 temp=0b00000001;
	_tm0al=(BITC/2); _tm0ah=(BITC/2)>>8;			//0.5T
	_t0on=1;
	_t0af=0;
	RxData=0;
	while(!_t0af);									//等待0.5T
	_tm0al=BITC; _tm0ah=BITC>>8;					//T
	_t0af=0;
	do 
	{	while(!_t0af);								//等待1T時間
		_t0af=0;
		if(_RX==1) RxData|=temp;					//擷取資料
		temp<<=1;									//RxData左移
	} while (temp);									//若temp不為0接收下一位元
	b_RX=1;											//設定接收完成旗標
	while(!_t0af);									//等待1T時間
	_t0on=0;
	_int0f=0;
}
void UARTTxData(u8 data)
{	u8 temp=0b00000001;
	_tm0al=BITC; _tm0ah=BITC>>8;					//T
	_TX=0;											//起始位元
	_t0on=1;
	_t0af=0;
	while(!_t0af);									//等待T間
	_t0af=0;
	do 
	{	_TX=(data & temp)? 1 : 0 ;	  				//依資料位元設定腳位狀態
		while(!_t0af);								//等待T時間
		_t0af=0;
		temp<<=1;
	} while (temp);	
	_TX=1;											//結束位元
	while(!_t0af);
	_t0on=0;
}
u8 ScanKey(){
	u8 i,key=0;
	KeyPortC=0xF0; KeyPortPU=0xF0;			   		//IO規劃與提升身電阻致能
	KeyPort=0b11111110;					        	//Initial Scancode
	for(i=0;i<=2;i++)
	{	if(!(KeyPort & 1<<4)) break;		     	//Check Column 0
		key++;
		if(!(KeyPort & 1<<5)) break;			   	//Check Column 1
		key++;
		if(!(KeyPort & 1<<6)) break;			  	//Check Column 2
		key++;
		if(!(KeyPort & 1<<7)) break;			  	//Check Column 3
		key++;
		KeyPort<<=1; KeyPort|=0b00000001;	   		//Scancode for Next Row
	}
	return key;	
}
void delay(u16 del){	
	u16 i;
	for(i=0;i<del;i++) GCC_DELAY(2000);				//Delay del ms @fSYS=8MHz
}
void doMath(){
	chaosMath();	
}
void intiChaos(){
//	x1 = 0.5;
//	x2 = -0.3;
//	x3 = 0.4;
	y1 = -0.3;
	y2 = -0.1;
	y3 = 0.8;
	ax1=1;
	ax2=1;
	ax3=1;
	dx1=1;
	dx2=1;
	dx3=1;
	c1 = -0.5;
	c2 = 0.06;
	A = 0.1;
}
void chaosMath(double u1){
	g1 = - ( ax1 / (ax2 * ax2) );
	g2 = 2 * ax1 * dx2 / (ax2 * ax2);
	g3 = - 0.1 * ax1 / ax3;
	g4 = ax1 * ( 1.76 - (dx2 * dx2) /  (ax2 * ax2) + 0.1 * ax1 * dx3 / ax3 ) + dx1;
	
	h1 = ax2 / ax1;
	h2 = - ( ax2 * dx1 ) / ax1 + dx2;
	
	j1 = ax3 / ax2;
	j2 = - ( ax3 * dx2 )/ ax2 + dx3;

//	u1 = x2 * x2 * g1 + x2 * g2 + x3 * g3 + x1 * c1 * h1 + x2 * c2 * j1 - x1 * A - x2 * c1 * A - x3 * c2 * A;
//	x1n = g1 * x2 * x2 + g2 * x2 + g3 * x3 + g4;
//	x2n = h1 * x1 + h2;
//	x3n = j1 * x2 + j2;

	u2 = -(y2 * y2) * g1 - y2 * g2 - y3 * g3 - y1 * c1 * h1 - y2 * c2 * j1 + y1 * A + y2 * c1 * A + y3 * c2 * A;
	
	y1n = g1 * y2 * y2 + g2 * y2 + g3 * y3 + g4 + u1 + u2 ;//
	y2n = h1 * y1 + h2;
	y3n = j1 * y2 + j2;
	
//	x1 = x1n;
//	x2 = x2n;
//	x3 = x3n;
	y1 = y1n;
	y2 = y2n;
	y3 = y3n;
}