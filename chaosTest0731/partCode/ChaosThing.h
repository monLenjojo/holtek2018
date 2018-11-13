double g1,g2,g3,g4,h1,h2,j1,j2,u2,c1,c2,A,dx1,dx2,dx3,ax1,ax2,ax3,y1,y2,y3,y1n,y2n,y3n;
//double x1,x2,x3,x1n,x2n,x3n,u1;

void intiChaos(){
/*
	x1 = 0.5;
	x2 = -0.3;
	x3 = 0.4;
*/
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
}

void chaosMath(double Um){
	g1 = - ( ax1 / (ax2 * ax2) );
	g2 = 2 * ax1 * dx2 / (ax2 * ax2);
	g3 = - 0.1 * ax1 / ax3;
	g4 = ax1 * ( 1.76 - (dx2 * dx2) /  (ax2 * ax2) + 0.1 * ax1 * dx3 / ax3 ) + dx1;
	
	h1 = ax2 / ax1;
	h2 = - ( ax2 * dx1 ) / ax1 + dx2;
	
	j1 = ax3 / ax2;
	j2 = - ( ax3 * dx2 )/ ax2 + dx3;
/*
	u1 = x2 * x2 * g1 + x2 * g2 + x3 * g3 + x1 * c1 * h1 + x2 * c2 * j1 - x1 * A - x2 * c1 * A - x3 * c2 * A;
	
	x1n = g1 * x2 * x2 + g2 * x2 + g3 * x3 + g4;
	x2n = h1 * x1 + h2;
	x3n = j1 * x2 + j2;
	
	x1 = x1n;
	x2 = x2n;
	x3 = x3n;
*/
	u2 = -(y2 * y2) * g1 - y2 * g2 - y3 * g3 - y1 * c1 * h1 - y2 * c2 * j1 + y1 * A + y2 * c1 * A + y3 * c2 * A;
	
	y1n = g1 * y2 * y2 + g2 * y2 + g3 * y3 + g4 + Um + u2 ;
	y2n = h1 * y1 + h2;
	y3n = j1 * y2 + j2;
	
	y1 = y1n;
	y2 = y2n;
	y3 = y3n;
}
volatile long int IntY1,IntX1;
_Bool doMath(double Um, double xVal){
	if(y1==0.00 || y2==0.00 || y3==0.00){
		intiChaos();
	}
	chaosMath(Um);
	IntY1 = y1n*100000; 
	IntX1 = xVal*100000; 
	if(IntY1==IntX1){
		setLockState(HIGH);
		return 1;
	}else{
		return 0;	
	}
}