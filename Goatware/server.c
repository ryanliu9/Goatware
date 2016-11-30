#include <stdio.h>
#include <stdlib.h>
#include <string.h>       // strlen
#include <sys/socket.h>   // socket
#include <arpa/inet.h>    // inet_addr
#include <unistd.h>       // write
#include <fcntl.h>

#define SRV_PORT 5000
#define LISTEN_ENQ 5
#define MAX_RECV 512
#define MAX_SEND 512
#define SRV_IP "192.168.56.101"

void get_filename(int, char*);
int send_file(int , char*);

int main(int argc , char *argv[])
{
	int listen_fd, conn_fd;
	struct sockaddr_in srv_addr, cli_addr;
	socklen_t cli_len;

	char filename [MAX_RECV];
	char print_addr [INET_ADDRSTRLEN];

	memset(&srv_addr, 0, sizeof(srv_addr));
	memset(&cli_addr, 0, sizeof(cli_addr));
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_addr.s_addr = inet_addr(SRV_IP);
	srv_addr.sin_port = htons(SRV_PORT);

	if((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket error");
		exit(-1);
	}

	/*bind*/
	if (bind(listen_fd, (struct sockaddr*) &srv_addr, sizeof(srv_addr)) < 0) {
		perror("error binding");
		exit(-1);
	}

	if(listen(listen_fd, LISTEN_ENQ) < 0) {
		perror("error listening");
		exit(-1);
	}

	while (1) {
		cli_len = sizeof(cli_addr);

		if ((conn_fd = accept(listen_fd, (struct sockaddr*) &cli_addr, &cli_len)) < 0) {
			perror("error accepting");
			break;
		}

		inet_ntop(AF_INET, &(cli_addr.sin_addr), print_addr, INET_ADDRSTRLEN);

		get_filename(conn_fd, filename);
		send_file(conn_fd, filename);
		close(conn_fd);
	}

	close(listen_fd);
	return 0;
}

void get_filename(int sock, char* filename) {
	char recv_str[MAX_RECV];
	ssize_t bytes_rcvd;

	if((bytes_rcvd = recv(sock, recv_str, MAX_RECV, 0)) < 0) {
		perror("error recieving");
		return;
	}

	sscanf(recv_str, "%s\n", filename);
}

int send_file(int sock, char *file_name) {
	int count;
	ssize_t bytes_read, bytes_sent, file_size;
	char send_buf[MAX_SEND];
	char * errmsg = "File not found\n";
	int f;

	count = 0;
	file_size = 0;

	if ((f = open(file_name, O_RDONLY)) < 0) {
		perror(file_name);
		if((bytes_sent = send(sock, errmsg, strlen(errmsg), 0)) < 0) {
			perror("error sending file");
			return -1;
		}
	}
	else {
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
