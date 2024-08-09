#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>

char time_str[80];
char * ylog_get_time()
{
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", timeinfo);
    return time_str;
}

int ylog_now_print()
{
	printf("%s", ylog_get_time());
	return 0;
}

#define YLOG_FILE 1

#if YLOG_FILE
int g_fd;
int ylog_file_init()
{
	char tmp_file[94];
	snprintf(tmp_file, 94, "%s", ylog_get_time());
	g_fd = open(tmp_file, O_CREAT | O_RDWR, 0666);
	if (g_fd == -1) {
		perror("error open file\n");
		return 1;
	} else {
		printf("open %s success\n", tmp_file);
	}
	return 0;
}

int ylog_file_close()
{
	close(g_fd);
	return 0;
}
#endif

#define DEBUG 0
#if DEBUG
#define ylog(format, ...) \
	{ylog_now_print(); printf(" [%s : %s : %d] ", \
	__FILE__, __func__, __LINE__); \
	printf(format, ##__VA_ARGS__);}
#elif YLOG_FILE

#define ylog(format, ...) \
{ \
	char tmp[512] = {0}; \
	snprintf(tmp, 128, "%s [%s : %s : %d] ", ylog_get_time(),  __FILE__, __func__, __LINE__); \
	write(g_fd, tmp, strlen(tmp));\
	memset(tmp, 0, 512); \
	snprintf(tmp, 128, format, ##__VA_ARGS__); \
	write(g_fd, tmp, strlen(tmp)); }

#else
#define ylog(format, ...) 
#endif

int main(int argc, char *argv[])
{
#if YLOG_FILE
	ylog_file_init();
#endif
	ylog("hello\n");
	ylog("world\n");
#if YLOG_FILE
	ylog_file_close();
#endif
	return 0;
}
