#include <REGX51.H>
#define uint unsigned int
#define uchar unsigned char
#define delaytime 10 // 延迟时间
#include <intrins.h>

sbit Buzzer=P2^5;

unsigned char PWM_COUNT; // 计数
unsigned int HUXI_COUNT; // 占空比更新时间
unsigned char PWM_VLAUE; // 占空比比对值
bit direc_flag; // 占空比更新方向
// 管脚定义
// sbit P2_0 = P2 ^ 0;
// sbit P2_1 = P2 ^ 1;
// sbit P2_2 = P2 ^ 2;
// sbit P2_3 = P2 ^ 3;
// sbit P2_4 = P2 ^ 4;
// sbit P2_5 = P2 ^ 5;
// sbit P2_6 = P2 ^ 6;
// sbit P2_7 = P2 ^ 7;

uint t = 1 , i = 0 , keycount = 0 , keycurrent = 0 , ti = 0 , current = 0 ;
uint LED[8] = {0}; // 8个led

// 延迟函数
void delay_ms(unsigned int a)
{
    unsigned int b;
    while (a-- != 0)for (b = 0; b < 600; b++);

}
void delay(uint s)
{
    while(s--);
}
// 定时，1ms

void i0_server_(void) interrupt 1
{
    TH0 = 0xFC;
    TL0 = 0x18;
    if(keycurrent ==4)
    {
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
    if(keycount != 0)
    {
    ti++;
    if(ti > 60000)ti=0;
    }


        if(keycurrent ==3)
    {
	PWM_COUNT++;
	HUXI_COUNT++;
	if(PWM_COUNT == PWM_VLAUE) // 判断是否到了点亮LED的时候
		P2 = 0xfe; // 点亮LED

	if(PWM_COUNT == 10) // 当前周期结束
	{
		P2 = 0xff; // 熄灭LED
		PWM_COUNT = 0;
    } // 重新计时 

		if((HUXI_COUNT == 60) && (direc_flag == 0))
		{ // 占空比增加10%
			HUXI_COUNT = 0;
			PWM_VLAUE++;
			if(PWM_VLAUE == 9) // 占空比更改方向
                direc_flag = 1;
		}

		if((HUXI_COUNT == 60) && (direc_flag == 1))

		{ // 占空比减少10%
			HUXI_COUNT = 0;
			PWM_VLAUE--;
			if(PWM_VLAUE == 1) // 占空比更改方向
				direc_flag = 0;
		} }

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






// void Timer0_Routine() interrupt 3
// {

// }


// void Init_t1(void)
// {
// 	TMOD =0x01;
// 	TH1 = 0x47; // 定时器溢出值设置，每隔200us发起一次中断。
// 	TL1 = 0X47;
// 	TR1 = 1; // 定时器0开始计时
// 	ET1 = 1; // 开定时器0中断
// 	EA = 1; // 开总中断
// 	PWM_COUNT = 0;
// }


void Buzzer_Delay500us()		//@12.000MHz
{
	unsigned char i;

	_nop_();
	i = 247;
	while (--i);
}

/**
  * @brief  蜂鸣器发声
  * @param  ms 发声的时长，范围：0~32767
  * @retval 无
  */
void Buzzer_Time(unsigned int ms)
{
	unsigned int i;
	for(i=0;i<ms*2;i++)
	{
		Buzzer=!Buzzer;
		Buzzer_Delay500us();
	}
}


void main()
{
    uint et = 1;
    // LED[7] = 10;
    Init_t0();
    // Init_t1();
    // for (i = 0; i < 8; i++)LED[i] = i;
    
    	HUXI_COUNT = 0;
		PWM_COUNT = 0;
		PWM_VLAUE = 5;
		direc_flag = 0;
		P2 = 0xff; // 默认LED熄灭
		 // 定时器0初始化

    while (1)
    {
        while (P3_1 == 0)
        {
            keycurrent =0;
            delay_ms(delaytime);
            if (keycount == 2 && et == 1){keycount = 3;et = 0;Buzzer_Time(100);}
            if (keycount == 1 && et == 1){keycount = 2;et = 0;Buzzer_Time(100);}
            if (keycount == 0 && et == 1){keycount = 1;et = 0;Buzzer_Time(100);}
            if (ti > 1000){keycurrent = 4;et = 0;keycount = 0;Buzzer_Time(100);}
        }

        et = 1;

        if(ti >1000)
        {
            if(keycurrent != 4)keycurrent = keycount;
            keycount = 0;
            ti = 0;
        }
        if(keycurrent == 1)
        {
            current++;
            if(current <5000)P2 = 0x00;
            if(current >10000)
            {
                P2 = 0xFF;
                if(current >15000)current = 0;
            }
        }
        if(keycurrent == 2)
        {
            current++;
            if(current <1000)P2 =~0x01;
            if(current >1000 && current <2000)P2 = ~0x02;
            if(current >2000 && current <3000)P2 = ~0x04;
            if(current >3000 && current <4000)P2 = ~0x08;
            if(current >4000 && current <5000)P2 = ~0x10;
            if(current >5000 && current <6000)P2 = ~0x20;
            if(current >6000 && current <7000)P2 = ~0x40;
            if(current >7000 && current <8000)P2 = ~0x80;
            if(current >8000)current =0;
        }
        if(keycurrent == 3)
        {

        }

        if(keycurrent == 4)
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
        }



    }
}