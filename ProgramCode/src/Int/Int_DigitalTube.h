#ifndef __INT_DIGITALTUBE_H__
#define __INT_DIGITALTUBE_H__

#include "Com_Util.h"

// ʵ��ָ��λ������ָ�����֣�������
void Int_DigitalTube_DisplayNum(int position, unsigned char num, bit symbol);
// ������λ����
void Int_DigitalTube_Display(unsigned char EW, unsigned char SN);
// ѭ����������
void Int_DigitalTube_Refresh();

#endif /* !__INT_DIGITALTUBE_H__ */