BIN = main
CC  = gcc

WARNINGS = -Wall -Wextra -Wshadow -Wfloat-equal -Wpointer-arith \
	-Wstrict-overflow=5 -Werror-implicit-function-declaration   \
	-Wno-missing-braces -Wdouble-promotion -Wno-unused-parameter
CFLAGS   = -std=c11 -O0 -g -I. $(WARNINGS) -DDEBUGGING
LINKER   = gcc -o
LFLAGS   = -Wall -L./lib
DEPFLAGS = -MT $@ -MMD -MP -MF $(OBJDIR)/$*.dep

SRCDIR = ./
OBJDIR = ./obj

SRC := $(wildcard $(SRCDIR)/maths/*.c)    \
       $(wildcard $(SRCDIR)/util/*.c)     \
       $(wildcard $(SRCDIR)/graphics/*.c) \
       $(wildcard $(SRCDIR)/*.c)
OBJ := $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
LIB := -lm -lSDL2 -lSDL2_image -lGL -lGLEW -DGLEW_STATIC -lopenblas -lSOIL2
DEP := $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.dep)

PRECOMPILE  = mkdir -p $(@D)
POSTCOMPILE = 

all: $(BIN)
debug: all
	gdb ./main

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

.PHONEY: clean
clean:
	@rm -f $(OBJ)
	@echo "Cleanup complete"

.PHONEY: remove
remove:	clean
	@rm -f $(BIN)
	@echo "Executable removed"
	@rm -f $(DEP)
	@echo "Dependency files removed"

.PHONEY: game
game: all
	./$(BIN)
