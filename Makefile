GIT_TOP := $(shell git rev-parse --show-toplevel)
SRC_DIR := src
BUILD_DIR := build

VPATH = $(SRC_DIR)

.PHONY: debug release tss clean

# In the below, I am purposefully using make instead of $(MAKE) as the intention is for
# a completely new instance of make to perform the build.

all: npm
npm:
	@echo Building in src
	make -C src

clean:
	@echo Cleaning up the build cruft
	$(RM) -r $(BUILD_DIR)

$(V).SILENT:
