#include "partCode/MyInclude.h"
#include "TryCode.h"
void main()
{
	//s16 R=0,G=0,B=0;
	_wdtc=0b10101111;								//關閉WDT
	_RXC=1;_RXPU=1;_int0eg1=1; _int0eg0=0; _int0e=1;					//INT0負源觸發
	_pec7=1;_pepu7=1;//_int1s1=1;_int1s0=1;_pes3=0x00;_int1eg1=1;_int1eg0=0;_int1e=1; //INT1負源觸發,PA4轉到PE7
	_TX=1; _TXC=0;									//_TX為輸出模式(輸出Hi)	
	_tm0c0=0b00010000;								//For Bit Rate,fINT=fSYS
	_tm0c1=0b11000001;								//T/C, TM0A Match Clear
 	_emi=1;    										//致能中斷
 	b_RX=0;  			
	_t1on=1; _t3on=1;
	key=0;
	valBuffer.Val=0.00;
	valUm.Val=0.00;
	valX1n.Val=0.00;
	getUmState=0;
	LcdInit();
	LcdWriteString(LCD_LINE_1,0,"Input password:");
	_connectLight=0;
	_connectLightC=0;
	_connectLightPU=1;
	_dTrueLight=0;
	_dTrueLightC=0;
	_dTrueLightPU=1;
	_dFalseLight=0;
	_dFalseLightC=0;
	_dFalseLightPU=1;
//	delay(10000);
	while(1){
		_connectLight = getBluetoothState();//yellow
		if(getLockState() == LOW){
			if(_pe6 | _pe7){
				setBuzzerState(HIGH);	
			}else{
				setLockState(LOW);
				setBuzzerState(LOW);	
			}
		}else if(getLockState() == HIGH){
			if(getBuzzerState()){
				setBuzzerState(LOW);
			}
		}
		if(b_RX){
			key=RxData; b_RX=0;
			getFormatKey(&valUm, &valX1n);
			if(valUm.Val!=0.00 && valX1n.Val!=0.00){
				if(doMath(valUm.Val, valX1n.Val)){
					whenLockStateTrue();
				}
				valX1n.Val=0.00;
				valUm.Val=0.00;
			}
		}
		readTimeVal = ScanKey();
		if(readTimeVal!=12){
			getKeyBoard(readTimeVal);
		}
	}
}
