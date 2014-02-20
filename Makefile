# GNU make手册：http://www.gnu.org/software/make/manual/make.html
# ************ 遇到不明白的地方请google以及阅读手册 *************

# 编译器设定和编译选项
CC = gcc
LD = ld
CFLAGS = -m32 -static -MD -std=gnu89 -ggdb \
		 -fno-builtin -fno-stack-protector -fno-omit-frame-pointer \
		 -Wall -Werror -O2 -I./include
ASFLAGS = -m32 -MD
LDFLAGS = -melf_i386
QEMU = qemu-system-i386

# 编译目标：src目录下的所有.c和.S文件
CFILES = $(shell find src/ -name "*.c")
SFILES = $(shell find src/ -name "*.S")
OBJS = $(CFILES:.c=.o) $(SFILES:.S=.o)

game.img: game
	@cd boot; make
	cat boot/bootblock game > game.img

game: $(OBJS)
	$(LD) $(LDFLAGS) -e game_init -Ttext 0x00100000 -o game $(OBJS)

-include $(patsubst %.o, %.d, $(OBJS))

# 定义的一些伪目标
.PHONY: play clean debug

# 如果make play运行失败，请检查qemu的安装
# 也可以修改这里的脚本，用其他类型的模拟器启动game.img
play: game.img
	$(QEMU) -serial stdio game.img
debug: game.img
	$(QEMU) -serial stdio -s -S game.img

# make clean可以清除已生成的文件
clean:
	@cd boot; make clean
	rm -f game game.img $(OBJS) $(OBJS:.o=.d)
