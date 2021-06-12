CC = riscv64-unknown-elf-gcc
CFLAGS = -fno-builtin -mcmodel=medany -march=rv32ima -mabi=ilp32
CFLAGS += -nostdlib

QEMU = qemu-system-riscv32
QFLAGS = -nographic -smp 4 -machine virt -bios none

OBJDUMP = riscv64-unknown-elf-objdump

all: clean os.elf qemu

QEMU = qemu-system-riscv32
QFLAGS = -nographic -smp 4 -machine virt -bios none
QFLAGS += -drive file=fs.img,if=none,format=raw,id=x0
QFLAGS += -device virtio-blk-device,drive=x0,bus=virtio-mmio-bus.0

os.elf: start.s sys.s lib.c timer.c task.c os.c user.c unistd.c disk.c string.c
	$(CC) $(CFLAGS) -T os.ld -o os.elf $^

qemu: $(TARGET) fs.img
	@qemu-system-riscv32 -M ? | grep virt >/dev/null || exit
	@echo "Press Ctrl-A and then X to exit QEMU"
	$(QEMU) $(QFLAGS) -kernel os.elf

fs.img:
	qemu-img create -f raw fs.img 500M

clean:
	rm -f *.elf
