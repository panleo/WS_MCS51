#include <reg51.h>
sbit DB7 = P1^7;
sbit DB6 = P1^6;
sbit DB5 = P1^5;
sbit DB4 = P1^4;
sbit RS = P1^3;
sbit E = P1^2;
sbit PINO = P3^5;
#define LCD_DATA P1    // Dados nos P1.4-P1.7 (DB4-DB7)

void returnHome(void);
void entryModeSet(bit id, bit s);
void displayOnOffControl(bit display, bit cursor, bit blinking);
void cursorOrDisplayShift(bit sc, bit rl);
void functionSet(void);
void setDdRamAddress(char address);
void sendChar(char c);
void sendString(char* str);
bit getBit(char c, char bitNumber);
void delay(void);

void main(void) {
functionSet();
entryModeSet(1, 0); // increment and no shift
displayOnOffControl(1, 1, 1); // display on, cursor on and blinking on
	
	//char mensagem[32] = "XP SHPXOR YR PXN ^RPX^\\ R RHIRSR";
	//char mascara;
	//char variavel_mascara= -1;
	//char i;
	//char teste[32];
	//char linha[16];
	//char j;

sendString("EdSim51 LCD Module Simulation");
setDdRamAddress(0x40); // set address to start of second line
sendString("Based on Hitachi HD44780");


while (1) {
	PINO = 1;
	espera_us();
	PINO = 0;
	espera_us();
}
}

// LCD Module instructions -------------------------------------------
// To understand why the pins are being set to the particular values in the functions
// below, see HD44780.pdf.

void delay()
{
	TMOD &= 0xF0;  // Preserva a configuração do Timer 1
	TMOD |= 0x02;  // Timer 0 no Modo 2 (auto-reload)
		
	TL0 = 182; //(256 - tempo_us);
	TH0 = TL0;    
	TF0 = 0;  // Reseta a flag de overflow
	TR0 = 1;  // Liga o Timer 0
	while (!TF0);  // Espera até o overflow
    
	TR0 = 0;  // Desliga o Timer 0
	TF0 = 0;  // Reseta a flag
}

void returnHome(void) {
RS = 0;
DB7 = 0;
DB6 = 0;
DB5 = 0;
DB4 = 0;
E = 1;
E = 0;
DB5 = 1;
E = 1;
E = 0;
delay();
}
void entryModeSet(bit id, bit s) {
RS = 0;
DB7 = 0;
DB6 = 0;
DB5 = 0;
DB4 = 0;
E = 1;
E = 0;
DB6 = 1;
DB5 = id;
DB4 = s;
E = 1;
E = 0;
delay();
}
void displayOnOffControl(bit display, bit cursor, bit blinking) {
DB7 = 0;
DB6 = 0;
DB5 = 0;
DB4 = 0;
E = 1;
E = 0;
DB7 = 1;
DB6 = display;
DB5 = cursor;
DB4 = blinking;
E = 1;
E = 0;
delay();
}
void cursorOrDisplayShift(bit sc, bit rl) {
RS = 0;
DB7 = 0;
DB6 = 0;
DB5 = 0;
DB4 = 1;
E = 1;
E = 0;
DB7 = sc;
DB6 = rl;
E = 1;
E = 0;
delay();
}

void functionSet(void) {
// The high nibble for the function set is actually sent twice. Why? See 4-bit operation
// on pages 39 and 42 of HD44780.pdf.
DB7 = 0;
DB6 = 0;
DB5 = 1;
DB4 = 0;
RS = 0;
E = 1;
E = 0;
delay();
E = 1;
E = 0;
DB7 = 1;
E = 1;
E = 0;
delay();
}
void setDdRamAddress(char address) {
RS = 0;
DB7 = 1;
DB6 = getBit(address, 6);
DB5 = getBit(address, 5);
DB4 = getBit(address, 4);
E = 1;
E = 0;
DB7 = getBit(address, 3);
DB6 = getBit(address, 2);
DB5 = getBit(address, 1);
DB4 = getBit(address, 0);
E = 1;
E = 0;
delay();
}
void sendChar(char c) {
DB7 = getBit(c, 7);
DB6 = getBit(c, 6);
DB5 = getBit(c, 5);
DB4 = getBit(c, 4);
RS = 1;
E = 1;
E = 0;
DB7 = getBit(c, 3);
DB6 = getBit(c, 2);
DB5 = getBit(c, 1);
DB4 = getBit(c, 0);
E = 1;
E = 0;
delay();
}
// -- End of LCD Module instructions
// --------------------------------------------------------------------

void sendString(char* str) {
int index = 0;
while (str[index] != 0) {
sendChar(str[index]);
index++;
}
}
bit getBit(char c, char bitNumber) {
return (c >> bitNumber) & 1;
}
/*
void delay(void) {
char c;
for (c = 0; c < 50; c++);
}*/