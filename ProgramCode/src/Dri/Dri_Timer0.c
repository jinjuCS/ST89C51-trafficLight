#include "Dri_Timer0.h"
#define MAX_CALLBACK 4

static Timer0_Callback s_callbacks[MAX_CALLBACK];

void Dri_Timer0_Init()
{
    unsigned int i;

    // 1.�����ж�
    EA  = 1;
    ET0 = 1;

    // 2.����ģʽ GATE=0,C/T=0,M1=0,M0=0 �������ⲿ����ʱ����16λ��ʱ��
    TMOD = TMOD & 0xf0;
    TMOD = TMOD | 0x01;

    // 3.���ó�ʼֵ  50ms
    TL0 = 0x00;
    TH0 = 0x68;

    // 4.����
    TR0 = 1;

    // 5.��ʼ������ָ������
    for (i = 0; i < MAX_CALLBACK; i++) {
        s_callbacks[i] = NULL;
    }
}

bit Dri_Timer0_RegisterCallback(Timer0_Callback callback)
{
    unsigned char i;
    // ȷ�������ظ�ע��
    for (i = 0; i < MAX_CALLBACK; i++) {
        if (s_callbacks[i] == callback) {
            return 1;
        }
    }

    // Ѱ��ָ������Ŀ�λ
    for (i = 0; i < MAX_CALLBACK; i++) {
        if (s_callbacks[i] == NULL) {
            s_callbacks[i] = callback;
            return 1;
        }
    }

    // ָ������û�п�λ
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
    // 1.��Ϊ�����ؼ��أ�������Ҫÿ�����ó�ʼֵ
    TL0 = 0x00;
    TH0 = 0x68;

    // 2.��ѯ����ָ������
    for (i = 0; i < MAX_CALLBACK; i++) {
        if (s_callbacks[i] != NULL) {
            s_callbacks[i]();
        }
    }
}