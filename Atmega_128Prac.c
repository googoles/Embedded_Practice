#include<mega128.h>
#include<delay.h>
#define Q0 PORTB.0
#define Q1 PORTB.1
#define Q2 PORTB.2
#define Q3 PORTB.3

#define S1 {Q0 = 1; Q1 = 0; Q2 = 0; Q3 = 0;} // 1번째 FND 선택
#define S2 {Q0 = 0; Q1 = 1; Q2 = 0; Q3 = 0;} // 2번째 FND 선택
#define S3 {Q0 = 0; Q1 = 0; Q2 = 1; Q3 = 0;} // 3번째 FND 선택
#define S4 {Q0 = 0; Q1 = 0; Q2 = 0; Q3 = 1;} // 4번째 FND 선택

#define FND PORTA

const char Font[10] = {0xc0,0xf9,0xa4, // 0,1,2
                       0xb0,0x99,0x92, // 3,4,5
                       0x82,0xf8,0x80, // 6,7,8
                       0x90}; // 9
int count=0;

void segment(unsigned int number)
{
    unsigned int Buff, i;
    unsigned char D1000, D100, D10, D1;
    
    D1000 = number/1000; //천의 자
    Buff = number % 1000; // 1000으로 나눈 나머지 값 저장
    D100 = Buff / 100; // 백의자리
    Buff = Buff % 100;  // 100으로 나눈 나머지 값 저장
    D10 = Buff / 10;  // 십의자리
    D1 = Buff % 10;   // 일의자리
    
    for (i = 0; i <10; i++)
    {
    S1; // 첫 번째 FND를 ON 시킨다.
    FND = Font[D1000]; // 천의 자리수를 출력한다.
    delay_us(500);
    FND = 0xff;
    S2; // 두 번째 FND를 ON 시킨다.
    FND = Font[D100]; // 백의 자리수를 출력한다.
    delay_us(500);
    FND = 0xff;
    S3; // 세 번째 FND를 ON 시킨다.
    FND = Font[D10]; // 십의 자리수를 출력한다.
    delay_us(500);
    FND = 0xff;
    S4; // 네 번째 FND를 ON 시킨다.
    FND = Font[D1]; // 일의 자리수를 출력한다.
    delay_us(500);
    FND = 0xff;
    }

}


void Port_init(void)
{
    DDRB = 0xff; // 포트 A를 출력으로 설정한다.
    DDRA = 0xff; // 포트 B를 출력으로 설정한다.
}

void main(void)
{
    Port_init();
    Q0=Q1=Q2=Q3=0; // 모든 FND(0~3)를 선택(ON)한다.
    while(1)
    {   
        count++;
        segment(count);
        if(count == 9999) count = 0;
    }
}
