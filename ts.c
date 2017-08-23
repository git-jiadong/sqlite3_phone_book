#include "touch.h"

int init_touch(void)
{
	int ts = open("/dev/input/event0", O_RDWR);
	if(ts == -1)
	{
		perror("open touch failed ");
		exit(1);
	}

	return ts;
}

void wait4touch(int ts, touch *ts_buf)
{
	struct input_event buf;
	
	ts_buf->status = 1;
	while(1)
	{
		bzero(&buf, sizeof(buf));
		read(ts, &buf, sizeof(buf));
		if(buf.type == EV_ABS && buf.code == ABS_X)
		{
			ts_buf->x = buf.value;
		}
		if(buf.type == EV_ABS && buf.code == ABS_Y)
		{
			ts_buf->y = buf.value;
		}

		if(buf.type == EV_KEY)
		{
			if(buf.code == BTN_TOUCH && buf.value == 0)
			{
				ts_buf->status = buf.value;
				break;
			}
		}
	}
}
