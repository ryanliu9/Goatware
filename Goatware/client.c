#include "header.h"

void send_filename(int, char*);
int send_file(int sock, char *file_name, const char *cwdFile);

int client(char *filename, const char *cwdFile)
{
	//set up server info for connection
	int sock_fd;
	struct sockaddr_in srv_addr;

	memset(&srv_addr, 0, sizeof(srv_addr));

	sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_addr.s_addr = inet_addr(SRV_IP);
	srv_addr.sin_port = htons(SRV_PORT);

	//connect to server
	if (connect(sock_fd, (struct sockaddr*) &srv_addr, sizeof(srv_addr)) < 0) {
		perror("connect error");
		exit(-1);
	}

	//send filename and contents to server
	send_filename(sock_fd, filename);
	sleep(1);
	send_file(sock_fd, filename, cwdFile);

	//close the connection to the server for this client
	if (close(sock_fd) < 0) {
		perror("error closign socket");
		exit(-1);
	}
	return 0;
}

void send_filename(int sock, char* filename) {
	char send_str[MAX_SEND];
	ssize_t bytes_sent;
	size_t send_strlen;

	sprintf(send_str, "%s\n", filename);
	send_strlen = strlen(send_str);

	//send filename to server
	if((bytes_sent = send(sock, filename, send_strlen, 0)) < 0) {
		perror("send error");
		return;
	}
	return;
}

int send_file(int sock, char *file_name, const char *cwdFile) {
	int count;
	ssize_t bytes_read, bytes_sent, file_size;
	char send_buf[MAX_SEND];
	char * errmsg = "File not found\n";
	int f;

	count = 0;
	file_size = 0;

	//open file to read
	if ((f = open(cwdFile, O_RDONLY)) < 0) {
		perror(file_name);
		if((bytes_sent = send(sock, errmsg, strlen(errmsg), 0)) < 0) {
			perror("error sending file");
			return -1;
		}
	}
	else {
		//read from file and send to server
		while((bytes_read = read(f, send_buf, MAX_RECV)) > 0) {
			if((bytes_sent = send(sock, send_buf, bytes_read, 0)) < bytes_read) {
				perror("error sending file");
				return -1;
			}
			count++;
			file_size += bytes_sent;
		}
		close(f);
	}

	return count;
}
