//获取TCSR寄存器的值
INT32U get_TCSR(INT32U offset)
{
    INT32U TCSR_val = REG32(TIMER_BASE + offset);
    return TCSR_val;
}

//设置TCSR寄存器
void set_TCSR(INT32U offset, INT32U TCSR_val)
{
    REG32(TIMER_BASE + offset) = TCSR_val;
}

// 定时器初始化
void timer_init(INT32U offset, INT8U tri)
{
    INT32U TCSR_val = REG32(TIMER_BASE + offset);
    TCSR_val |= 0x00000020;
    REG32(TIMER_BASE + offset) = TCSR_val;			// 将定时器的控制状态寄存器TCSR的第5位（LOAD）置为1

    TCSR_val = REG32(TIMER_BASE + offset);
    TCSR_val |= 0x00000010;
    REG32(TIMER_BASE + offset) = TCSR_val;			// 将定时器的控制状态寄存器TCSR的第4位（ARTH）置为1

    TCSR_val = REG32(TIMER_BASE + offset);
    if(tri == 0)
      TCSR_val &= 0xfffffffd;						// 将定时器的控制状态寄存器TCSR的第1位（UDT）置为0
    else
      TCSR_val |= 0x00000002; 						// 将定时器的控制状态寄存器TCSR的第1位（UDT）置为1
    REG32(TIMER_BASE + offset) = TCSR_val;			

    TCSR_val = REG32(TIMER_BASE + offset);
    TCSR_val |= 0x00000040;
    REG32(TIMER_BASE + offset) = TCSR_val;			// 将定时器的控制状态寄存器TCSR的第6位（ENIT）置为1
}

// 加载定时器的TLR寄存器，设置定时值
void timer_load(INT32U offset, INT32U cnt)
{
    REG32(TIMER_BASE + offset) = cnt;
}

// 启动定时器计时
void timer_start(INT32U offset)
{
    INT32U TCSR_val = get_TCSR(offset); 
    set_TCSR(offset, (TCSR_val & 0xffffffdf));		// 将定时器的控制状态寄存器TCSR的第5位（LOAD）清0
    TCSR_val = get_TCSR(offset); 
    set_TCSR(offset, (TCSR_val | 0x00000080));		// 将定时器的控制状态寄存器TCSR的第7位（ENT）置为1
}

// 判断定时器是否到达预设的计数值
INT8U timer_expired(INT32U offset)
{
    INT32U TCSR_val = get_TCSR(offset);
    return (TCSR_val & 0x00000100) >> 8;
    
}

// 清除定时器TCSR寄存器的中断状态位（TINT）
void timer_clrINT(INT32U offset)
{
    INT32U TCSR_val = get_TCSR(offset);
    set_TCSR(offset, (TCSR_val | 0x00000100));		// 向定时器的控制状态寄存器TCSR的第8位（TINT）写入1
}
