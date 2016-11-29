#include <stdio.h>
#include <stdlib.h>
#include <string.h>      // strlen
#include <sys/socket.h>  // socket
#include <arpa/inet.h>   // inet_addr
#include <unistd.h>      // write
#include <fcntl.h>

#define SRV_PORT 5000
#define MAX_RECV 512
#define MAX_SEND 512

int recv(int ,char*);

int main(int argc , char *argv[])
{
	int sock_fd;
	struct sockaddr_in srv_addr;

	memset(&srv_addr, 0, sizeof(srv_addr));

	/*create server*/
	sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_addr.s_addr = INADDR_ANY;
	srv_addr.sin_port = htons(SRV_PORT);

	if (connect(sock_fd, (struct sockaddr*) &srv_addr, sizeof(srv_addr)) < 0) {
		perror("connect error");
		exit(-1);
	}

	recv(sock_fd, "file.txt");

	if (close(sock_fd) < 0) {
		perror("error closign socket");
		exit(-1);
	}
	return 0;
}

int recv(int sock, char* file_name) {
	char send_str[MAX_SEND];
	int f;
	ssize_t bytes_sent, bytes_rcvd, file_size;
	int count;
	char recv_str[MAX_RECV];
	size_t send_strlen;

	sprintf(send_str, "%s\n", file_name);
	send_strlen = strlen(send_str);

	if((bytes_sent = send(sock, file_name, send_strlen, 0)) < 0) {
		perror("send error");
		return -1;
	}

	/*create file*/
	if((f = open("test2.txt", O_WRONLY|O_CREAT, 0644)) < 0) {
		perror("could not creat file");
		return -1;
	}

	count = 0;
	file_size = 0;

	while ((bytes_rcvd = recv(sock, recv_str, MAX_RECV, 0)) > 0) {
		count++;
		file_size += bytes_rcvd;

		if (write(f, recv_str, bytes_rcvd) < 0) {
			perror("could not write to file");
			return -1;
		}
	}
	close(f);
	return file_size;
}
