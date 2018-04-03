#ifndef CSAGE_H
#define CSAGE_H

#ifndef CSAGE_DIMENSIONS
	#define CSAGE_DIMENSIONS 3
#endif

#include "common.h"

extern struct Renderer renderer;

void csage_init(void);
void csage_loop(void);
void csage_quit(void);

#endif
