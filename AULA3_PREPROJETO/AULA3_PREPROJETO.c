#include <reg51.h>

#define FREQ_OSC 12000000
sbit RS = P1^3;
sbit E  = P1^2;
#define LCD_DATA P1    // Dados nos P1.4-P1.7 (DB4-DB7)


void espera_us(unsigned char tempo_us);
void LCD_INIT();
void LCD_4B_cmd(unsigned char cmd);
void LCD_PulseEnable();
void LCD_4B_wt(unsigned char dado);
void LCD_String(char *str);


void main()
{	
	LCD_INIT();	
	LCD_String("Hello 8051");  // Escreve no LCD
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
}

// Envia um comando para o LCD
void LCD_4B_cmd(unsigned char cmd) {
    RS = 0;           // Modo comando (RS = 0)
    LCD_DATA = (LCD_DATA & 0x0F) | (cmd & 0xF0); // Envia nibble alto (P1.4-P1.7)
    LCD_PulseEnable();
    LCD_DATA = (LCD_DATA & 0x0F) | ((cmd << 4) & 0xF0); // Envia nibble baixo
    LCD_PulseEnable();
    espera_us(60);
}

// Escreve um caractere no LCD
void LCD_4B_wt(unsigned char dado) {
    RS = 1;           // Modo dado (RS = 1)
    LCD_DATA = (LCD_DATA & 0x0F) | (dado & 0xF0); // Nibble alto
    LCD_PulseEnable();
    LCD_DATA = (LCD_DATA & 0x0F) | ((dado << 4) & 0xF0); // Nibble baixo
    LCD_PulseEnable();
    espera_us(60);
}


// Escreve uma string no LCD
void LCD_String(char *str) {
    while (*str) {
        LCD_4B_wt(*str++);
    }
}
