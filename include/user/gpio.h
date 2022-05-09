#define RED				1
#define GREEN			2
#define BLUE			4	

#define _0			0b11000000
#define _1			0b11111001
#define _2			0b10100100
#define _3			0b10110000
#define _4			0b10011001
#define _5			0b10010010
#define _6			0b10000010
#define _7			0b11111000
#define _8			0b10000000
#define _9			0b10010000
#define _A			0b10001000
#define _B			0b10000011
#define _C			0b11000110
#define _D			0b10100001
#define _E			0b10000110
#define _F			0b10001110

#define SCAN_FREQ 3000   // 循环扫描频率
#define SCAN_CNT  100    // 循环扫描次数

INT32U x7seg_an[]   = {0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F};
INT32U x7seg_disp[] = {_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _A, _B, _C, _D, _E, _F};

// GPIO初始化
void gpio_init()
{
	REG32(LED_BASE + LED_TRI)        = 0x00000000;
	REG32(LED_BASE + RGB_TRI)        = 0x00000000;
	REG32(X7SEG_BASE + X7SEG_DISP_TRI) = 0x00000000;
	REG32(X7SEG_BASE + X7SEG_AN_TRI)   = 0x00000000;
}

// 单色LED灯显示
void display_led(INT16U led)
{
	REG16(LED_BASE + LED_DATA) = led;
}

// 三色LED灯显示
void display_rgb(INT8U rgb1, INT8U rgb2)
{
	REG16(LED_BASE + RGB_DATA) = ((rgb1 << 3) | rgb2);
}

// 七段数码管动态扫描显示
/*void display_seg(INT32U num) {
	INT32U bit_mask = 0xF;
	INT32U an, disp;
	// 7段数码管循环扫描
        for(an = 0; an < 8; an++) {
	      disp = num & bit_mask;
	      num = num >> 4;
	      REG8(X7SEG_BASE + X7SEG_DISP_DATA) = x7seg_disp[disp];
	      REG8(X7SEG_BASE + X7SEG_AN_DATA) = x7seg_an[an];
	      delay(SCAN_FREQ);
        }
}*/
