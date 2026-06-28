BASE_DIR := $(shell realpath ..)
BUILD_DIR := $(BASE_DIR)/build

CFLAGS := -Wall -Werror -std=c11
CPPFLAGS := -I$(BASE_DIR)/include
CPPFLAGS += -D_POSIX_C_SOURCE=200809L

# Sources stored in _this_ directory
SRCS := ReadFile.c

OBJS := $(SRCS:%.c=$(BUILD_DIR)/%.o)

$(info OBJS is $(OBJS))

all: _build_dir $(OBJS)

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

_build_dir: |$(BUILD_DIR)
$(BUILD_DIR):
	mkdir -p $@

.PHONY: clean
clean:
	$(RM) -r $(BUILD_DIR)

$(V).SILENT:
