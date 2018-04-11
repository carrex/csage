BIN   = main
# STLIB = libcsage.a
# SHLIB = libcsage.so
CC    = gcc

WARNINGS = -Wall -Wextra -Wshadow -Wfloat-equal -Wpointer-arith  \
	-Wstrict-overflow=5 -Werror-implicit-function-declaration    \
	-Wno-missing-braces -Wdouble-promotion -Wno-unused-parameter
# -Wsuggest-attribute=[pure|const|noreturn|format|cold|malloc]
CFLAGS   = -std=c11 -O0 -g -I. $(WARNINGS) -DDEBUGGING
NIMFLAGS = -std=gnu11 -O0 -I. -I./nimcache -I/home/charles/.choosenim/toolchains/nim-0.18.0/lib
CFLAGS  += $(NIMFLAGS)

LINKER   = gcc -o
LFLAGS   = -Wall -L./lib
DEPFLAGS = -MT $@ -MMD -MP -MF $(OBJDIR)/$*.dep
# STFLAGS  = -static-libgcc -static
# SHFLAGS  = -fPIC

SRCDIR = ./
OBJDIR = ./obj

SRC := $(wildcard $(SRCDIR)/nimcache/*.c) \
       $(wildcard $(SRCDIR)/maths/*.c)    \
       $(wildcard $(SRCDIR)/util/*.c)     \
       $(wildcard $(SRCDIR)/graphics/*.c) \
       $(wildcard $(SRCDIR)/*.c)
OBJ := $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
LIB := -lc -ldl -lm -pthread -lSDL2 -lGL -lGLEW -DGLEW_STATIC -lOpenBLAS -lSOIL2
DEP := $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.dep)

PRECOMPILE  = mkdir -p $(@D)
POSTCOMPILE = 

all: $(BIN)

# static: CFLAGS += $(STFLAGS)
# static: $(OBJ)
# 	@ar rcs libcsage.a $(OBJ)
# shared: CFLAGS += $(SHFLAGS)
# shared: $(OBJ)
# 	@$(CC) $(OBJ) -shared -o $(SHLIB)

$(BIN): $(OBJ)
	@$(LINKER) $@ $(LFLAGS) $(OBJ) $(LIB)
	@echo "Linking complete"

$(OBJ): $(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(PRECOMPILE)
	@$(CC) $(DEPFLAGS) $(CFLAGS) -c $< -o $@
	@$(POSTCOMPILE)
	@echo "Compiled "$<" successfully"

-include $(DEP)
$(DEP): $(SRC)
	@$(CC) $(CFLAGS) $< -MM -MT $(@:.dep=.o) > $@

.PHONEY: debug
debug: all
	gdb ./main

.PHONEY: val
val: all
	valgrind ./main --leck-check=full

.PHONEY: nim
nim: 
	@nim c --noMain --noLinking --parallelBuild:4 --header:game.h game.nim
	@echo "Nim compiled successfully"
	@make -j 4 game

.PHONEY: clean
clean:
	@rm -f $(OBJ)
	@echo "Cleanup complete"

.PHONEY: remove
remove:	clean
	@rm -f $(BIN)
	@echo "Executable removed"
	@rm -f $(SLIB)
	@echo "Shared library removed"
	@rm -f $(DEP)
	@echo "Dependency files removed"

.PHONEY: game
game: all
	./$(BIN)
