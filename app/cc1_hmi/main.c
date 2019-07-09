////////////////////////////////////////////////////////////////////////////////
/// @file     MAIN.C
/// @author   D CHEN
/// @version  2.0.0 Beta4
/// @date     2019-07-02
/// @brief    THIS FILE PROVIDES ALL THE SPI_DMA EXAMPLE.
////////////////////////////////////////////////////////////////////////////////
/// @attention
///
/// THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
/// CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
/// TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
/// CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
/// HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
/// CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
///
/// <H2><CENTER>&COPY; COPYRIGHT 2018-2019 MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
#define _MAIN_C_
////////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include "system_mm32.h"
#include "mm32.h"

#include "drv.h"
#include "resource.h"


#include "rtc.h"
#include "datetime.h"
#include "lcd.h"
#include "uart.h"
#include "tim.h"

////////////////////////////////////////////////////////////////////////////////
void AppTaskTick()
{
    if (tickCnt++ >= 250) {
        tickCnt  = 0;
        tickFlag = true;
    }
    decodeTick();
    setTimTick();
    beepTick();
    AlarmTick();
    encodeTick();
    
}

////////////////////////////////////////////////////////////////////////////////
void initPara()
{
    recFlag     = false;
    txSendFlag  = false;
    isFirstRx   = true;
    beepFlag    = false;
    autoModeFlag= false;
    ledCmd      = 0;
    timTick     = 0;
    beepMode    = biNone;
}


////////////////////////////////////////////////////////////////////////////////
void initPeripheral()
{
    lcd_init();
    initUART(COMx);
    initBeepTimer();
    initLcdTimer();
    while(initRTC()){};
    
}

////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    MCUID = SetSystemClock(emSYSTICK_On, (u32*)&AppTaskTick);
    
    initPara();
    initPeripheral();
    vdLED = 0x01;
    
    while(1){
        lcdTick();        
        
        if (SysKeyboard(&vkKey)) {
            switch  (vkKey) {
                case  VK_K0:
                beepMode = bi;
                (vdLED & 0x01) ? (vdLED &= ~0x01) : (vdLED |= 0x01); // toggle LD1
                KeyProcess_Key0();
                break;
                case  VK_K1:
                beepMode = bibi;
                (vdLED & 0x02) ? (vdLED &= ~0x02) : (vdLED |= 0x02); // toggle LD1
                KeyProcess_Key1();
                break;
                case  VK_K2:
                beepMode = bi_bi;
                (vdLED & 0x04) ? (vdLED &= ~0x04) : (vdLED |= 0x04); // toggle LD1
                RTC_SetTime(&gtp);
                KeyProcess_Key2();
                break;
                default:
                break;
            }
        }
        
        if (tickFlag) {                
            vdLED = vdLED << 1;
            if(vdLED > 8)
                vdLED = 1;
            tickFlag = false;
        }
        SysDisplay((u8*)&vdLED);
    }
    
}
