void readEEPROM(u8 *ptr){//, int addStart){
	u8 i;
	for(i=0;i<8;i++){
		_eea = i;//+addStart;
		_mp1h=0x01;_mp1l=0x40;
		_iar1=RDEN;_iar1|=RD;
		while(_iar1&RD);
		_iar1=0;//disable
		*ptr++=_eed;//return
	}
}

void writeEEPROM(u8 *ptr){//, int addStart){
	u8 i;
	for(i=0;i<8;i++){
		_eea = i;//+addStart;
		_eed = *ptr++;
		_mp1h=0x01;_mp1l=0x40;
		_iar1=WREN; _iar1|=WR;
		while(_iar1 & WR);
		_iar1=0;//disable
	}	
}