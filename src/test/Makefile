ROOT_DIR := $(realpath ../..)
TEST_BUILD := $(CURDIR)/build
RESOURCES_DIR := $(ROOT_DIR)/resources

INCLUDE_DIR := $(ROOT_DIR)/include
OS_NAME := $(shell uname)

-include $(RESOURCES_DIR)/colors.mk

TEST_FILE_SRC := test.file.txt
TEST_FILE_NAME = $(TEST_BUILD)/$(TEST_FILE_SRC)
TEST_TEXT_HEADER = $(TEST_BUILD)/test_file.h

ifeq ($(OS_NAME),Darwin)
GTEST_VERSION = $(shell brew info googletest | perl -ne 'print "$$1" if /stable (\d{1,}\.\d{1,}\.\d{1,})/')
GTEST_ROOT = /opt/homebrew/Cellar/googletest/$(GTEST_VERSION)
INCLUDE_DIR += $(GTEST_ROOT)/include
endif

INCLUDE_DIR += $(TEST_BUILD)

TEST_SRCS := test_ReadFile.cpp
TEST_SRCS += main.cpp

SRCS := ReadFile.c

OBJS := $(TEST_SRCS:%.cpp=$(TEST_BUILD)/%.o)
OBJS += $(SRCS:%.c=$(TEST_BUILD)/%.o)

CPPFLAGS += $(addprefix -I,$(INCLUDE_DIR))
CPPFLAGS += -D_POSIX_C_SOURCE=200809L
CXXFLAGS += -std=c++17

TEST_BIN := $(TEST_BUILD)/gtest

VPATH += $(ROOT_DIR)/src

.PHONY: tests
tests: _test_build _test_text_stuff $(OBJS) $(TEST_BIN)

.PHONY: _test_build
_test_build: | $(TEST_BUILD)
$(TEST_BUILD):
	@echo Making build dir
	mkdir -p $@

$(TEST_BUILD)/%.o: %.cpp
	@printf "Building $(OBJ_COLOR)$(@F)$(NO_COLOR) from $(SRC_COLOR)$(<F)$(NO_COLOR)\n"
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(CFLAGS) -c -o $@ $<

$(TEST_BUILD)/%.o: %.c
	@printf "Building $(OBJ_COLOR)$(@F)$(NO_COLOR) from $(SRC_COLOR)$(<F)$(NO_COLOR)\n"
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

$(TEST_BIN): $(OBJS)
	@printf "Building $(BIN_COLOR)$(@F)$(NO_COLOR) from $(OBJ_COLOR)$(notdir $^)$(NO_COLOR)\n"
	$(CXX) -o $@ $^ -L$(GTEST_ROOT)/lib -lgtest

.PHONY: runtest
runtest: $(TEST_BIN)
	@printf "Running $(BIN_COLOR)$(<F)$(NO_COLOR)\n"
	cd $(TEST_BUILD) && ./$(<F)

_test_text_stuff: $(TEST_TEXT_HEADER) $(TEST_FILE_NAME)
$(TEST_TEXT_HEADER): $(TEST_FILE_SRC)
	@printf "Building the header file for test\n"
	printf "%s\n%s\n%s\n" \
	        "#pragma once" \
	        "static const char *testFile = \"$<\";" \
	        "static const char *fileContents = \"$$(perl -pe 's/\n/\\n/g' $^)\";" > $@

$(TEST_FILE_NAME): $(TEST_FILE_SRC)
	@printf "Staging the test text file $(<F)\n"
	cp $< $@

.PHONY: clean
clean:
	$(RM) -r $(TEST_BUILD)

$(V).SILENT:
