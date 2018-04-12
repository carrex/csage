#ifndef CSAGE_H
#define CSAGE_H

#define CSAGE_DIMENSIONS 3

#include "common.h"

extern struct Renderer renderer;

void csage_init(void);
void csage_loop(void);
noreturn void csage_quit(void);

#endif
