# ---- OS detection ----
ifeq ($(OS),Windows_NT)
    PLATFORM_OS := WINDOWS
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Darwin)
        PLATFORM_OS := OSX
    else
        PLATFORM_OS := LINUX
	endif
endif

TARGET     := game
SRC_DIR    := src
BUILD      := build
RAYLIB_SRC := vendor/raylib/src
RAYLIB_OUT := $(BUILD)/raylib
RAYLIB_LIB := $(RAYLIB_OUT)/libraylib.a

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD)/obj/%.o)
DEPS := $(OBJS:.o=.d)

# IMPORTANT: for zed to see the libs add them to compile_flags.txt
CFLAGS := -std=c2x -Wall -Wextra -g -I$(RAYLIB_SRC) -Ivendor/stb -MMD -MP

ifeq ($(PLATFORM_OS),WINDOWS)
    CC     := gcc
    EXE    := .exe
    LDLIBS := -lopengl32 -lgdi32 -lwinmm
else ifeq ($(PLATFORM_OS),OSX)
    CC     := clang
    LDLIBS := -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -framework CoreAudio
else
    CC     := gcc
    LDLIBS := -lGL -lm -lpthread -ldl -lrt -lX11
endif

BIN := $(BUILD)/$(TARGET)$(EXE)

.PHONY: all run clean distclean

all: $(BIN)

$(BIN): $(OBJS) $(RAYLIB_LIB)
	$(CC) $(OBJS) $(RAYLIB_LIB) $(LDLIBS) -o $@

$(BUILD)/obj/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(RAYLIB_LIB):
	@mkdir -p $(RAYLIB_OUT)
	$(MAKE) -C $(RAYLIB_SRC) PLATFORM=PLATFORM_DESKTOP RAYLIB_RELEASE_PATH=$(abspath $(RAYLIB_OUT))

run: $(BIN)
	./$(BIN)

# clean only your code; distclean also rebuilds raylib next time
clean:
	rm -rf $(BUILD)/obj $(BIN)

distclean:
	rm -rf $(BUILD)
	$(MAKE) -C $(RAYLIB_SRC) clean

-include $(DEPS)

# ------------------------------------------------------------------
# Targets
# ------------------------------------------------------------------
# make            Build the game (same as `make all`). Builds raylib first if build/raylib/libraylib.a is missing.
# make run        Build if needed, then run the game.
# make clean      Remove your object files and the executable. Keeps the compiled raylib, so the next build is fast.
# make distclean  Remove all of build/ (including libraylib.a) and run raylib's own clean in vendor/raylib/src. The next build recompiles raylib.
#
# Never touched by any target: vendor/raylib (the submodule source) and vendor/stb.
#
# Notes
# - The OS is detected automatically (Linux / macOS / Windows via MSYS2 or w64devkit). On Windows, run make from that shell, not cmd.exe.
# - Header changes trigger rebuilds of the files that include them (via -MMD -MP and the generated .d files).
# - To upgrade raylib: git -C vendor/raylib fetch --tags && git -C vendor/raylib checkout 6.2, then make distclean && make
# ------------------------------------------------------------------
