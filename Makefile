TARGET = main
CC     = gcc

WARNINGS = -Wall -Wextra -Wshadow -Wfloat-equal -Wpointer-arith \
	-Wstrict-overflow=5 -Werror-implicit-function-declaration \
	-Wno-missing-braces -Wdouble-promotion
CFLAGS   = -std=c11 -O3 -g -I. $(WARNINGS) -DDEBUGGING

LINKER = gcc -o
LFLAGS = -Wall -I. -lm

SRCDIR  = ./
OBJDIR  = obj

SOURCES  := $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/*/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h) 
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
LIBS     := -lSDL2 -lSDL2_image -lGL -lGLEW -DGLEW_STATIC -lopenblas
# -lX11 -lpthread -lXrandr -lXi

all: $(TARGET)
debug: CFLAGS += -O0 -g3 -ggdb -fvar-tracking
debug: remove all
strict: CFLAGS += -std=c99 -pedantic -Wunreachable-code -Wconversion -Wstrict-prototypes -Wno-unused-parameter -Wno-empty-body -UDEBUGGING
strict: remove all

$(TARGET): $(OBJECTS)
	@$(LINKER) $@ $(LFLAGS) $(OBJECTS) $(LIBS)
	@echo "Linking complete"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully"

.PHONEY: clean
clean:
	@rm -f $(OBJECTS)
	@echo "Cleanup complete"

.PHONEY: remove
remove:	clean
	@rm -f  $(TARGET)
	@rm -rf $(OBJDIR)
	@echo "Executable removed"

.PHONEY: game
game: all
	./$(TARGET)

.PHONEY: gameall
gameall: remove all
	./$(TARGET)
# TARGET = main
# CC     = gcc

# WARNINGS = -Wall -Wextra -Wshadow -Wfloat-equal -Wpointer-arith \
# 	-Wstrict-overflow=5 -Werror-implicit-function-declaration \
# 	-Wno-missing-braces -Wdouble-promotion
# CFLAGS   = -std=c11 -O3 -g -I. $(WARNINGS) -DDEBUGGING

# LINKER = gcc -o
# LFLAGS = -Wall -I. -lm

# SRCDIR  = ./
# OBJDIR  = obj

# SOURCES  := $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/*/*.c)
# INCLUDES := $(wildcard $(SRCDIR)/*.h) 
# OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
# LIBS     := -lSDL2 -lSDL2_image -lGL -lGLEW -DGLEW_STATIC -lblas
# # -lX11 -lpthread -lXrandr -lXi

# all: $(TARGET)
# debug: CFLAGS += -O0 -g3 -ggdb -fvar-tracking
# debug: remove all
# strict: CFLAGS += -std=c99 -pedantic -Wunreachable-code -Wconversion -Wstrict-prototypes -Wno-unused-parameter -Wno-empty-body -UDEBUGGING
# strict: remove all

# $(TARGET): $(OBJECTS)
# 	@$(LINKER) $@ $(LFLAGS) $(OBJECTS) $(LIBS)
# 	@echo "Linking complete"

# $(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
# 	@mkdir -p $(@D)
# 	@$(CC) $(CFLAGS) -c $< -o $@
# 	@echo "Compiled "$<" successfully"

# .PHONEY: clean
# clean:
# 	@rm -f $(OBJECTS)
# 	@echo "Cleanup complete"

# .PHONEY: remove
# remove:	clean
# 	@rm -f  $(TARGET)
# 	@rm -rf $(OBJDIR)
# 	@echo "Executable removed"

# .PHONEY: game
# game: all
# 	./$(TARGET)

# .PHONEY: gameall
# gameall: remove all
# 	./$(TARGET)
