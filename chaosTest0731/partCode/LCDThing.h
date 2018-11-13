#include <string.h>

#define LCD_EN			_pe0
#define LCD_ENC			_pec0
#define LCD_RS			_pe1
#define LCD_RSC			_pec1
#define LCD_RW			_pe2
#define LCD_RWC			_pec2
#define LCD_DataPort	_pd
#define LCD_DataPortC	_pdc
#define LCD_LINE_1		1
#define LCD_LINE_2		2

// Function set
#define DOT_5X10_OFF                    0x00
#define DOT_5X10_ON                     0x04
#define DUAL_LINE_OFF                   0x00
#define DUAL_LINE_ON                    0x08
#define BUS_8BIT_OFF                    0x00
#define BUS_8BIT_ON                     0x10
#define FUNCTION_SET(options)           LcdControl(0x20 | (options))

// Set display control
#define SHITF_DISPLAY_ON                0x04
#define SHITF_DISPLAY_OFF               0x00
#define SHITF_RIGHT_ON                  0x02
#define SHITF_RIGHT_OFF                 0x00
#define SET_CURSOR_SHIFT(options)       LcdControl(0x10 | (options))

// Set enter mode
#define INCREMENT_ON                    0x02
#define INCREMENT_OFF                   0x00
#define DISPLAY_SHIFT_ON                0x01
#define DISPLAY_SHIFT_OFF               0x00
#define SET_ENTER_MODE(options)         LcdControl(0x04 | (options))

// Display clear
#define DISPLAY_CLEAR()                 LcdControl(0x01)

// Set display control
#define DISPLAY_CTRL_ON                 0x04
#define DISPLAY_CTRL_OFF                0x00
#define DISPLAY_CTRL_BLINK_ON           0x01
#define DISPLAY_CTRL_BLINK_OFF          0x00
#define DISPLAY_CTRL_CURSOR_ON          0x02
#define DISPLAY_CTRL_CURSOR_OFF         0x00
#define SET_DISPLAY_CTRL(options)       LcdControl(0x08 | (options))

// Set Display Start Line
#define LINE1                           0x00
#define LINE2                           0x40
#define SET_DISPLAY_LINE(line)          LcdControl(0x80 | (line))

// LCD lines
#define LCD_LINE_COUNT                  2
#define LCD_LINE_LENGTH                 16

static void LcdControl(unsigned int command){
    LCD_RSC = 0;
    LCD_RS = 0;
    LCD_DataPort = command;
    LCD_EN = 1;
    delay(2);
    LCD_EN = 0;
    delay(80);
}

static void LcdWrite(unsigned int ch){
    LCD_RSC = 0;
    LCD_RS = 1;
    LCD_DataPort = ch;
    LCD_EN = 1;
    delay(2);
    LCD_EN = 0;
    delay(1);
}

void LcdClear(void){
    unsigned int n;
    SET_DISPLAY_LINE(LINE1);
    for (n = 0; n < LCD_LINE_LENGTH; n++){
        LcdWrite(' ');
    }
    SET_DISPLAY_LINE(LINE2);
    for (n = 0; n < LCD_LINE_LENGTH; n++){
        LcdWrite(' ');
    }
}

void LcdClearLINE1(unsigned int j){
	unsigned int n;
    SET_DISPLAY_LINE(LINE1+j);
    for (n = 0; n < LCD_LINE_LENGTH; n++){
        LcdWrite(' ');
    }
}

void LcdClearLINE2(short int j){
	short int n;
    SET_DISPLAY_LINE(LINE2+j);
    for(n = 0; n < LCD_LINE_LENGTH; n++){
    	LcdWrite(' ');
    }
}

void LcdWriteChar(unsigned int line, unsigned int col, char text){
    if (line == LCD_LINE_2){
        SET_DISPLAY_LINE(LINE2 + col);
    }else{
        SET_DISPLAY_LINE(LINE1 + col);
    }
    LcdWrite(text);
}

static void LcdWriteMany(char *pData, unsigned int count){
    while (count--){
        LcdWrite(*(pData++));
    }
}

void LcdWriteString(unsigned int line, unsigned int col, char *pText){
    if (line == LCD_LINE_2)
    {
        SET_DISPLAY_LINE(LINE2+col);
    }else{
        SET_DISPLAY_LINE(LINE1+col);
    }
    LcdWriteMany(pText, strlen(pText));
}


#define ABS(n)     (((n) < 0) ? -(n) : (n))
char *convInt32ToText(long value){
    static char pValueToTextBuffer[12];
    char *pLast;
    char *pFirst;
    char last;
    unsigned int negative;

    pLast = pValueToTextBuffer;

    // Record the sign of the value
    negative = (value < 0);
    value = ABS(value);

    // Print the value in the reverse order
    do{
        *(pLast++) = '0' + (unsigned int)(value % 10);
        value /= 10;
    }
    while (value);

    // Add the '-' when the number is negative, and terminate the string
    if (negative){
        *(pLast++) = '-';
    }
    *(pLast--) = 0x00;

    // Now reverse the string
    pFirst = pValueToTextBuffer;
    while (pLast > pFirst){
        last =  *pLast;
        *(pLast--) =  *pFirst;
        *(pFirst++) = last;
    }

    return pValueToTextBuffer;
}

void LcdWriteIntToChar(unsigned int lcd_line,unsigned int lcd_col,unsigned int lcd_text){
	char *pValue = convInt32ToText(lcd_text);
	if(lcd_line == LCD_LINE_1) LcdWriteString(LCD_LINE_1,lcd_col,pValue);
	if(lcd_line == LCD_LINE_2) LcdWriteString(LCD_LINE_2,lcd_col,pValue);
}



void LcdInit(void){	
	LCD_RWC = 0;
	LCD_RW = 0;
    LCD_DataPortC = 0;
	LCD_RSC = 0;
	LCD_ENC = 0;
    LCD_EN = 0;
    delay(15);

    FUNCTION_SET(BUS_8BIT_ON);
    delay(2);
    FUNCTION_SET(BUS_8BIT_ON);
    delay(2);
    FUNCTION_SET(BUS_8BIT_ON);
    delay(2);
    FUNCTION_SET(BUS_8BIT_ON | DUAL_LINE_ON);
    delay(2);
    FUNCTION_SET(BUS_8BIT_ON | DUAL_LINE_ON);
    delay(2);
    SET_CURSOR_SHIFT(SHITF_DISPLAY_OFF);
    SET_ENTER_MODE(INCREMENT_ON);
    DISPLAY_CLEAR();
    delay(2);
    // Clear the display
    LcdClear();
    SET_DISPLAY_CTRL(DISPLAY_CTRL_ON | DISPLAY_CTRL_BLINK_OFF | DISPLAY_CTRL_CURSOR_OFF);
}