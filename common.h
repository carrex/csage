#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdnoreturn.h>
#include <string.h>

#include <GL/glew.h>

#define GFX_DIR "./assets/gfx/"

enum Direction {
	DIR_NONE,
	DIR_RIGHT,
	DIR_LEFT,
	DIR_UP,
	DIR_DOWN,
	DIR_FORWARD,
	DIR_BACKWARD,
};

/*  +------------------------------------------+
 *  |           Integral Types Chart           |
 *  +----------+--------+----------------------+
 *  |   Type   |  Bits  |   Range (approx.)    |
 *  +----------+--------+----------------------+
 *  |     char |    8   |     +-127 || 0..255  |   
 *  |    short |   16   |  +-3.27e4 || 6.55e4  |
 *  |      int | 16-32* |  +-2.14e9 || 4.29e9  |
 *  |     long | 32*-64 |  +-2.14e9 || 4.29e9  |
 *  | longlong |   64   | +-9.22e18 || 1.84e19 |
 *  +----------+--------+----------------------+
 */
typedef  int8_t   int8 ;
typedef  int16_t  int16;
typedef  int32_t  int32;
typedef  int64_t  int64;
typedef uint8_t  uint8 ;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef unsigned int uint;
typedef  intptr_t  intptr;
typedef uintptr_t uintptr;
typedef ptrdiff_t ptrdiff;

typedef void (*VoidFn)(void);

#define SELECT1(_1, ...) (_1)

#define DEBUG_MALLOC_MIN 64

#define TERM_NORMAL  "\x1B[0m"
#define TERM_RED     "\x1B[31m"
#define TERM_GREEN   "\x1B[32m"
#define TERM_YELLOW  "\x1B[33m"
#define TERM_BLUE    "\x1B[34m"
#define TERM_MAGENTA "\x1B[35m"
#define TERM_CYAN    "\x1B[36m"
#define TERM_WHITE   "\x1B[37m"
#define DEBUG_COLOUR(str) (fprintf(stderr, !strncmp((str), "[INIT]" , 6)? TERM_WHITE  : \
                                           !strncmp((str), "[RES]"  , 5)? TERM_GREEN  : \
                                           !strncmp((str), "[GFX]"  , 5)? TERM_BLUE   : \
                                           !strncmp((str), "[MATHS]", 7)? TERM_YELLOW : \
                                           !strncmp((str), "[MEM]"  , 5)? TERM_MAGENTA: \
                                           TERM_NORMAL))

#ifdef DEBUGGING
	#define DEBUG(...) do {                           \
			if (SELECT1(__VA_ARGS__, "")[0]) {         \
				DEBUG_COLOUR(SELECT1(__VA_ARGS__, "")); \
				fprintf(stderr, __VA_ARGS__);            \
				fprintf(stderr, "\n" TERM_NORMAL);        \
			}\
		} while (0)
	#define ERROR(...) do {                               \
			fprintf(stderr, TERM_RED);                     \
			fprintf(stderr, __VA_ARGS__);                   \
			fprintf(stderr, "\n\t%s:%d in %s\n" TERM_NORMAL, \
				    __FILE__, __LINE__, __func__);            \
		} while (0)
	#define DEBUG_GL() do {                                                                 \
		GLenum err;                                                                         \
		while ((err = glGetError()) != GL_NO_ERROR) {                                       \
			fprintf(stderr, TERM_RED "[OGL] %s",                                            \
				err == GL_INVALID_ENUM                 ? "INVALID_ENUM"                 :   \
				err == GL_INVALID_VALUE                ? "INVALID_VALUE"                :   \
				err == GL_INVALID_OPERATION            ? "INVALID_OPERATION"            :   \
				err == GL_STACK_OVERFLOW               ? "STACK_OVERFLOW"               :   \
				err == GL_STACK_UNDERFLOW              ? "STACK_UNDERFLOW"              :   \
				err == GL_OUT_OF_MEMORY                ? "OUT_OF_MEMORY"                :   \
				err == GL_INVALID_FRAMEBUFFER_OPERATION? "INVALID_FRAMEBUFFER_OPERATION":   \
				"UNKNOWN ERROR");                                                           \
			fprintf(stderr, "\n\t%s:%d in %s\n" TERM_NORMAL, __FILE__, __LINE__, __func__); \
		}                                                                                   \
	} while (0)
#else
	#define DEBUG(...)
	#define ERROR(...)
	#define DEBUG_GL()
#endif

#define typename(x) (_Generic((x),                                                \
        _Bool: "_Bool",                  unsigned char: "unsigned char",          \
         char: "char",                     signed char: "signed char",            \
    short int: "short int",         unsigned short int: "unsigned short int",     \
          int: "int",                     unsigned int: "unsigned int",           \
     long int: "long int",           unsigned long int: "unsigned long int",      \
long long int: "long long int", unsigned long long int: "unsigned long long int", \
        float: "float",                         double: "double",                 \
  long double: "long double",                   char *: "pointer to char",        \
       void *: "pointer to void",                int *: "pointer to int",         \
      default: "other"))

/* * * * * Memory functions * * * * */
#define smalloc(x)    (_smalloc(x   , __FILE__, __LINE__, __func__))
#define scalloc(x, y) (_scalloc(x, y, __FILE__, __LINE__, __func__))

void* _smalloc(uintptr bytes, char* file, uint line, char const* func);
void* _scalloc(uintptr items, uintptr size, char* file, uint line, char const* func);

#endif
