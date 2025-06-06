#define _XTAL_FREQ 8000000
#include <xc.h>
 
// LCD Connections
#define RS RD2
#define EN RD3
#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7
 
// DHT11 Pin
#define DHT11_Data_Pin PORTCbits.RC0
#define DHT11_Data_Pin_Direction TRISCbits.TRISC0
 
// Configuration Bits
#pragma config FOSC = EXTRC_CLKOUT
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config MCLRE = ON
#pragma config CP = OFF
#pragma config CPD = OFF
#pragma config BOREN = ON
#pragma config IESO = ON
#pragma config FCMEN = ON
#pragma config LVP = ON
#pragma config BOR4V = BOR40V
#pragma config WRT = OFF
 
// Variables
unsigned char Check_bit, Temp_byte_1, Temp_byte_2, RH_byte_1, RH_byte_2;
unsigned char temper, RH, Sumation;
char Temp[] = "00.0 C";
char Hum[]  = "00.0 %";
 
// LCD Functions
void Lcd_Port(char a) {
    D4 = (a >> 0) & 1;
    D5 = (a >> 1) & 1;
    D6 = (a >> 2) & 1;
    D7 = (a >> 3) & 1;
}
 
void Lcd_Cmd(char a) {
    RS = 0;
    Lcd_Port(a >> 4);
    EN = 1;
    __delay_us(40);
    EN = 0;
    Lcd_Port(a & 0x0F);
    EN = 1;
    __delay_us(40);
    EN = 0;
}
 
void Lcd_Clear(void) {
    Lcd_Cmd(0x01);
    __delay_ms(2);
}
 
void Lcd_Set_Cursor(char row, char col) {
    char pos;
    if (row == 1)
        pos = 0x80 + col - 1;
    else
        pos = 0xC0 + col - 1;
 
    Lcd_Cmd(pos);
}
 
void Lcd_Init(void) {
    Lcd_Port(0x00);
    __delay_ms(20);
 
    Lcd_Cmd(0x03);
    __delay_ms(5);
    Lcd_Cmd(0x03);
    __delay_us(150);
    Lcd_Cmd(0x03);
    Lcd_Cmd(0x02); // 4-bit mode
 
    Lcd_Cmd(0x28); // 2 lines, 5x7 matrix
    Lcd_Cmd(0x0C); // Display ON, cursor OFF
    Lcd_Cmd(0x06); // Increment cursor
    Lcd_Cmd(0x01); // Clear display
    __delay_ms(2);
}
 
void Lcd_Write_Char(char a) {
    RS = 1;
    Lcd_Port(a >> 4);
    EN = 1;
    __delay_us(40);
    EN = 0;
    Lcd_Port(a & 0x0F);
    EN = 1;
    __delay_us(40);
    EN = 0;
}
 
void Lcd_Write_String(char *str) {
    while (*str)
        Lcd_Write_Char(*str++);
}
 
// DHT11 Functions
void dht11_init(void) {
    DHT11_Data_Pin_Direction = 0; // Output
    DHT11_Data_Pin = 0;
    __delay_ms(18);
    DHT11_Data_Pin = 1;
    __delay_us(30);
    DHT11_Data_Pin_Direction = 1; // Input
}
 
void find_response(void) {
    Check_bit = 0;
    __delay_us(40);
    if (DHT11_Data_Pin == 0) {
        __delay_us(80);
        if (DHT11_Data_Pin == 1) {
            Check_bit = 1;
        }
        __delay_us(50);
    }
}
 
char read_dht11(void) {
    char data = 0;
    for (char i = 0; i < 8; i++) {
        while (!DHT11_Data_Pin);
        __delay_us(30);
        if (DHT11_Data_Pin == 0) {
            data &= ~(1 << (7 - i));
        } else {
            data |= (1 << (7 - i));
            while (DHT11_Data_Pin);
        }
    }
    return data;
}
 
// Main Program
void main(void) {
    unsigned int val;
    unsigned char a, b, c, d;
 
    TRISD = 0x00;
    TRISC = 0xFF;
 
    Lcd_Init();
 
    while (1) {
        dht11_init();
        find_response();
 
        if (Check_bit == 1) {
            RH_byte_1 = read_dht11();
            RH_byte_2 = read_dht11();
            Temp_byte_1 = read_dht11();
            Temp_byte_2 = read_dht11();
            Sumation = read_dht11();
 
            if (Sumation == ((RH_byte_1 + RH_byte_2 + Temp_byte_1 + Temp_byte_2) & 0xFF)) {
                temper = Temp_byte_1;
                RH = RH_byte_1;
 
                // Temperature display
                Temp[0] = (temper / 10) + '0';
                Temp[1] = (temper % 10) + '0';
                Temp[3] = '0';
                Temp[4] = '0';
 
                Lcd_Set_Cursor(1, 1);
                Lcd_Write_String("Temp: ");
                Lcd_Write_String(Temp);
 
                // Humidity display
                Hum[0] = (RH / 10) + '0';
                Hum[1] = (RH % 10) + '0';
                Hum[3] = '0';
                Hum[4] = '0';
 
                Lcd_Set_Cursor(2, 1);
                Lcd_Write_String("RH:   ");
                Lcd_Write_String(Hum);
 
            } else {
                Lcd_Set_Cursor(1, 1);
                Lcd_Write_String("Checksum Error");
                Lcd_Set_Cursor(2, 1);
                Lcd_Write_String("Try Again...");
            }
        }
 
        __delay_ms(2000); // Wait 2 seconds before next read
    }
}
