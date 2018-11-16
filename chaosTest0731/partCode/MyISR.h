volatile u8	RxData;
volatile _Bool b_RX;
DEFINE_ISR(ISR_ExtINT0,0x04){
	u8 temp=0b00000001;
	_tm0al=(BITC/2); _tm0ah=(BITC/2)>>8;			//0.5T
	_t0on=1;
	_t0af=0;
	RxData=0;
	while(!_t0af);									//����0.5T
	_tm0al=BITC; _tm0ah=BITC>>8;					//T
	_t0af=0;
	do 
	{	while(!_t0af);								//����1T�ɶ�
		_t0af=0;
		if(_RX==1) RxData|=temp;					//�^�����
		temp<<=1;									//RxData����
	} while (temp);									//�Ytemp����0�����U�@�줸
	b_RX=1;											//�]�w���������X��
	while(!_t0af);									//����1T�ɶ�
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