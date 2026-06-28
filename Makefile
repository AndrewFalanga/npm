GIT_TOP := $(shell git rev-parse --show-toplevel)
SRC_DIR := src
BUILD_DIR := build

VPATH = $(SRC_DIR)

.PHONY: npm tests runtests clean

# In the below, I am purposefully using make instead of $(MAKE) as the intention is for
# a completely new instance of make to perform the build.

all: npm
npm:
	@echo Building in src
	make -C src

tests:
	@echo Building tests for npm
	make -C src/test
	@echo Builidng interface tests
	@echo ... they do not yet exist

runtests:
	@echo Running tests
	make -C src/test runtest

clean:
	@echo Cleaning up the build cruft
	$(RM) -r $(BUILD_DIR)
	make -C src/test $@

$(V).SILENT:
