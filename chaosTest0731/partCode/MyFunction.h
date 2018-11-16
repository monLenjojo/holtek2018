
void UARTTxData(u8 data){	
	u8 temp=0b00000001;
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

volatile int switchCaseNum=1;
volatile _Bool getUmState;
volatile u8 key;
volatile union IEEE754 valBuffer, valUm, valX1n;
void getFormatKey(union IEEE754* formatUm,union IEEE754* formatX1n){
	if(!getUmState){
		switch(switchCaseNum){
			case 1:
				valBuffer.Byte.a=key;
				switchCaseNum=2;
				break;
			case 2:
				valBuffer.Byte.b=key;
				switchCaseNum=3;
				break;
			case 3:
				valBuffer.Byte.c=key;
				switchCaseNum=4;
				break;
			case 4:
				valBuffer.Byte.d=key;
				switchCaseNum=5;
				break;
			case 5:
				valBuffer.Byte.e=key;
				switchCaseNum=6;
				break;
			case 6:
				valBuffer.Byte.f=key;
				switchCaseNum=7;
				break;
			case 7:
				valBuffer.Byte.g=key;
				switchCaseNum=8;
				break;
			case 8:
				valBuffer.Byte.h=key;
				switchCaseNum=9;
				break;
			case 9:
				valBuffer.Byte.i=key;
				switchCaseNum=10;
				break;
			case 10:
				valBuffer.Byte.j=key;
				switchCaseNum=11;
				break;
			case 11:
				valBuffer.Byte.k=key;
				switchCaseNum=1;
				*formatUm = valBuffer;
				valBuffer.Val=0.00;
				getUmState=1;
				break;
		}
	}else{
		switch(switchCaseNum){
			case 1:
				valBuffer.Byte.a=key;
				switchCaseNum=2;
				break;
			case 2:
				valBuffer.Byte.b=key;
				switchCaseNum=3;
				break;
			case 3:
				valBuffer.Byte.c=key;
				switchCaseNum=4;
				break;
			case 4:
				valBuffer.Byte.d=key;
				switchCaseNum=5;
				break;
			case 5:
				valBuffer.Byte.e=key;
				switchCaseNum=6;
				break;
			case 6:
				valBuffer.Byte.f=key;
				switchCaseNum=7;
				break;
			case 7:
				valBuffer.Byte.g=key;
				switchCaseNum=8;
				break;
			case 8:
				valBuffer.Byte.h=key;
				switchCaseNum=9;
				break;
			case 9:
				valBuffer.Byte.i=key;
				switchCaseNum=10;
				break;
			case 10:
				valBuffer.Byte.j=key;
				switchCaseNum=11;
				break;
			case 11:
				valBuffer.Byte.k=key;
				switchCaseNum=1;
				*formatX1n = valBuffer;
				valBuffer.Val=0.00;
				getUmState=0;
				break;
		}
	}
}

_Bool getBluetoothState(){
	_BTstateC=0;
	_BTstatePU=0;
	if(_BTstate){
		return 1;
	}else{
		return 0;
	}
}

_Bool getOpenIRState(){
	_OpenIRStateC=1;
	_OpenIRStatePU=1;
	if(_OpenIRState){
		return 1;
	}else{
		return 0;
	}	
}

_Bool getBuzzerState(){
	_buzzerRelayC=0;
	_buzzerRelayPU=0;
	if(_buzzerRelay){
		return 1;
	}else{
		return 0;	
	}
}

void setBuzzerState(_Bool state){
	_buzzerRelayC=0;
	_buzzerRelayPU=0;
	if(state){
		_buzzerRelay=1;
	}else{
		_buzzerRelay=0;
	}
}

_Bool getLockState(){//password check
	_doorRelayC = 0;
	_doorRelayPU = 1;
	if(_doorRelay){
		return 1;
	}else{
		return 0;
	}
}

void setLockState(_Bool state){
	_doorRelayC = 0;
	_doorRelayPU = 1;
	if(state){
		_doorRelay = 1;
	}else{
		_doorRelay = 0;
	}	
}

volatile u8 keyBoard,readTimeVal;
u8 ScanKey(){
	u8 i,keyBoard=0;
	KeyPortC=0xF0; KeyPortPU=0xF0;			   		//IO規劃與提升身電阻致能
	KeyPort=0b11111110;					        	//Initial Scancode
	for(i=0;i<=2;i++){	
		if(!(KeyPort & 1<<4)) break;		     	//Check Column 0
		keyBoard++;
		if(!(KeyPort & 1<<5)) break;			   	//Check Column 1
		keyBoard++;
		if(!(KeyPort & 1<<6)) break;			  	//Check Column 2
		keyBoard++;
		if(!(KeyPort & 1<<7)) break;			  	//Check Column 3
		keyBoard++;
		KeyPort<<=1; KeyPort|=0b00000001;	   		//Scancode for Next Row
	}
	return keyBoard;	
}

int keyBoardBuffer[4]={0,0,0,0}, inputKeyBoardBuffer[4]={-1,-1,-1,-1}, keyBoardBufferPtr=0;
void intiKeyBoard(){
	keyBoardBufferPtr = 0;
	int i;
	for(i=0; i<=3; i++){
		inputKeyBoardBuffer[i] = -1;
	}
}

void inputKeyBoardFull(){
	int i; _Bool checkIn = 1;
	for(i=0; i<=3; i++){
		if(keyBoardBuffer[i] != inputKeyBoardBuffer[i]){
			checkIn &= 0;
			i=3;
		}
		if(i==3){
			if(!checkIn){
				intiKeyBoard();
				LcdClearLINE2(0);
			}else{
				LcdWriteString(LCD_LINE_2,0,"Lock Open");
				intiKeyBoard();
				setLockState(HIGH);	
			}
		}
	}
}

void putValtoBuffer(int inputVal){
	inputKeyBoardBuffer[keyBoardBufferPtr] = inputVal;
	keyBoardBufferPtr++;
	if(keyBoardBufferPtr==4){
		inputKeyBoardFull();
		delay(20);
	}
}

void clipValtoBuffer(){
	if(keyBoardBufferPtr!=0){
		keyBoardBufferPtr--;
		inputKeyBoardBuffer[keyBoardBufferPtr] = -1;
		LcdClearLINE2(keyBoardBufferPtr);
	}
}

void changePassword(){
	
}

void getKeyBoard(){
	if(getLockState()){
		LcdClearLINE2(0);
		setLockState(LOW);
	}
	switch(ScanKey()){
		case 0:
		//1
			LcdWriteString(LCD_LINE_2,keyBoardBufferPtr,"1");
			putValtoBuffer(1);
			break;
		case 1:
		//4
			LcdWriteString(LCD_LINE_2,keyBoardBufferPtr,"4");
			putValtoBuffer(4);
			break;
		case 2:
		//7
			LcdWriteString(LCD_LINE_2,keyBoardBufferPtr,"7");
			putValtoBuffer(7);
			break;
		case 3:
		//*
			LcdWriteString(LCD_LINE_2,keyBoardBufferPtr,"*");
			clipValtoBuffer();
			break;
		case 4:
		//2
			LcdWriteString(LCD_LINE_2,keyBoardBufferPtr,"2");
			putValtoBuffer(2);
			break;
		case 5:
		//5
			LcdWriteString(LCD_LINE_2,keyBoardBufferPtr,"5");
			putValtoBuffer(5);
			break;
		case 6:
		//8
			LcdWriteString(LCD_LINE_2,keyBoardBufferPtr,"8");
			putValtoBuffer(8);
			break;
		case 7:
		//0
			LcdWriteString(LCD_LINE_2,keyBoardBufferPtr,"0");
			putValtoBuffer(0);
			break;
		case 8:
		//3
			LcdWriteString(LCD_LINE_2,keyBoardBufferPtr,"3");
			putValtoBuffer(3);
			break;
		case 9:
		//6
			LcdWriteString(LCD_LINE_2,keyBoardBufferPtr,"6");
			putValtoBuffer(6);
			break;
		case 10:
		//9
			LcdWriteString(LCD_LINE_2,keyBoardBufferPtr,"9");
			putValtoBuffer(9);
			break;
		case 11:
		//#
			LcdWriteString(LCD_LINE_2,keyBoardBufferPtr,"#");
			changePassword();
			break;
	}delay(30);
}