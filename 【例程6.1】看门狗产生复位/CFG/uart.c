#include "lpc11xx.h"
#include "uart.h"


/************************************************/
/* 函数功能：初始化UART口                       */
/************************************************/
void UART_init(uint32_t baudrate)
{
	uint32_t DL_value,Clear=Clear;   // (用这种方式定义变量解决编译器的Warning)                       
	
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16); // 使能IOCON时钟 
	LPC_IOCON->PIO1_6 &= ~0x07;    
	LPC_IOCON->PIO1_6 |= 0x01; //把P1.6脚设置为RXD
	LPC_IOCON->PIO1_7 &= ~0x07;	
	LPC_IOCON->PIO1_7 |= 0x01; //把P1.7脚设置为TXD
	LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16); // 禁能IOCON时钟

	LPC_SYSCON->UARTCLKDIV = 0x1;	//时钟分频值为1
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<12);//允许UART时钟
	LPC_UART->LCR = 0x83;   //8位传输，1个停止位，无几偶校验，允许访问除数锁存器
	DL_value = SystemCoreClock/16/baudrate ;  //计算该波特率要求的除数锁存寄存器值
	LPC_UART->DLM = DL_value / 256;	   //写除数锁存器高位值			
	LPC_UART->DLL = DL_value % 256;	  //写除数锁存器低位值
	LPC_UART->LCR = 0x03;    //DLAB置0
	LPC_UART->FCR = 0x07;    //允许FIFO，清空RxFIFO 和 TxFIFO
	Clear = LPC_UART->LSR;   //读UART状态寄存器将清空残留状态
}

/************************************************/
/* 函数功能：串口接收字节数据                       */
/************************************************/
uint8_t UART_recive(void)
{	
	while(!(LPC_UART->LSR & (1<<0)));//等待接收到数据
	return(LPC_UART->RBR);			 //读出数据
}

/************************************************/
/* 函数功能：串口发送字节数据                       */
/************************************************/
void UART_send_byte(uint8_t byte)
{
	while ( !(LPC_UART->LSR & (1<<5)) );//等待发送完
	LPC_UART->THR = byte;
}

/************************************************/
/* 函数功能：串口发送数组数据                   */
/************************************************/
void UART_send(uint8_t *Buffer, uint32_t Length)
{
	while(Length != 0)
	{
		while ( !(LPC_UART->LSR & (1<<5)) );//等待发送完
		LPC_UART->THR = *Buffer;
		Buffer++;
		Length--;
	}
}


