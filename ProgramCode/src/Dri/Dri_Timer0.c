#include "Dri_Timer0.h"
#define MAX_CALLBACK 4

static Timer0_Callback s_callbacks[MAX_CALLBACK];

void Dri_Timer0_Init()
{
    unsigned int i;

    // 1.启用中断
    EA  = 1;
    ET0 = 1;

    // 2.工作模式 GATE=0,C/T=0,M1=0,M0=0 不启用外部、定时器、16位定时器
    TMOD = TMOD & 0xf0;
    TMOD = TMOD | 0x01;

    // 3.设置初始值  50ms
    TL0 = 0x00;
    TH0 = 0x68;

    // 4.启动
    TR0 = 1;

    // 5.初始化函数指针数组
    for (i = 0; i < MAX_CALLBACK; i++) {
        s_callbacks[i] = NULL;
    }
}

bit Dri_Timer0_RegisterCallback(Timer0_Callback callback)
{
    unsigned char i;
    // 确保不会重复注册
    for (i = 0; i < MAX_CALLBACK; i++) {
        if (s_callbacks[i] == callback) {
            return 1;
        }
    }

    // 寻找指针数组的空位
    for (i = 0; i < MAX_CALLBACK; i++) {
        if (s_callbacks[i] == NULL) {
            s_callbacks[i] = callback;
            return 1;
        }
    }

    // 指针数组没有空位
    return 0;
}

bit Dri_Timer0_DeregisterCallback(Timer0_Callback callback)
{
    unsigned char i;
    for (i = 0; i < MAX_CALLBACK; i++) {
        if (s_callbacks[i] == callback) {
            s_callbacks[i] = NULL;
            return 1;
        }
    }

    return 0;
}

void Dri_Timer0_Handler() interrupt 1
{
    unsigned char i;
    // 1.因为不能重加载，所以需要每次设置初始值
    TL0 = 0x00;
    TH0 = 0x68;

    // 2.轮询函数指针数组
    for (i = 0; i < MAX_CALLBACK; i++) {
        if (s_callbacks[i] != NULL) {
            s_callbacks[i]();
        }
    }
}