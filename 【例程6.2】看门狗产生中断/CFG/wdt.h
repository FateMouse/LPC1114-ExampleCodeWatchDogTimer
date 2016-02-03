#ifndef __NXPLPC11XX_WDT_H__
#define __NXPLPC11XX_WDT_H__

extern void WDT_Enable(uint8_t mode);
extern void WDTFeed(void);
extern void WDT_IRQHandler(void);


#endif




