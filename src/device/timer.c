#include "common.h"
#include "x86/x86.h"
#include "device/timer.h"

/* 8253输入频率为1.193182MHz */
#define TIMER_PORT 0x40
#define FREQ_8253 1193182

void
init_timer(void) {
	int counter = FREQ_8253 / HZ;
	assert(counter < 65536);
	out_byte(TIMER_PORT + 3, 0x34);
	out_byte(TIMER_PORT + 0, counter % 256);
	out_byte(TIMER_PORT + 0, counter / 256);
}
