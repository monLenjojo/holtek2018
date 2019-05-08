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
	_BTstateC=1;
	_BTstatePU=1;
	if(_BTstate){
		return 1;
	}else{
		return 0;
	}
}
void setDTrueLightState(_Bool state){
	_dTrueLight=0;
	_dTrueLightC=0;
	_dTrueLightPU=1;
	if(state){
		_dTrueLight=1;
	}else{
		_dTrueLight=0;
	}
}

void setDFalseLightState(_Bool state){
	_dFalseLight=0;
	_dFalseLightC=0;
	_dFalseLightPU=1;
	if(state){
		_dFalseLight=1;
	}else{
		_dFalseLight=0;
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
	_buzzerRelayPU=1;
	if(_buzzerRelay){
		return 1;
	}else{
		return 0;	
	}
}

void setBuzzerState(_Bool state){
	_buzzerRelayC=0;
	_buzzerRelayPU=1;
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
