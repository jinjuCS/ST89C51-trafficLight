#ifndef __INT_DIGITALTUBE_H__
#define __INT_DIGITALTUBE_H__

#include "Com_Util.h"

// 实现指定位置亮起指定数字（单个）
void Int_DigitalTube_DisplayNum(int position, unsigned char num, bit symbol);
// 点亮多位数字
void Int_DigitalTube_Display(unsigned char EW, unsigned char SN);
// 循环遍历数组
void Int_DigitalTube_Refresh();

#endif /* !__INT_DIGITALTUBE_H__ */