#include "Int_DigitalTube.h"

static unsigned char buffer_EW[2];
static unsigned char buffer_SN[2];

void Int_DigitalTube_DisplayNum(int position, unsigned char num, bit symbol)
{
    P0 = 0;
    // λѡ����־λΪ1ѡ�������򣬱�־λΪ0ѡ���ϱ�����
    if (symbol == 1)
        P2 = (P2 | 0x0f) ^ position;
    if (symbol == 0)
        P2 = (P2 | 0x0f) ^ (position << 2);

    // ��ѡ
    Com_Util_Code(num);
}

void Int_DigitalTube_Display(unsigned char EW, unsigned char SN)
{
    int i;
    for (i = 0; i < 2; i++) // ��ʼ����ʾ����
    {
        buffer_EW[i] = 100;
        buffer_SN[i] = 100;
    }

    // ���������ֲ�⵽��ʾ������
    buffer_EW[0] = EW % 10;
    buffer_EW[1] = EW / 10;

    buffer_SN[0] = SN % 10;
    buffer_SN[1] = SN / 10;
}

void Int_DigitalTube_Refresh()
{
    int i;
    for (i = 0; i < 2; i++) {
        Int_DigitalTube_DisplayNum(i + 1, buffer_EW[i], 1);
    }
    for (i = 0; i < 2; i++) {
        Int_DigitalTube_DisplayNum(i + 1, buffer_SN[i], 0);
    }
}