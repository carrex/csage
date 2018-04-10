#include <stdio.h>

#include "common.h"
#include "file.h"

uintptr file_size(FILE* file)
{
	fseek(file, 0, SEEK_END);
	uintptr size = ftell(file) * sizeof(char);
	rewind(file);

	return size;
}
