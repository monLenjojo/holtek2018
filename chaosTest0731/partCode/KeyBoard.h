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
void whenLockStateTrue(){
	LcdWriteString(LCD_LINE_2,0,"Lock Open");
	intiKeyBoard();
	setLockState(HIGH);
	setDFalseLightState(LOW);
	setDTrueLightState(HIGH);
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
				setDFalseLightState(HIGH);
				setDTrueLightState(LOW);
			}else{
				whenLockStateTrue();
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
//-----------------------------------------
int EEPROMBuffer[4]={-1,-1,-1,-1}, nullBuffer[4]={-1,-1,-1,-1}, where;
void putValtoEEPROMBuffer(int inputVal){
	if(where<=3){
		LcdWriteIntToChar(LCD_LINE_2,where,inputVal);
		EEPROMBuffer[where] = inputVal;
		where++;
		delay(20);
	}
}

void clipEEPROMBuffer(){
	if(where!=0){
		where--;
		EEPROMBuffer[where] = -1;
		LcdClearLINE2(where);
	}
}
int readEEPROMBuffer[4]={0,0,0,0},newInt[];
void setEEPROM(){
	_eea=0; writeEEPROM(EEPROMBuffer);
	LcdClearLINE2(0);
	LcdWriteString(LCD_LINE_2,0,"OK!");
	delay(1000);
	_eea=0; readEEPROM(keyBoardBuffer);
	LcdClearLINE1(0);
	LcdWriteString(LCD_LINE_1,0,"Input password:");
	LcdClearLINE2(0);
	
	//call set new key
	/*LcdClearLINE2(0);
	int p =0;
	for (p=0;p<4;p++){
		LcdWriteIntToChar(LCD_LINE_2,p,readEEPROMBuffer[p]);
	}*/
}

_Bool fullPassword;
void getEEPROM(u8 Val){
	switch(Val){
		case 0:
		//1
			putValtoEEPROMBuffer(1);
			break;
		case 1:
		//4
			putValtoEEPROMBuffer(4);
			break;
		case 2:
		//7
			putValtoEEPROMBuffer(7);
			break;
		case 3:
		//*
			clipEEPROMBuffer();
			break;
		case 4:
		//2
			putValtoEEPROMBuffer(2);
			break;
		case 5:
		//5
			putValtoEEPROMBuffer(5);
			break;
		case 6:
		//8
			putValtoEEPROMBuffer(8);
			break;
		case 7:
		//0
			putValtoEEPROMBuffer(0);
			break;
		case 8:
		//3
			putValtoEEPROMBuffer(3);
			break;
		case 9:
		//6
			putValtoEEPROMBuffer(6);
			break;
		case 10:
		//9
			putValtoEEPROMBuffer(9);
			break;
		case 11:
		//#
			//check input OK 
			fullPassword =0;
			break;
	}
	delay(30);	
}

void changePassword(){
	LcdWriteString(LCD_LINE_1,0,"Set New password");
	where=0;fullPassword=1;
	while(fullPassword){
		readTimeVal = ScanKey();
		if(readTimeVal!=12){
			getEEPROM(readTimeVal);
		}
	}
	if(where==4){
		setEEPROM();
	}
}

void getKeyBoard(u8 Val){
	if(getLockState()){
		LcdClearLINE2(0);
		setLockState(LOW);
	}
	setDFalseLightState(LOW);
	setDTrueLightState(LOW);
	switch(Val){
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
			//LcdWriteString(LCD_LINE_2,keyBoardBufferPtr,"*");
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
			//LcdWriteString(LCD_LINE_2,keyBoardBufferPtr,"#");
			changePassword();
			break;
	}delay(30);
}


