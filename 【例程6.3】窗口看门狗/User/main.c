/************************************************************************************** 
*   日期    ：2013年11月6日 (版权所有，翻版必究) 
*   目标    ：ARM Cortex-M0 LPC1114 
*   编译环境：KEIL 4.60
*   外部晶振：10Mhz(主频50M)
*   功能    ：学会使用窗口看门狗功能
*   作者    ：Ration
*   官方网址：http://www.rationmcu.com
*   淘宝店  ：http://ration.taobao.com
**************************************************************************************/
#include "lpc11xx.h"
#include "wdt.h"
#include "uart.h"


void delay(void)
{
	uint16_t i,j;
	
	for(i=0;i<5000;i++)
		for(j=0;j<280;j++);
}

/******************************************/
/* 函数功能：看门狗中断服务函数           */
/* 说明：当MOD值设置为0x01时，如果没有及时*/
/*       喂狗，将会进入这个中断函数。     */
/******************************************/
void WDT_IRQHandler(void)
{
 	LPC_WDT->MOD &= ~(0x1<<2);		// 清看门狗中断标志位WDTOF
	WDTFeed();
}

int main()
{
	uint8_t cnt=0;
	
	UART_init(9600);
	WDT_Window_Enable();	 // 看门狗初始化，1秒钟之内喂狗
	NVIC_EnableIRQ(WDT_IRQn);
	
	while(1)
	{
		UART_send_byte(cnt++);
		delay();
	}
}




