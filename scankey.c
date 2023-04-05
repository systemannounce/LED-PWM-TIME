/**************************************************************************
函数功能：按键扫描
入口参数：双击等待时间
返回 值：按键状态 0：无动作 1：单击 2：双击
key=0是按下的意思
**************************************************************************/
u8 click_N_Double(u8 time)
{
    static u8 flag_key, count_key, double_key;
    static u16 count_single, Forever_count;
    if (KEY2 == 0)
        Forever_count++; // 长按标志位未置1
    else
        Forever_count = 0;
    if (0 == KEY2 && 0 == flag_key)
        flag_key = 1;
    if (0 == count_key)
    {
        if (flag_key == 1) // 单击一次进去一次
        {
            double_key++;
            count_key = 1;
        }
        if (double_key == 2) // 判断双击
        {
            double_key = 0;
            count_single = 0;
            return 2; // 双击执行的指令
        }
    }
    if (1 == KEY2)
        flag_key = 0, count_key = 0;
    if (1 == double_key)
    {
        count_single++;
        if (count_single > time && Forever_count < time)
        {
            // 中间间隔时间太长 判断为的单击
            double_key = 0;
            count_single = 0;
            return 1; // 单击执行的指令
        }
        if (Forever_count > time)
        {
            // 长按不放
            double_key = 0;
            count_single = 0;
        }
    }
    return 0;
}

/**************************************************************************
函数功能：按键扫描（这里的操作主要是为了单击）
入口参数：无
返回 值：按键状态 0：无动作 1：单击
**************************************************************************/
u8 click(void)
{
    static u8 flag_key = 1; // 按键按松开标志
    if (flag_key && KEY == 0)
    {
        flag_key = 0;
        return 1; // 按键按下
    }
    else if (1 == KEY)
        flag_key = 1;
    return 0; // 无按键按下
}

/**************************************************************************
函数功能：长按检测
入口参数：无
返回 值：按键状态 0：无动作 1：长按2s
**************************************************************************/
u8 Long_Press(void)
{
    static u16 Long_Press_count, Long_Press;
    if (Long_Press == 0 && KEY == 0)
        Long_Press_count++; // 长按标志位未置1
    else
        Long_Press_count = 0;
    if (Long_Press_count > 200)

    {
        Long_Press = 1; // 这里是为了控制长按时间
        Long_Press_count = 0;
        return 1;
    }

    if (Long_Press == 1) // 长按标志位置1

    {
        Long_Press = 0;
    }
    return 0;
}