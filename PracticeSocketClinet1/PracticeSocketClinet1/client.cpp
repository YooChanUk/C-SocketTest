#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<winsock2.h>
#include<ws2tcpip.h>
#pragma comment(lib,"ws2_32.lib")
#define PORT 5500
using namespace std;

int main()
{
	WSADATA wsdata;
	sockaddr_in serverAddress;

	WSAStartup(MAKEWORD(2, 2), &wsdata);
	SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);

	cout << "클라이언트 소켓 생성 완료" << endl;

	ZeroMemory(&serverAddress, sizeof(serverAddress));
	inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(PORT);

	connect(clientSocket, (sockaddr*)&serverAddress, sizeof(serverAddress));

	closesocket(clientSocket);
	WSACleanup();
	return 0;
}