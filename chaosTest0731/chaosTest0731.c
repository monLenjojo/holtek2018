// PROGRAM	: RGBV2.c								2018.0601
// FUNCTION	: RGB LED Simple Control By BT			By Steven
// Note: 兩組對接進行測試 (PA1(A)-->PA3(B),
//						   PA3(A)-->PA1(B),
//						   GND(A)-->GND(B))
#include "partCode/MyInclude.h"
#include "TryCode.h"
void main()
{
	//s16 R=0,G=0,B=0;
	_wdtc=0b10101111;								//關閉WDT
	_RXC=1;_RXPU=1;_int0eg1=1; _int0eg0=0; _int0e=1;					//INT0負源觸發
	_pec7=1;_pepu7=1;_int1s1=1;_int1s0=1;_pes3=0x00;_int1eg1=1;_int1eg0=0;_int1e=1; //INT1負源觸發,PA4轉到PE7
	_TX=1; _TXC=0;									//_TX為輸出模式(輸出Hi)	
	_tm0c0=0b00010000;								//For Bit Rate,fINT=fSYS
	_tm0c1=0b11000001;								//T/C, TM0A Match Clear
	/*
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
*/
 	_emi=1;    										//致能中斷
 	b_RX=0;  			
	_t1on=1; _t3on=1;
	key=0;
	valBuffer.Val=0.00;
	valUm.Val=0.00;
	valX1n.Val=0.00;
	getUmState=0;//intiChaos();
	//---------------------------------test
	setLockState(HIGH);delay(1000);
	setLockState(LOW);delay(1000);
	setBuzzerState(HIGH);
	//tryLikeConnectChaos();
	//tryGetIeee754();
	//GCC_HALT();
	//switchCaseNum=1;
	//--------------------------------------
	LcdInit();
	LcdWriteString(LCD_LINE_1,0,"Input password:");
	while(1){	
		_pf2=getBluetoothState();
		if(b_RX){
			key=RxData; b_RX=0;
			getFormatKey(&valUm, &valX1n);
			if(valUm.Val!=0.00 && valX1n.Val!=0.00){
				if(doMath(valUm.Val, valX1n.Val)){
					setLockState(HIGH);
				}
				valX1n.Val=0.00;
				valUm.Val=0.00;
			}
		}
		readTimeVal = ScanKey();
		if(readTimeVal!=12){
			getKeyBoard(readTimeVal);
		}
		/*else
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
		}*/
	}
}