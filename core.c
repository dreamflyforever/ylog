#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int now()
{
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    char time_str[80];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", timeinfo);
    printf("%s", time_str);

    return 0;
}
#define DEBUG 1
#if DEBUG
#define ylog(format, ...) \
	{now(); printf(" [%s : %s : %d] ", \
	__FILE__, __func__, __LINE__); \
	printf(format, ##__VA_ARGS__);}
#else
#define os_printf(format, ...) 
#endif

int main(int argc, char *argv[])
{
	ylog("hello\n");
	ylog("world\n");
	return 0;
}
