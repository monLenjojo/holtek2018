#define  KeyPort		_pg
#define  KeyPortC		_pgc
#define  KeyPortPU		_pgpu
#define	_TX				_pa1							//連接至藍芽RX (Yellow)
#define	_TXC			_pac1
#define	_RX				_pa3							//連接至藍芽TX (Blue)
#define	_RXC			_pac3
#define _RXPU			_papu3
#define _BTstate		_pe5
#define _BTstateC		_pec5
#define _BTstatePU		_pepu5
#define _OpenIRState	_pe6
#define _OpenIRStateC	_pec6
#define _OpenIRStatePU	_pepu6
#define _doorRelay		_pf3
#define _doorRelayC		_pfc3
#define _doorRelayPU	_pfpu3
#define _buzzerRelay	_pf4
#define _buzzerRelayC	_pfc4
#define _buzzerRelayPU	_pfpu4
#define	fSYS		8000000	
#define	BaudRate	9800	
#define	BITC		(fSYS/BaudRate)					//Bit Interval Time Constant
#define HIGH		1
#define LOW			0