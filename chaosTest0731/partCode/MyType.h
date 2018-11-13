typedef	unsigned char	u8;
typedef	char			s8;
typedef	unsigned short	u16;
typedef	short			s16;
typedef	unsigned long	u32;
typedef	long			s32;

struct SetIEEE754{
	unsigned long m:23;
	unsigned e:8;
	unsigned s:1;
	};//32bit
	
struct SendFormatIEEE754{
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
	struct SendFormatIEEE754 Byte;
	struct SetIEEE754 setIEEE754;
	unsigned long AllBit;
	double Val;
};