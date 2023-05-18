#include<iostream>
#include<stdlib.h>
#include<winsock2.h>
#include<time.h>
#pragma comment(lib.,"ws2_32.lib")
#define PORT 5500
using namespace std;

int main()
{
	WSADATA wsdata;
	sockaddr_in serverAddress;

	int fromClient;

	WSAStartup(MAKEWORD(2, 2), &wsdata);

	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	cout << "서버 소켓 생성완료" << endl;

	ZeroMemory(&serverAddress, sizeof(serverAddress));
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(PORT);

	bind(serverSocket, (sockaddr*)&serverAddress, sizeof(serverAddress));

	listen(serverSocket, 5);
	cout << "클라이언트의 접속을 감시합니다." << endl;

	SOCKET clientSocket = accept(serverSocket, NULL, NULL);
	cout << "클라이언트가 접속했습니다." << endl;

	//이 아래부터 서버에서 해야할 함수를 집어넣습니다.
	while (1)
	{
		recv(clientSocket, (char*)fromClient, sizeof(fromClient), 0);
	}

	closesocket(serverSocket);
	WSACleanup();
	return 0;
}

int sachick()
{

}

int leftright()
{

}