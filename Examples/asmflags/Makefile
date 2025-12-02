NASM = nasm
NASMFLAGS = -f elf -dOS_LINUX -g

SOURCES = flags.asm hex2num.asm strlen.asm putstr.asm quit.asm \
	flagshow.asm num2hex.asm
OBJECTS = $(SOURCES:.asm=.o)


%.o:	%.asm
	$(NASM) $(NASMFLAGS) $< -o $@

prog:	$(OBJECTS)
	$(LD) -m elf_i386 $^ -o $@


clean:
	rm -f $(OBJECTS) prog a.out core
