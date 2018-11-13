volatile union IEEE754 IEEE754Val, *ptr;
volatile double *valPtr,Dval;

void tryGetIeee754(){
		ptr =& IEEE754Val;
		valPtr =& IEEE754Val;
		/*ptr->setIEEE754.s = 0b0;
		ptr->setIEEE754.e = 0b10000010;
		ptr->setIEEE754.m = 0b10010000000000000000000;
	*/
		IEEE754Val.AllBit = 0b01000001010010000000000000000000;
		/*IEEE754Val.Byte.a = IEEE754Val.Byte.a|0x07;
		*/
		//unsigned long val = IEEE754Val;
}
//-------
volatile int tryDoOnce = 0;
double x1,x2,x3,x1n,x2n,x3n,u1;
void tryExecuteChaosAllInOne(){
	x1 = 0.5;
	x2 = -0.3;
	x3 = 0.4;
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
	while(1){
		g1 = - ( ax1 / (ax2 * ax2) );
		g2 = 2 * ax1 * dx2 / (ax2 * ax2);
		g3 = - 0.1 * ax1 / ax3;
		g4 = ax1 * ( 1.76 - (dx2 * dx2) /  (ax2 * ax2) + 0.1 * ax1 * dx3 / ax3 ) + dx1;
		
		h1 = ax2 / ax1;
		h2 = - ( ax2 * dx1 ) / ax1 + dx2;
	
		j1 = ax3 / ax2;
		j2 = - ( ax3 * dx2 )/ ax2 + dx3;
		
		u1 = x2 * x2 * g1 + x2 * g2 + x3 * g3 + x1 * c1 * h1 + x2 * c2 * j1 - x1 * A - x2 * c1 * A - x3 * c2 * A;
		
		x1n = g1 * x2 * x2 + g2 * x2 + g3 * x3 + g4;
		x2n = h1 * x1 + h2;
		x3n = j1 * x2 + j2;
		
		x1 = x1n;
		x2 = x2n;
		x3 = x3n;
		
		u2 = -(y2 * y2) * g1 - y2 * g2 - y3 * g3 - y1 * c1 * h1 - y2 * c2 * j1 + y1 * A + y2 * c1 * A + y3 * c2 * A;
		
		y1n = g1 * y2 * y2 + g2 * y2 + g3 * y3 + g4 + u1 + u2;
		y2n = h1 * y1 + h2;
		y3n = j1 * y2 + j2;
		
		y1 = y1n;
		y2 = y2n;
		y3 = y3n;
		tryDoOnce++;
		if(x1n==y1n){
			_pfc5 = 0;
			_pf5 = 1;
			delay(1000);
			_pf5 = 0;
			break;
		}
	}
}
//------
double chaosPartOfMasterU1(){
	u1 = x2 * x2 * g1 + x2 * g2 + x3 * g3 + x1 * c1 * h1 + x2 * c2 * j1 - x1 * A - x2 * c1 * A - x3 * c2 * A;
	return u1;
}

double chaosPartOfMasterX1n(){
	x1n = g1 * x2 * x2 + g2 * x2 + g3 * x3 + g4;
	x2n = h1 * x1 + h2;
	x3n = j1 * x2 + j2;
	x1 = x1n;
	x2 = x2n;
	x3 = x3n;
	return x1n;
}

_Bool tryExecuteChaos(double Um, double myx1n){
	u2 = -(y2 * y2) * g1 - y2 * g2 - y3 * g3 - y1 * c1 * h1 - y2 * c2 * j1 + y1 * A + y2 * c1 * A + y3 * c2 * A;
		
	y1n = g1 * y2 * y2 + g2 * y2 + g3 * y3 + g4 + Um + u2;
	y2n = h1 * y1 + h2;
	y3n = j1 * y2 + j2;
	
	y1 = y1n;
	y2 = y2n;
	y3 = y3n;
	tryDoOnce++;
	if(myx1n==y1n){
		_pfc5 = 0;
		_pf5 = 1;
		delay(100);
		_pf5 = 0;
		delay(100);
		_pf5 = 1;
		delay(100);
		_pf5 = 0;
		return 1;
	}
	return 0;
}

void tryLikeConnectChaos(){
	x1 = 0.5;
	x2 = -0.3;
	x3 = 0.4;
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
	while(1){
		g1 = - ( ax1 / (ax2 * ax2) );
		g2 = 2 * ax1 * dx2 / (ax2 * ax2);
		g3 = - 0.1 * ax1 / ax3;
		g4 = ax1 * ( 1.76 - (dx2 * dx2) /  (ax2 * ax2) + 0.1 * ax1 * dx3 / ax3 ) + dx1;
		
		h1 = ax2 / ax1;
		h2 = - ( ax2 * dx1 ) / ax1 + dx2;
	
		j1 = ax3 / ax2;
		j2 = - ( ax3 * dx2 )/ ax2 + dx3;
		double theUm = chaosPartOfMasterU1();
		double theX1n = chaosPartOfMasterX1n();
		if(tryExecuteChaos(theUm,theX1n)){
			break;	
		};	
	}	
}
//------
