#include "common.h"

/* implement this function to support printk */
void vfprintf(void (*printer)(char), const char *ctl, void **args) {
	const char *str = __FUNCTION__;
	for(;*str != '\0'; str ++) printer(*str);

	str = ": vfprintf() is not implemented!\n";
	for(;*str != '\0'; str ++) printer(*str);
}

extern void serial_printc(char);

/* __attribute__((__noinline__))  here is to disable inlining for this function to avoid some optimization problems for gcc 4.7 */
void __attribute__((__noinline__)) 
printk(const char *ctl, ...) {
	void **args = (void **)&ctl + 1;
	vfprintf(serial_printc, ctl, args);
}
