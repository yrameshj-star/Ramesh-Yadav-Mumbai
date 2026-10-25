CC     = xc8-cc
DEVICE = 16F877A
OUT    = build

all: $(OUT)/main.hex

$(OUT)/main.hex: main.c
	mkdir -p $(OUT)
	$(CC) -mcpu=$(DEVICE) -O2 -o $(OUT)/main.elf main.c

clean:
	rm -rf $(OUT)

.PHONY: all clean
