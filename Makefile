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
ASSETS	   := assets
BUILD      := build
RAYLIB_SRC := vendor/raylib/src
RAYLIB_OUT := $(BUILD)/raylib
RAYLIB_LIB := $(RAYLIB_OUT)/libraylib.a
 
# recursive wildcard: $(call rwildcard,dir/,pattern)
rwildcard = $(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

SRCS := $(call rwildcard,$(SRC_DIR),*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD)/obj/%.o)
DEPS := $(OBJS:.o=.d)

# IMPORTANT: for zed to see the libs add them to compile_flags.txt
CFLAGS := -std=c2x -Wall -Wextra -g -I$(SRC_DIR) -I$(RAYLIB_SRC) -Ivendor/stb -MMD -MP

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

.PHONY: all run clean distclean assets dist

all: $(BIN) assets

$(BIN): $(OBJS) $(RAYLIB_LIB)
	$(CC) $(OBJS) $(RAYLIB_LIB) $(LDLIBS) -o $@

$(BUILD)/obj/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(RAYLIB_LIB):
	@mkdir -p $(RAYLIB_OUT)
	$(MAKE) -C $(RAYLIB_SRC) PLATFORM=PLATFORM_DESKTOP RAYLIB_RELEASE_PATH=$(abspath $(RAYLIB_OUT))

assets:
	@mkdir -p $(BUILD)/assets
	cp -R $(ASSETS)/. $(BUILD)/assets/
	
run: all
	cd $(BUILD) && ./$(TARGET)$(EXE)

# clean only your code; distclean also rebuilds raylib next time
clean:
	rm -rf $(BUILD)/obj $(BIN)

distclean:
	rm -rf $(BUILD)
	$(MAKE) -C $(RAYLIB_SRC) clean

dist:
	cd $(BUILD) && zip -r ../$(TARGET)-$(PLATFORM_OS).zip $(TARGET)$(EXE) assets
	
-include $(DEPS)

# ------------------------------------------------------------------
# Targets
# ------------------------------------------------------------------
# make            Build the game and copy assets/ into build/
# make run        Build, then run the game
# make assets     Copy assets/ into build/assets/
# make dist       Build, then zip the game and assets into game-<OS>.zip
# make clean      Remove your object files and the executable (keeps compiled raylib)
# make distclean  Remove build/ and the zip, and clean raylib (next build recompiles raylib)
#
# RELEASE=1       Optimised build, e.g. `make dist RELEASE=1`. Run `make clean` when switching.
#
# Notes
# - On Windows, run make in the MinGW shell (MSYS2 / w64devkit)
# - Upgrade raylib: git -C vendor/raylib fetch --tags && git -C vendor/raylib checkout 6.2, then make distclean && make
# ------------------------------------------------------------------
