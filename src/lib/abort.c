#include "common.h"
#include "x86/x86.h"
#include "device/video.h"
#include "string.h"

static void
append(char **p, const char *str) {
	while (*str) {
		*((*p) ++) = *str ++;
	}
}

/* 将文件名和assert fail的行号显示在屏幕上 */
#define BLUE_SCREEN_TEXT "Assertion failed: "
static void
blue_screen(const char *file, int line) {
	static char buf[256] = BLUE_SCREEN_TEXT;
	char *p = buf + sizeof(BLUE_SCREEN_TEXT) - 1;

	append(&p, file);
	append(&p, ":");
	append(&p, itoa(line));

	prepare_buffer();
	memset(vmem, 1, SCR_SIZE);
	draw_string(buf, 0, 0, 15);
	display_buffer();
}

int
abort(const char *fname, int line) {
	/* 当程序遇到不可恢复的错误时，首先将外部中断关闭以防其他错误发生，
     * 然后显示出错信息后，等待下一个中断到来(实际永远等不到)。*/
	disable_interrupt();
	blue_screen(fname, line);
	while (TRUE) {
		wait_for_interrupt();
	}
}
