#ifndef   __NXPLPC11XX_UART_H__
#define   __NXPLPC11XX_UART_H__

extern uint8_t Recived_data; // 接收字节

extern void UART_init(uint32_t baudrate);  // 初始化串口
extern uint8_t UART_recive(void);   // 串口接收字节数据
extern void UART_send_byte(uint8_t byte); // 串口发送字节数据
extern void UART_send(uint8_t *Buffer, uint32_t Length); // 串口发送数组数据

#endif





