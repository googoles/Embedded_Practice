#include<mega128.h>
#include<delay.h>
#define Q0 PORTB.0
#define Q1 PORTB.1
#define Q2 PORTB.2
#define Q3 PORTB.3

#define S1 {Q0 = 1; Q1 = 0; Q2 = 0; Q3 = 0;} // 1��° FND ����
#define S2 {Q0 = 0; Q1 = 1; Q2 = 0; Q3 = 0;} // 2��° FND ����
#define S3 {Q0 = 0; Q1 = 0; Q2 = 1; Q3 = 0;} // 3��° FND ����
#define S4 {Q0 = 0; Q1 = 0; Q2 = 0; Q3 = 1;} // 4��° FND ����

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
    
    D1000 = number/1000; //õ�� ��
    Buff = number % 1000; // 1000���� ���� ������ �� ����
    D100 = Buff / 100; // �����ڸ�
    Buff = Buff % 100;  // 100���� ���� ������ �� ����
    D10 = Buff / 10;  // �����ڸ�
    D1 = Buff % 10;   // �����ڸ�
    
    for (i = 0; i <10; i++)
    {
    S1; // ù ��° FND�� ON ��Ų��.
    FND = Font[D1000]; // õ�� �ڸ����� ����Ѵ�.
    delay_us(500);
    FND = 0xff;
    S2; // �� ��° FND�� ON ��Ų��.
    FND = Font[D100]; // ���� �ڸ����� ����Ѵ�.
    delay_us(500);
    FND = 0xff;
    S3; // �� ��° FND�� ON ��Ų��.
    FND = Font[D10]; // ���� �ڸ����� ����Ѵ�.
    delay_us(500);
    FND = 0xff;
    S4; // �� ��° FND�� ON ��Ų��.
    FND = Font[D1]; // ���� �ڸ����� ����Ѵ�.
    delay_us(500);
    FND = 0xff;
    }

}


void Port_init(void)
{
    DDRB = 0xff; // ��Ʈ A�� ������� �����Ѵ�.
    DDRA = 0xff; // ��Ʈ B�� ������� �����Ѵ�.
}

void main(void)
{
    Port_init();
    Q0=Q1=Q2=Q3=0; // ��� FND(0~3)�� ����(ON)�Ѵ�.
    while(1)
    {   
        count++;
        segment(count);
        if(count == 9999) count = 0;
    }
}
