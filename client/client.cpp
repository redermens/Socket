#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <iostream>
#include <fstream>
#pragma comment(lib,"ws2_32.lib")

#define BUF_SIZE 1024
#define PORT 12345//设置端口
#define IPv4 "192.168.43.212"//设置ip地址

int main()
{
	std::ofstream os("02.jpg", std::ios::out|std::ios::binary);//传输图片的话好像必须要设置为binary
	if (os.is_open())
	{
		std::cout << "file open success!" << std::endl;
	}
	else
		std::cout << "file open failed!" << std::endl;
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr.S_un.S_addr = inet_addr(IPv4);
	sockAddr.sin_port = htons(PORT);
	connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

	long tmp = 0;
	char* buffer = new char[BUF_SIZE];
	while (auto n = recv(sock, buffer, BUF_SIZE, 0))
	{
		os.write(buffer,n);
		tmp += n;
		if (n != 1024)
		{
			break;
		}
	}

	std::cout << "Messeage recv success!" << std::endl;
	std::cout << tmp << std::endl;

	os.close();
	closesocket(sock);
	WSACleanup();

	system("pause");
	return 0;

}