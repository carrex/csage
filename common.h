#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include <GL/glew.h>

enum Direction {
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

static inline bool starts_with(char* str, char* start)
{
	for (uint8 i = 0; i < strlen(start); i++)
		if (str[i] != start[i])
			return false;
	return true;
}

#define SELECT1(_1, ...) _1

#define TERM_NORMAL  "\x1B[0m"
#define TERM_RED     "\x1B[31m"
#define TERM_GREEN   "\x1B[32m"
#define TERM_YELLOW  "\x1B[33m"
#define TERM_BLUE    "\x1B[34m"
#define TERM_MAGENTA "\x1B[35m"
#define TERM_CYAN    "\x1B[36m"
#define TERM_WHITE   "\x1B[37m"
#define DEBUG_COLOUR(...) (printf(starts_with(SELECT1(__VA_ARGS__), "[INIT]")? TERM_WHITE: \
                                  starts_with(SELECT1(__VA_ARGS__), "[RES]" )? TERM_GREEN: \
                                  starts_with(SELECT1(__VA_ARGS__), "[GFX]" )? TERM_BLUE : \
                                  TERM_NORMAL))

#if DEBUGGING
	#define DEBUG(...) do {                \
			if (SELECT1(__VA_ARGS__)[0]) { \
				DEBUG_COLOUR(__VA_ARGS__); \
				printf(__VA_ARGS__);       \
				printf("\n" TERM_NORMAL);  \
			}                              \
		} while (0)
	#define ERROR(...) do {                                                                 \
			fprintf(stderr, TERM_RED);                                                      \
			fprintf(stderr, __VA_ARGS__);                                                   \
			fprintf(stderr, "\n\t%s:%d in %s\n" TERM_NORMAL, __FILE__, __LINE__, __func__); \
		} while (0)
	#define ASSERT(ass, exit, ...) do { \
			if (!(ass)) {               \
				ERROR(__VA_ARGS__);     \
				if ((exit))             \
					abort();            \
			}                           \
		} while (0);
	#define DEBUG_GL() do {                                                                 \
		GLenum err;                                                                         \
		while ((err = glGetError()) != GL_NO_ERROR) {                                       \
			fprintf(stderr, TERM_RED "[OGL] %s",                                            \
				err == GL_INVALID_ENUM                 ? "INVALID_ENUM"     :               \
				err == GL_INVALID_VALUE                ? "INVALID_VALUE"    :               \
				err == GL_INVALID_OPERATION            ? "INVALID_OPERATION":               \
				err == GL_STACK_OVERFLOW               ? "STACK_OVERFLOW"   :               \
				err == GL_STACK_UNDERFLOW              ? "STACK_UNDERFLOW"  :               \
				err == GL_OUT_OF_MEMORY                ? "OUT_OF_MEMORY"    :               \
				err == GL_INVALID_FRAMEBUFFER_OPERATION?                                    \
				"INVALID_FRAMEBUFFER_OPERATION": "UNKNOWN ERROR");                          \
			fprintf(stderr, "\n\t%s:%d in %s\n" TERM_NORMAL, __FILE__, __LINE__, __func__); \
		}                                                                                   \
	} while (0)
#else
	#define DEBUG(...)
	#define ERROR(...)
	#define ASSERT(...)
	#define DEBUG_GL()
#endif

#endif
