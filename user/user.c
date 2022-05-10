#include "includes.h"
#include "machine.h"
#include "uart.h"
#include "gpio.h"
#include "timer.h"

#define TASK_STK_SIZE 256
OS_STK TaskStartStk[TASK_STK_SIZE];
OS_STK TaskGpioStk[TASK_STK_SIZE];
OS_STK Taskx7SegStk[TASK_STK_SIZE];

/*uC/OS-II Running!\r\n*/
char Info[19] = {0x75,0x43,0x2F,0x4f,0x53,0x2D,0x49,0x49,0x20,0x52,0x75,0x6E,0x6E,0x69,0x6E,0x67,0x21,0x0D,0x0A}; 

// 操作系统定时器中断初始化
void OSInitTick(void)
{
    /*** 每个Tick会触发一次定时器中断，根据每秒有多少个Tick计算定时器的计数值 ***/
    INT32U timer_cnt = (INT32U)(IN_CLK / OS_TICKS_PER_SEC);
    /*** 设置Status寄存器，使能定时器中断 ***/
    asm volatile("mtc0   %0,$12"   : :"r"(0x10000401));
    
    /*** 初始化定时器，加载计数值 ***/
    timer_init(TIMER_TCSR0, 1);
    timer_load(TIMER_TLR0, timer_cnt);
    uart_print("Timer initialization done ! \r\n", 30);
    
    /*** 启动定时器 ***/
    timer_start(TIMER_TCSR0);
    return; 
}
// 操作系统启动任务，打印一串字符串
void  TaskStart (void *pdata)
{	
    INT32U count = 0;
    pdata = pdata;          
    OSInitTick();     
    for (;;) {
       if(count < 19)
        {
            uart_sendByte(Info[count]);
        }
        count=count+1;
        OSTimeDly(10);
    }
}

// 单色LED灯和三色LED灯显示任务
void TaskGpio(void *pdata) {
    pdata = pdata;          
    for(;;) {
        display_led(0xF0F0);
        display_rgb(GREEN, RED);
        OSTimeDly(1000);      // 延迟1000ms
        display_led(0x0F0F);
        display_rgb(RED, GREEN);
        OSTimeDly(1000);      // 延迟1000ms
    }
}

// 七段数码管显示任务
void Taskx7Seg(void *pdata) {
    pdata = pdata;                                

    INT32U mask = 0xf;
    INT32U n0;
    int i, j;
    INT32U count = 0, seconds = 0;
	while(1) {
		INT32U tmp = count;
        	for(i = 0; i < 8; i ++) {
            		n0 = tmp & mask;
            		tmp = tmp >> 4;
	    		REG8(X7SEG_BASE + X7SEG_DISP_DATA) = x7seg_disp[n0];
            		REG8(X7SEG_BASE + X7SEG_AN_DATA) = x7seg_an[i];
            		seconds = seconds + 1;
            		OSTimeDly(1);  // 循环扫描7段数码管
        	}
        	if(seconds == 1000) {
            		count = count + 1;
            		seconds = 0;
        	}
	}
}

void main()
{
    OSInit();
    uart_init();
    uart_print("UART initialization done ! \r\n", 29);
    // gpio_init();
    // uart_print("GPIO initialization done ! \r\n", 29);	
    // OSTaskCreate(TaskStart, (void *)0, &TaskStartStk[TASK_STK_SIZE - 1], 0);
    // OSTaskCreate(TaskGpio, (void *)0, &TaskGpioStk[TASK_STK_SIZE - 1], 1);
    // OSTaskCreate(Taskx7Seg, (void *)0x0, &Taskx7SegStk[TASK_STK_SIZE - 1], 2);
    // OSStart();  
    return;
}
