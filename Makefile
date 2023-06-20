TARGET = alpha.elf

CROSS_COMPILE =

CC = $(CROSS_COMPILE)gcc

OBJS = gba.o memory.o sound.o system.o sound_output.o core.o input.o \
	font_drawing.o menu.o scaler.o video_blit.o memalign.o

VPATH = ./src

CFLAGS = -Iinclude -Ofast -flto -fno-common -Wall -std=gnu++11 \
	-DLSB_FIRST -DINLINE="inline" -DWANT_16BPP -DFRONTEND_SUPPORTS_RGB565 \
	-DNDEBUG -DWANT_STEREO_SOUND -DVIRTUAL_SURFACE  \
	`/usr/bin/sdl-config --cflags`

ASFLAGS = 

LDFLAGS = -Ofast -flto=4 -fwhole-program -fuse-linker-plugin \
	  -fdata-sections -ffunction-sections \
	  -fno-stack-protector -fomit-frame-pointer\
	  -falign-functions=1 -falign-jumps=1 -falign-loops=1 \
	  -fno-unwind-tables -fno-asynchronous-unwind-tables -fno-unroll-loops -fmerge-all-constants \
	  -lc -lgcc -lm -lSDL -lasound -lz -pthread -flto -Wl,--as-needed -Wl,--gc-sections 

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@
	@echo Done!!!

%.o: %.S
	$(CC) $(ASFLAGS) -c $< -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)