BASE_DIR := $(shell realpath ..)
SRC_DIR := $(shell realpath $(CURDIR))
BUILD_DIR := $(SRC_DIR)/build
RESOURCES_DIR := $(BASE_DIR)/resources

# Bring in the color coding for nicer looking builds
-include $(RESOURCES_DIR)/colors.mk

CFLAGS := -Wall -Werror -std=c11
CPPFLAGS := -I$(SRC_DIR)
CPPFLAGS := -I$(BASE_DIR)/include
CPPFLAGS += -D_POSIX_C_SOURCE=200809L

# Sources stored in _this_ directory
SRCS := ReadFile.c
SRCS += CliParse.c

OBJS := $(SRCS:%.c=$(BUILD_DIR)/%.o)

all: _build_dir $(OBJS)

$(BUILD_DIR)/%.o: %.c
	@printf "Building $(OBJ_COLOR)$(@F)$(NO_COLOR) from $(SRC_COLOR)$(<F)$(NO_COLOR)\n"
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

_build_dir: |$(BUILD_DIR)
$(BUILD_DIR):
	mkdir -p $@

.PHONY: clean
clean:
	@printf "Cleaning up build cruft\n"
	$(RM) -r $(BUILD_DIR)

$(V).SILENT:
