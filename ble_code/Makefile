# List all source files to be compiled; separate with space
SOURCE_FILES := main.c

# Feel free to ignore anything below this line
FAMILY := nrf51

BUILD_DIR := build
LINKER_SCRIPT := $(BUILD_DIR)/linker_script.ld

OBJECT_FILES := $(SOURCE_FILES:%.c=$(BUILD_DIR)/%.o)
OBJECT_FILES += $(BUILD_DIR)/gcc_startup_nrf51.o
OBJECT_FILES += $(BUILD_DIR)/system_nrf51.o

GNU_PREFIX	:= arm-none-eabi
CC			:= $(GNU_PREFIX)-gcc
OBJCOPY		:= $(GNU_PREFIX)-objcopy
OBJDUMP		:= $(GNU_PREFIX)-objdump

CFLAGS += -mcpu=cortex-m0 -mthumb -mabi=aapcs -mfloat-abi=soft
CFLAGS += -ffunction-sections -fdata-sections --short-enums
CFLAGS += -fno-strict-aliasing -fno-builtin
CFLAGS += -Wall -Werror -std=gnu99

LFLAGS := --specs=nosys.specs -Wl,--gc-sections -T $(LINKER_SCRIPT)

.DEFAULT_GOAL := $(BUILD_DIR)/main.hex

$(BUILD_DIR)/gcc_startup_nrf51.o: $(BUILD_DIR)/gcc_startup_nrf51.S
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/system_nrf51.o: $(BUILD_DIR)/system_nrf51.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/main.hex: $(OBJECT_FILES)
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJECT_FILES) -o $(BUILD_DIR)/main.elf
	$(OBJCOPY) -O ihex $(BUILD_DIR)/main.elf $(BUILD_DIR)/main.hex

.PHONY: flash
flash: $(BUILD_DIR)/main.hex
	nrfjprog -f $(FAMILY) --chiperase --program $(BUILD_DIR)/main.hex
	nrfjprog -f $(FAMILY) --reset

.PHONY: erase
erase:
	nrfjprog -f $(FAMILY) --eraseall

.PHONY: clean
clean:
	rm $(OBJECT_FILES)
	rm $(BUILD_DIR)/main.{elf,hex}
