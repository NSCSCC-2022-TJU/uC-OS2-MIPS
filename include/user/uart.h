// 串口初始化
void uart_init(void)
{
	REG32(UART_BASE + UART_CTRL) =  (INT32U)0;
	return;
}

// 串口发送字节
void uart_sendByte(INT8U Data)
{
	INT32U StatusRegister = REG32(UART_BASE + UART_STAT);
	while ((StatusRegister & 0x08) == 0x08) {
		StatusRegister = REG32(UART_BASE + UART_STAT);
	}
	REG32(UART_BASE + UART_RT) = Data;
}

// 串口发送字符串
INT32U uart_print(INT8U *SentBuff, INT32U NumBytes) {

	INT32U SentCount = 0;
	INT8U StatusRegister;

	REG32(UART_BASE + UART_CTRL) =  (INT32U)0;

	INT32U RemainingBytes = NumBytes;
	
	while (SentCount < RemainingBytes) {
		uart_sendByte(SentBuff[SentCount]);
		SentCount++;
	}

	return SentCount;
}
