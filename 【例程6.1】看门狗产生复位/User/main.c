/************************************************************************************** 
*   日期    ：2013年11月6日 (版权所有，翻版必究) 
*   目标    ：ARM Cortex-M0 LPC1114 
*   编译环境：KEIL 4.60
*   外部晶振：10Mhz(主频50M)
*   功能    ：学会使用看门狗基本用法
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
		for(j=0;j<250;j++);
}

int main()
{
	uint8_t i=0;
	
	UART_init(9600);
	WDT_Enable(1);	 // 看门狗初始化，1秒钟之内喂狗
	
	while(1)
	{
		delay();
		WDTFeed();
		UART_send_byte(i);
		i++;
	}
}




