#include "Int_INT0.h"

void Int_INT0_Init()
{
    //1.�����ж�
    EA = 1;
    EX0 = 1;

    //2.������ʽ���½��أ�
    IT0 = 1;
}

void INT0_Handler() interrupt 0
{
    unsigned int s_count = 0;
    unsigned int alt;
    alt = P1;
    Com_Util_Delay10ms();
    if(INT0 == 0){
        P1 = (P1 | 0x3f) & 0xc9;
    }
    while(s_count < 300){
        Com_Util_Delay10ms();
        s_count++;
    }
    P1 = alt;
}