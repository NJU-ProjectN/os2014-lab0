static int seed = 0;

void
srand(int s) {
	seed = s;
}

/* 生成下一个随机数 */
int
rand(void) {
	seed = 0x015A4E35 * seed + 1;
	return (seed >> 16) & 0x7FFF;
}

