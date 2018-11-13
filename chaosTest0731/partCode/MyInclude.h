#include <HT66F70A.h>
#include "MyType.h"
#include "MyDefine.h"
void delay(u16 del){	
	u16 i;
	for(i=0;i<del;i++) GCC_DELAY(2000);				//Delay del ms @fSYS=8MHz
}
#include "LCDThing.h"
#include "MyFunction.h"
#include "ChaosThing.h"
#include "MyISR.h"