#ifndef CSAGE_H
#define CSAGE_H

#include "common.h"

#define THREAD_COUNT 4
#define CSAGE_DIMENSIONS 3

extern struct Renderer renderer;

void csage_init(void);
void csage_loop(void);
noreturn void csage_quit(void);

#endif
