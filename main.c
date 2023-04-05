#include <REGX51.H>
#define uint unsigned int
#define uchar unsigned char
#define delaytime 10 // 延迟时间

// 管脚定义
// sbit P2_0 = P2 ^ 0;
// sbit P2_1 = P2 ^ 1;
// sbit P2_2 = P2 ^ 2;
// sbit P2_3 = P2 ^ 3;
// sbit P2_4 = P2 ^ 4;
// sbit P2_5 = P2 ^ 5;
// sbit P2_6 = P2 ^ 6;
// sbit P2_7 = P2 ^ 7;

uint t = 1;
uint LED[8] = {0}; // 8个led

// 延迟函数
void delay_ms(unsigned int a)
{
    unsigned int i;
    while (a-- != 0)for (i = 0; i < 600; i++);

}

// 定时，1ms

void time0_server_(void) interrupt 1
{
    TH0 = 0xFC;
    TL0 = 0x18;

    if (t >= 9)t = 1;
    else t++;

    if (t > LED[0]) // LED0 亮度
        P2_0 = 1;
    else
        P2_0 = 0;

    if (t > LED[1]) // LED1 亮度
        P2_1 = 1;
    else
        P2_1 = 0;

    if (t > LED[2]) // LED2 亮度
        P2_2 = 1;
    else
        P2_2 = 0;

    if (t > LED[3]) // LED3 亮度
        P2_3 = 1;
    else
        P2_3 = 0;

    if (t > LED[4]) // LED4 亮度
        P2_4 = 1;
    else
        P2_4 = 0;

    if (t > LED[5]) // LED5 亮度
        P2_5 = 1;
    else
        P2_5 = 0;

    if (t > LED[6]) // LED6 亮度
        P2_6 = 1;
    else
        P2_6 = 0;

    if (t > LED[7]) // LED7 亮度
        P2_7 = 1;
    else
        P2_7 = 0;
}

void Init_t0(void) // 定时器初始化
{
    TMOD = 0x01; // 选择方式1
    TH0 = 0xFC;
    TL0 = 0x18; // 1ms
    EA = 1;
    ET0 = 1;
    TR0 = 1; // 开始计数
}

void main(void)

{
    uint i, j;
    LED[7] = 10;
    Init_t0();
    for (i = 0; i < 8; i++)LED[i] = i;
    while (1)
    {
        LED[0] = 10;
        delay_ms(delaytime);
        LED[1] = 10;
        LED[0] = 6;
        delay_ms(delaytime);
        LED[2] = 10;
        LED[1] = 6;
        LED[0] = 2;
        for (i = 0; i < 5; i++)
        {
            LED[i] = 0;
            LED[i + 1] = 2;
            LED[i + 2] = 6;
            LED[i + 3] = 10;
            delay_ms(delaytime);
        }
        LED[5] = 0;
        LED[6] = 2;
        LED[7] = 6;
        delay_ms(delaytime);
        LED[6] = 0;
        LED[7] = 2;
        delay_ms(delaytime);
        LED[7] = 0;
        delay_ms(delaytime);
        /*
        for(i = 0;i <8;i++)
        {
        for(j = 0;j < 8;j++) LED[j] = (i+j)%8;
        delay_ms(10);
        }*/
    }
}