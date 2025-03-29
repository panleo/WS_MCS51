#include <reg51.h>

<<<<<<< HEAD
#define FREQ_OSC 12000000
sbit RS = P1^3;
sbit E  = P1^2;
#define LCD_DATA P1    // Dados nos P1.4-P1.7 (DB4-DB7)


void espera_us(unsigned char tempo_us);
=======


//#define TIME_D 0.00004

sbit DB7 = P1^7;
sbit DB6 = P1^6;
sbit DB5 = P1^5;
sbit DB4 = P1^4;
sbit RS = P1^3;
sbit E  = P1^2;
sbit PINO = P3^5;
#define LCD_DATA P1    // Dados nos P1.4-P1.7 (DB4-DB7)
#define FREQ_OSC 22118400UL  // 22.1184 MHz (unsigned long)
#define TIME_D   40          // 0.00004 escalonado por 10^6

   

void Delay_ms();
>>>>>>> primeiroDisplay
void LCD_INIT();
void LCD_4B_cmd(unsigned char cmd);
void LCD_PulseEnable();
void LCD_4B_wt(unsigned char dado);
void LCD_String(char *str);
<<<<<<< HEAD
=======
void returnHome(void);
void entryModeSet(bit id, bit s);
void displayOnOffControl(bit display, bit cursor, bit blinking);
void functionSet(void);
void setDdRamAddress(char address);
void sendChar(char c);
void sendString(char* str);
bit getBit(char c, char bitNumber);

>>>>>>> primeiroDisplay


void main()
{	
	LCD_INIT();	
	LCD_String("Hello 8051");  // Escreve no LCD
<<<<<<< HEAD
	while(1);
}

void espera_us(unsigned int tempo_us)
{
	if (tempo_us == 0) return;

    TMOD &= 0xF0;  // Preserva a configuração do Timer 1
    TMOD |= 0x02;  // Timer 0 no Modo 2 (auto-reload)
		
    TH0 = (256 - tempo_us);
    TL0 = TH0;    
    TF0 = 0;  // Reseta a flag de overflow
    TR0 = 1;  // Liga o Timer 0
    while (!TF0);  // Espera até o overflow
    
    TR0 = 0;  // Desliga o Timer 0
    TF0 = 0;  // Reseta a flag
}

void LCD_INIT()
{
		espera_us(60);     // Espera estabilização do LCD
=======
	PINO = 1;
	Delay_ms();
	PINO = 0;
	Delay_ms();
	while(1);
}


void Delay_ms()
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




void LCD_INIT()
{
		Delay_ms();     // Espera estabilização do LCD
>>>>>>> primeiroDisplay
		/*
    // Configuração inicial (modo 8 bits - 3 vezes)
    LCD_4B_cmd(0x30); 
    espera_us(50);
    LCD_4B_cmd(0x30);
    espera_us(50);
    LCD_4B_cmd(0x30);
    espera_us(50);
		*/

    
    // Mudança para modo 4 bits
<<<<<<< HEAD
    LCD_4B_cmd(0x20); 
    espera_us(60);
    
    // Configuração do LCD: 2 linhas, fonte 5x8
    LCD_4B_cmd(0x28); 
    espera_us(60);
    
    // Liga display, cursor desligado
    LCD_4B_cmd(0x0C); 
    espera_us(60);
    
    // Limpa o display
    LCD_4B_cmd(0x01); 
    espera_us(60);
    
    // Modo de entrada (incremento automático)
    LCD_4B_cmd(0x06); 
    espera_us(60);

}

// Pulso no pino Enable (E)
void LCD_PulseEnable() {
    E = 1;
    espera_us(60);  // Pequeno atraso (~1 µs)
    E = 0;
    espera_us(60);
=======
	
    LCD_4B_cmd(0x20); 
    Delay_ms();
    
    // Configuração do LCD: 2 linhas, fonte 5x8
    LCD_4B_cmd(0x28); 
    Delay_ms();
    
    // Liga display, cursor desligado
    LCD_4B_cmd(0x0C); 
    Delay_ms();
    
    // Limpa o display
    LCD_4B_cmd(0x01); 
    Delay_ms();
    
    // Modo de entrada (incremento automático)
    LCD_4B_cmd(0x06); 
    Delay_ms();

}



// Pulso no pino Enable (E)
void LCD_PulseEnable() {
    E = 1;
    Delay_ms();  // Pequeno atraso (~1 µs)
    E = 0;
    Delay_ms();
>>>>>>> primeiroDisplay
}

// Envia um comando para o LCD
void LCD_4B_cmd(unsigned char cmd) {
    RS = 0;           // Modo comando (RS = 0)
    LCD_DATA = (LCD_DATA & 0x0F) | (cmd & 0xF0); // Envia nibble alto (P1.4-P1.7)
    LCD_PulseEnable();
    LCD_DATA = (LCD_DATA & 0x0F) | ((cmd << 4) & 0xF0); // Envia nibble baixo
    LCD_PulseEnable();
<<<<<<< HEAD
    espera_us(60);
=======
    Delay_ms();
>>>>>>> primeiroDisplay
}

// Escreve um caractere no LCD
void LCD_4B_wt(unsigned char dado) {
    RS = 1;           // Modo dado (RS = 1)
    LCD_DATA = (LCD_DATA & 0x0F) | (dado & 0xF0); // Nibble alto
    LCD_PulseEnable();
    LCD_DATA = (LCD_DATA & 0x0F) | ((dado << 4) & 0xF0); // Nibble baixo
    LCD_PulseEnable();
<<<<<<< HEAD
    espera_us(60);
=======
    Delay_ms();
>>>>>>> primeiroDisplay
}


// Escreve uma string no LCD
void LCD_String(char *str) {
    while (*str) {
        LCD_4B_wt(*str++);
    }
}
<<<<<<< HEAD
=======


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
void sendString(char *str) {
int index = 0;
while (str[index] != 0) {
sendChar(str[index]);
index++;
}
	/*while (*str)
	{
		sendChar(*str++);
	}*/
}
bit getBit(char c, char bitNumber) {
return (c >> bitNumber) & 1;
}
>>>>>>> primeiroDisplay
