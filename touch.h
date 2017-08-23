#ifndef __TOUCH_H
#define __TOUCH_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/input.h>

typedef struct touch
{
	int x;
	int y;
	bool status;
}touch;

int init_touch(void);
void wait4touch(int ts, touch *ts_buf);

#endif
