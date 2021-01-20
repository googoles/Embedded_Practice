/*
 * Atmega_128Prac.c
 *
 * Created: 1/13/2021 10:13:48 PM
 * Author: Yunslog
 */

#include <mega128.h>
#include <delay.h>
#include <io.h>

#define Q0 PORTB.0
#define Q1 PORTB.1
#define Q2 PORTB.2
#define Q3 PORTB.3

#define S1 {Q0 = 0; Q1 = 1; Q2 = 1; Q3 = 1;} // 1번째 FND 선택
#define S2 {Q0 = 1; Q1 = 0; Q2 = 1; Q3 = 1;} // 2번째 FND 선택
#define S3 {Q0 = 1; Q1 = 1; Q2 = 0; Q3 = 1;} // 3번째 FND 선택
#define S4 {Q0 = 1; Q1 = 1; Q2 = 1; Q3 = 0;} // 4번째 FND 선택

#define FND PORTA

//const char Font[10] = {
//         //abcdefg.
//         //0b 하고 각각 a,b,c,d,e,f,g를 가르킨다.
//         //맨뒤는 dp포트         
//                0xc0, // FND FONT0
//                0xf9, // FND FONT1
//                0xa4, // FND FONT2
//                0xb0, // FND FONT3
//                0x99, // FND FONT4
//                0x92, // FND FONT5
//                0x82, // FND FONT6
//                0xf8, // FND FONT7
//                0x80, // FND FONT8
//                0x90  // FND FONT9
// 
//      };

char Font[ ] = {
         //abcdefg.
         //0b 하고 각각 a,b,c,d,e,f,g를 가르킨다.
         //맨뒤는 dp포트         
                0b11111100, // FND FONT0
                0b01100000, // FND FONT1
                0b11011010, // FND FONT2
                0b11110010, // FND FONT3
                0b01100110, // FND FONT4
                0b10110110, // FND FONT5
                0b10111110, // FND FONT6
                0b11100000, // FND FONT7
                0b11111110, // FND FONT8
                0b11110110  // FND FONT9
 
      };   

                
int count = 0;

void segment(unsigned int number)
{
    unsigned int Buff, i;
    unsigned char D1000, D100, D10, D1;
    
    D1000 = number/1000;
    Buff = number % 1000;
    D100 = Buff % 100;
    Buff = Buff % 100;
    D10 = Buff / 10;
    D1 = Buff % 10;
    
    for (i = 0; i <10; i++)
    {
    S4; // 첫 번째 FND를 ON 시킨다.
    FND = Font[D1000]; // 천의 자리수를 출력한다.
    delay_ms(500);
    FND = 0xff;
    S3; // 두 번째 FND를 ON 시킨다.
    FND = Font[D100]; // 백의 자리수를 출력한다.
    delay_ms(500);
    FND = 0xff;
    S2; // 세 번째 FND를 ON 시킨다.
    FND = Font[D10]; // 십의 자리수를 출력한다.
    delay_ms(500);
    FND = 0xff;
    S1; // 네 번째 FND를 ON 시킨다.
    FND = Font[D1]; // 일의 자리수를 출력한다.
    delay_ms(500);
    FND = 0xff;
    }

}

void Port_init(void)
{
    DDRA = 0xff;
    DDRB = 0xff;
}
                 
void main(void)
{
    Port_init();
    
    Q0 = Q1 = Q2 = Q3 = 0;
    
    while (1)
    {
        count++;
        segment(count);
        if(count == 9999) count = 0;
    
    
    
    }

}
