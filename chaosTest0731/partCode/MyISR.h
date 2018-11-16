volatile u8	RxData;
volatile _Bool b_RX;
DEFINE_ISR(ISR_ExtINT0,0x04){
	u8 temp=0b00000001;
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
DEFINE_ISR(ISR_ExtINT1,0x08){
	if(getOpenIRState()){
		if(!getLockState()){
			while(getOpenIRState()){
				setBuzzerState(HIGH);
			}
			setBuzzerState(LOW);
		}else{
			LcdClearLINE2(0);
			setLockState(LOW);
		}
	}
}
/*
DEFINE_ISR(ISR_ExtINT2,0x30){
	if(!lockState){
		warning();
	}	
}*/