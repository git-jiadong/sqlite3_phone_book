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
#include "jpeg.h"
#include "touch.h"
#include "sqlite3.h"
#include "head.h"

int main(int argc, char *argv[])
{
	touch buf;

	init_show();
	int ts = init_touch();
	
	sqlite3 *db = init_sql();
	create_table(db);

	while(1)
	{
		printf("input the cmd: \n");
		wait4touch(ts, &buf);
#ifdef DEBUG
		printf("x: %d\n", buf.x);
		printf("y: %d\n", buf.y);
		printf("status: %d\n", buf.status);
#endif
		if(buf.x>160 && buf.x<280 && 
		   buf.y>120 && buf.y<360 && 
		   buf.status==0)
		{
			close(ts);
			if(sqlite_insert(db))
			{
				printf("insert contacts failed\n");
			}
			ts = init_touch();
		}
		if(buf.x>320 && buf.x<440 && 
		   buf.y>120 && buf.y<360 && 
		   buf.status==0)
		{
			close(ts);
			if(sqlite_delete(db))
			{
				printf("insert contacts failed\n");
			}
			ts = init_touch();
		}
		if(buf.x>480 && buf.x<600 && 
		   buf.y>120 && buf.y<360 &&
		   buf.status==0)
		{
			close(ts);
			if(sqlite_update(db))
			{
				printf("update contacts failed\n");
			}
			ts = init_touch();
		}
		 if(buf.x>640 && buf.x<760 && 
		    buf.y>120 && buf.y<360 && 
		    buf.status==0)
		{
			close(ts);
			if(sqlite_show(db))
			{
				printf("NOT contacts\n");
			}
			ts = init_touch();
		}
		

	}

	return 0;
}
