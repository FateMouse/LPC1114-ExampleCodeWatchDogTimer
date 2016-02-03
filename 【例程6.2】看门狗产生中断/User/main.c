/************************************************************************************** 
*   日期    ：2013年11月6日 (版权所有，翻版必究) 
*   目标    ：ARM Cortex-M0 LPC1114 
*   编译环境：KEIL 4.60
*   外部晶振：10Mhz(主频50M)
*   功能    ：学会使用看门狗中断功能
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
 	LPC_WDT->MOD &= ~(0x1<<2);		// 清看门狗超时标志位WDTOF
	// 在下面可以写入当看门狗中断发生时你想要做的事情
	UART_send_byte('B');
	delay();//等待数据发送完成
	NVIC_SystemReset();
}

int main()
{
	UART_init(9600);
	WDT_Enable(0);	 // 看门狗初始化，1秒钟之内喂狗
	NVIC_EnableIRQ(WDT_IRQn);
	
	while(1)
	{
		delay();
//		WDTFeed();
		UART_send_byte('A');
	}
}




