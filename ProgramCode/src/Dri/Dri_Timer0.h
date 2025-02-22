#ifndef __DRI_TIMER0_H__
#define __DRI_TIMER0_H__

#include "REG51.H"
#include "STDIO.H"

typedef void(*Timer0_Callback)(void);

void Dri_Timer0_Init();
//注册回调函数，并判断是否成功
bit Dri_Timer0_RegisterCallback(Timer0_Callback callback);
//取消注册回调函数，并判断是否成功
bit Dri_Timer0_DeregisterCallback(Timer0_Callback callback);

#endif /* !__DRI_TIMER0_H__ */