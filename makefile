GCC_PATH = /Applications/ARM/bin

ifdef DEBUG
	NO_ECHO :=
else
	NO_ECHO := @
endif

CC      = $(GCC_PATH)/arm-none-eabi-gcc
LD      = $(GCC_PATH)/arm-none-eabi-ld
OCPY    = $(GCC_PATH)/arm-none-eabi-objcopy
ODUMP   = $(GCC_PATH)/arm-none-eabi-objdump
SZ      = $(GCC_PATH)/arm-none-eabi-size
MKDIR   = mkdir


CFLAGS +=   -nostdlib\
			-ffreestanding \
			-march=armv4t \
			-mtune=arm7tdmi \
			-mthumb-interwork \
			-ffunction-sections \
			-O1 \
			-fcaller-saves -fcode-hoisting  -fcrossjumping  -fcse-follow-jumps  -fcse-skip-blocks  -fdelete-null-pointer-checks  -fexpensive-optimizations  -ffinite-loops  -fgcse  -fgcse-lm   -fhoist-adjacent-loads  -finline-functions   -findirect-inlining  -fipa-bit-cp  -fipa-cp  -fipa-icf  -fipa-ra  -fipa-sra  -flra-remat  -foptimize-sibling-calls    -fpartial-inlining  -fpeephole2 -freorder-functions  -frerun-cse-after-loop      -fsched-interblock  -fsched-spec  -fstore-merging  -fstrict-aliasing   -ftree-builtin-call-dce   -ftree-pre -ftree-switch-conversion  -ftree-tail-merge  -ftree-vrp 

#-fdata-sections

LDFLAGS += -T cxd2680.ld #--just-symbols cxd2680v1.6.sym 
SRCS = firmware.c display.c button.c tetris.c main.c 
INCLUDES += ./

CFLAGS += $(foreach i,$(INCLUDES),-I$(i))
OBJS = $(patsubst %.c,build/objs/%.o,$(SRCS))
#CFLAGS += $(foreach d,$(DEFINES),-D$(d))

all: build/minitris.bin
	hexdump -v -e '"\\" "x" 1/1 "%02X"' build/minitris.bin
	wc -c build/minitris.bin

build:
	mkdir -p build

build/objs:
	mkdir -p build/objs/

build/objs/%.o: %.c build/objs
	@echo "Compiling $<"
	mkdir -p $(dir $@)
	$(CC) -c -o $@ $< $(CFLAGS)

build/minitris.bin: build/minitris.elf build/minitris.lst
	$(OCPY) $< $@ -O binary
	$(SZ) $<

build/minitris.lst: build/minitris.elf build
	$(ODUMP) -D $< > $@

build/minitris.elf: $(OBJS)
	@echo "Linking $@"
	$(LD) $^ $(LDFLAGS) -o $@

clean:
	rm -rf build/*