#include "common.h"

uint32 malloced = 0;

void* _smalloc(uintptr bytes, char* file, uint line, char const* func)
{
	void* mem = malloc(bytes);
	if (!mem) {
		ERROR("[MEM] Malloc failed for %u bytes", (uint)bytes);
		return NULL;
	} else {
		malloced += bytes;
		if (bytes >= DEBUG_MALLOC_MIN)
			DEBUG("[MEM] Allocated %uB (%.2fkB) (%.2fkB total) in \"%s:%u:%s\"",
				  (uint)bytes, (double)bytes/1024.0, (double)malloced/1024.0, file, line, func);
		return mem;
	}
}

void* _scalloc(uintptr items, uintptr size, char* file, uint line, char const* func)
{
	uintptr bytes = items * size;
	void* mem = calloc(items, size);
	if (!mem) {
		ERROR("[MEM] Calloc failed for %u bytes", (uint)bytes);
		return NULL;
	} else {
		malloced += bytes;
		if (bytes >= DEBUG_MALLOC_MIN)
			DEBUG("[MEM] Allocated %uB (%.2fkB) (%.2fkB total) in \"%s:%u:%s\"",
				  (uint)bytes, (double)bytes/1024.0, (double)malloced/1024.0, file, line, func);
		return mem;
	}
}
