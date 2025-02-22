#include "Com_Util.h"

void Com_Util_Delay10ms() //@11.0592MHz
{
    unsigned char i, j;

    i = 18;
    j = 235;
    do {
        while (--j);
    } while (--i);
}

void Com_Util_Code(unsigned char num) // ±àÂë
{
    switch (num) {
        case 0:
            P0 = 0x3f;
            break;
        case 1:
            P0 = 0x06;
            break;
        case 2:
            P0 = 0x5b;
            break;
        case 3:
            P0 = 0x4f;
            break;
        case 4:
            P0 = 0x66;
            break;
        case 5:
            P0 = 0x6d;
            break;
        case 6:
            P0 = 0x7d;
            break;
        case 7:
            P0 = 0x07;
            break;
        case 8:
            P0 = 0x7f;
            break;
        case 9:
            P0 = 0x6f;
            break;
        default:
            break;
    }
}