#include "lpc11xx.h"
#include "wdt.h"


/******************************************/
/* 函数功能：使能看门狗                   */
/* 参    数：mode = 1 不喂狗产生复位      */
/*           mode = 0 不喂狗产生中断      */
/******************************************/
void WDT_Enable(uint8_t mode)
{ 
  LPC_SYSCON->PDRUNCFG &= ~(0x1<<6);    // 看门狗振荡器时钟上电（bit6）
	LPC_SYSCON->WDTOSCCTRL = (0x1<<5); // DIVSEL=0 FREQSEL=1  WDT_OSC_CLK=300KHz
  LPC_SYSCON->WDTCLKSEL = 0x2;        // 选择看门狗时钟源
  LPC_SYSCON->WDTCLKUEN = 0x01;          // 更新时钟源
  LPC_SYSCON->WDTCLKUEN = 0x00;          // 先写0，再写1达到更新目的
  LPC_SYSCON->WDTCLKUEN = 0x01;
  while ( !(LPC_SYSCON->WDTCLKUEN & 0x01) );  // 等待更新成功
  LPC_SYSCON->WDTCLKDIV = 3;            // 设置看门狗分频值为3，所以现在的看门狗时钟为100K	
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<15);// 允许WDT时钟
  LPC_WDT->TC = 25000;		// 给看门狗定时器赋值，定时时间大约1秒(这是在wdt_clk=100KHz时)
	if(mode==1) LPC_WDT->MOD |= 0x03;		// 写值0x03：不喂狗产生复位  
  else if(mode==0) LPC_WDT->MOD |= 0x01; //  写值0x01：不喂狗发生中断
 	LPC_WDT->FEED = 0xAA;		// 喂看门狗，开启
  LPC_WDT->FEED = 0x55;    
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
}
/******************************************/
/* 函数功能：喂狗                         */
/******************************************/
void WDTFeed(void)
{
  LPC_WDT->FEED = 0xAA;		// 喂狗
  LPC_WDT->FEED = 0x55;
}




