#define CSAGE_DIMENSIONS 2
#include "csage.h"

int main(int argc, char** argv)
{
	(void)argc; (void)argv;
	csage_init();
	csage_loop();

	return 0;
}
