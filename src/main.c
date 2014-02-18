#include "game.h"
#include "irq.h"
#include "x86/x86.h"
#include "device/timer.h"
#include "device/palette.h"
#include "assert.h"

void
game_init(void) {
	init_serial();
	init_timer();
	init_idt();
	init_intr();
	set_timer_intr_handler(timer_event);
	set_keyboard_intr_handler(keyboard_event);

	printk("game start!\n");
	enable_interrupt();
	main_loop();
	assert(0); /* main_loop是死循环，永远无法返回这里 */
}
