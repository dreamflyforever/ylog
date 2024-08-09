#include "core.h"

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

int ylog_init()
{
#if YLOG_FILE
	ylog_file_init();
#endif
	return 0;
}

int ylog_deinit()
{
#if YLOG_FILE
	ylog_file_close();
#endif
	return 0;
}
