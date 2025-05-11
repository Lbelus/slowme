TARGET_EXEC := fc_curl
cc := clang
BUILD_DIR := ./build
SRC_DIRS := ./src

# https://www.gnu.org/software/make/manual/html_node/Setting.html
export C_INCLUDE_PATH=include/

DEBUG ?= 0

# Compiler and linker flags
WARNINGS := -Wall -Wextra -Werror
DEBUG_FLAGS := -fsanitize=address -g
RELEASE_FLAGS := -O2

ifeq ($(DEBUG), 1)
    CFLAGS := $(WARNINGS) $(DEBUG_FLAGS)
    LDFLAGS := $(DEBUG_FLAGS) -lssl -lcrypto `pkg-config --libs criterion`
    BIN_NAME := debug
else
    CFLAGS := $(RELEASE_FLAGS)
    LDFLAGS := -lssl -lcrypto
    BIN_NAME := $(TARGET_EXEC)
endif

.PHONY: all clean fclean debug debugc


# Find all the C files we want to compile
# Note the single quotes around the * expressions. Make will incorrectly expand these otherwise.
SRCS := $(shell find $(SRC_DIRS) -name '*.c')

# SRCS := $(filter-out $(SRC_DIRS)/curlapimodule.c, $(SRCS))
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# As an example, ./build/hello.c.o turns into ./build/hello.c.d
DEPS := $(OBJS:.o=.d)

# Every folder in ./src will need to be passed to GCC so that it can find header files
INC_DIRS := $(shell find $(SRC_DIRS) -type d)

# Add a prefix to INC_DIRS. So moduleA would become -ImoduleA. GCC understands this -I flag
INC_FLAGS := $(addprefix -IC,$(INC_DIRS))

# The -MMD and -MP flags together generate Makefiles for us!
# These files will have .d instead of .o as the output.
XTRAFLAGS := $(INC_FLAGS) -g -MMD -MP

.PHONY: all clean fclean debug debugc
# ---------------

# It's the final build step dumdum du.
$(BUILD_DIR)/$(BIN_NAME): $(OBJS)
	$(cc) $(OBJS) -o $@ $(LDFLAGS)
	cp $@ ./

# Build step for C source
$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(cc) $(CFLAGS) $(XTRAFLAGS) -c $< -o $@
# ---------------

clean:
	rm -f $(OBJS) $(DEPS)
	rm -f $(BUILD_DIR)/$(TARGET_EXEC) $(BUILD_DIR)
	rm -f $(TARGET_EXEC) debug

fclean:
	rm -rf $(BUILD_DIR)
	rm -f $(TARGET_EXEC) debug

debug:
	$(MAKE) DEBUG=1

debugc:
	rm -f debug
	rm -f $(BUILD_DIR)

# Include the .d makefiles. The - at the front suppresses the errors of missing
# Makefiles. Initially, all the .d files will be missing, and we don't want those
# errors to show up.
-include $(DEPS)

# Thanks to Job Vranish (https://spin.atomicobject.com/2016/08/26/makefile-c-projects/)
