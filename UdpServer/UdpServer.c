#pragma comment (lib,"ws2_32.lib")
#include <stdio.h>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>


void quit(const char* msg) {
	printf("Error:%s\n", msg);
	exit(1);
}

int main(int argc, char** argv) {
	if (argc != 2) quit("Command Argument");
	WSADATA w;
	int ret = WSAStartup(MAKEWORD(2, 2), &w);
	if (ret == 1) quit("WinSockApi");

	SOCKET s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (s == SOCKET_ERROR) quit("create Socket");
	printf("Socket Is Ready\n");
	//Socket Binding
	SOCKADDR_IN sa, ca; //local and remote socket address
	sa.sin_addr.s_addr = INADDR_ANY;
	sa.sin_port = htons(atoi(argv[1]));
	sa.sin_family = AF_INET;
	ret = bind(s, (SOCKADDR*)&sa, sizeof(sa));
	if (ret == SOCKET_ERROR) quit("Binding");
	printf("Binding is OK\n");
	while (1) {
		char buf[1000] = { 0 }; //memset(buf, 0 , 100);
		int rlen = sizeof(ca);
		ret = recvfrom(s, buf, 1000, 0, (SOCKADDR*)&ca, &rlen); //in case if we dont wanna know the remote
		if (ret = SOCKET_ERROR) quit("recvform");
		printf("client(%s:%d): %s/n", inet_ntoa(ca.sin_addr), ntohs(ca.sin_port), buf);
	}
}