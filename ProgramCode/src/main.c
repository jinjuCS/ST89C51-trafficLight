/**
 * *********************************************
 *
 * 8051 blink demo
 *
 * PIN: P11
 *
 * *********************************************
 */

#include "Com_Util.h"
#include "Dri_Timer0.h"
#include "Int_DigitalTube.h"
#include "Int_INT0.h"
#define RED_LIGHT    15
#define GREEN_LIGHT  12
#define YELLOW_LIGHT 3

sbit RED_EW    = P1 ^ 0; // ���ƶ�������ĺ�ƣ��͵�ƽ����
sbit YELLOW_EW = P1 ^ 1; // ���ƶ�������ĻƵƣ��͵�ƽ����
sbit GREEN_EW  = P1 ^ 2; // ���ƶ���������̵ƣ��͵�ƽ����
sbit RED_SN    = P1 ^ 3; // �����ϱ�����ĺ�ƣ��͵�ƽ����
sbit YELLOW_SN = P1 ^ 4; // �����ϱ�����ĻƵƣ��͵�ƽ����
sbit GREEN_SN  = P1 ^ 5; // �����ϱ�������̵ƣ��͵�ƽ����

int time_EW = RED_LIGHT, time_SN = GREEN_LIGHT;
bit symbol_Same = 1; // ������������ĵ�ͬʱ��������

void traffic_Blink()
{
    static unsigned int count = 0;
    count++;

    // �ϱ������̵����4����˸
    if (time_EW <= 7 && time_SN <= 4 && time_EW >= 4) {
        if (count == 10 || count == 20)
            GREEN_SN = ~GREEN_SN;
    }

    // ���������̵����4����˸
    if (time_SN <= 7 && time_EW <= 4 && time_SN >= 4) {
        if (count == 10 || count == 20)
            GREEN_EW = ~GREEN_EW;
    }

    if (count == 20) {
        time_EW--;
        time_SN--;
        Int_DigitalTube_Display(time_EW, time_SN);
        Int_DigitalTube_Refresh();

        // �ϱ��̵�ʱ���������Ϊ�Ƶ�
        if (time_EW != 0 && time_SN == 0) {
            YELLOW_SN = 1;
            GREEN_SN  = 0;
            time_SN   = YELLOW_LIGHT;
            Int_DigitalTube_Display(time_EW, time_SN);
            Int_DigitalTube_Refresh();
        }

        if (time_EW == 0 && time_SN == 0) {
            // ������ƽ�������Ϊ�̵ƣ��ϱ��Ƶƽ�������Ϊ���
            if (symbol_Same == 1) {
                GREEN_EW    = 1;
                RED_EW      = 0;
                RED_SN      = 1;
                YELLOW_SN   = 0;
                time_EW     = GREEN_LIGHT;
                time_SN     = RED_LIGHT;
                symbol_Same = 0;
            }

            // �����Ƶƽ�������Ϊ��ƣ��ϱ���ƽ�������Ϊ�̵�
            else {
                RED_EW      = 1;
                YELLOW_EW   = 0;
                GREEN_SN    = 1;
                RED_SN      = 0;
                time_EW     = RED_LIGHT;
                time_SN     = GREEN_LIGHT;
                symbol_Same = 1;
            }
        }

        // �����̵ƽ�������Ϊ�Ƶ�
        if (time_EW == 0 && time_SN != 0) {
            YELLOW_EW = 1;
            GREEN_EW  = 0;
            time_EW   = YELLOW_LIGHT;
            Int_DigitalTube_Display(time_EW, time_SN);
            Int_DigitalTube_Refresh();
        }

        count = 0;
    }
}

void main()
{
    // ��ʼʱ��������ƣ��ϱ��̵�
    YELLOW_EW = 0;
    GREEN_EW  = 0;
    RED_SN    = 0;
    YELLOW_SN = 0;
    Int_DigitalTube_Display(time_EW, time_SN);
    Int_DigitalTube_Refresh();
    Int_INT0_Init();
    Dri_Timer0_Init();
    Dri_Timer0_RegisterCallback(traffic_Blink);
    while (1) {
        Int_DigitalTube_Display(time_EW, time_SN);
        Int_DigitalTube_Refresh();
    }
}