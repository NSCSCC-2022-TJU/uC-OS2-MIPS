typedef unsigned  char              BOOLEAN;
typedef unsigned  char              INT8U;        
typedef signed    char              INT8S;        
typedef unsigned  short             INT16U;       
typedef signed    short             INT16S;       
typedef unsigned  int               INT32U;       
typedef signed    int               INT32S;

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define REG8(add) *((volatile INT8U *)(add))
#define REG16(add) *((volatile INT16U *)(add))
#define REG32(add) *((volatile INT32U *)(add))

// 定义时钟频率
#define IN_CLK 50000000

// axi_gpio_0控制器基地址和偏移地址
#define LED_BASE        	0xBFD00000
#define LED_DATA        	0x00000000
#define LED_TRI         	0x00000004
#define RGB_DATA        	0x00000008
#define RGB_TRI         	0x0000000c

// axi_gpio_1控制器基地址和偏移地址
#define X7SEG_BASE        	0xBFD01000
#define X7SEG_DISP_DATA     	0x00000000
#define X7SEG_DISP_TRI      	0x00000004
#define X7SEG_AN_DATA   	0x00000008
#define X7SEG_AN_TRI    	0x0000000c

// axi uartlite控制器基地址和偏移地址
#define UART_BASE		0xBFD10000
#define UART_RX			0x00000000	
#define UART_RT			0x00000004	
#define UART_STAT		0x00000008	
#define UART_CTRL		0x0000000c

// axi timer控制器基地址和偏移地址
#define TIMER_BASE        	0xBFD30000
#define TIMER_TCSR0       	0x00000000
#define TIMER_TLR0        	0x00000004
#define TIMER_TCR0        	0x00000008
#define TIMER_TCSR1       	0x00000010
#define TIMER_TLR1        	0x00000014
#define TIMER_TCR1        	0x00000018

// 显存VRAM的基地址
#define VRAM_ADDR           	0xB0000000

// axi vga控制器基地址和偏移地址
#define VGA_BASE     		0xBFD40000
#define VGA_CTRL     		0x00000000
#define VGA_IMPOINT     	0x00000004
#define VGA_IMSIZE     		0x00000008
#define VGA_BGCOLOR     	0x0000000c

/*#define DELAY_CNT 3000000

// 延迟函数
void delay(INT32U cnt) {
	INT32U i = 0;
	while(i < cnt) {
		i ++;
	}
}*/
