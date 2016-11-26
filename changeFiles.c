/* CURRENTLY DOES: Lists all files/directories in specific directory */
/* NEEDS TO: Change the content of programs based on their file extension. */

#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

void changeDir(const char *direct, int level) {
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
			char directPath[1024];
			int length = snprintf(directPath, sizeof(directPath)-1, "%s/%s", direct, entry->d_name);
			directPath[length] = 0;
			if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
				continue;
			printf("%*s[%s]\n", level*2, "", entry->d_name);
			changeDir(directPath, level + 1);
		}
		else {
			printf("%*s- %s\n", level*2, "", entry->d_name);
		}
	} while (entry = readdir(dir));
	closedir(dir);
}

int main(void) {
	changeDir(".", 0);
	return 0;
}

