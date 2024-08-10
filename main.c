#include "core.h"

void disk_full(void * arg)
{
	ylog("no space\n");
}

int main(int argc, char *argv[])
{
	ylog_init();
	register_cb(disk_full);
	ylog("hello\n");
	ylog("world\n");
	ylog_deinit();
	return 0;
}
