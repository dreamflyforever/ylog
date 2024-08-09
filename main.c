#include "core.h"

int main(int argc, char *argv[])
{
	ylog_init();
	ylog("hello\n");
	ylog("world\n");
	ylog_deinit();
	return 0;
}
