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

	int clientNumber[3];
	int i;
	int score[2];
	int nm = 1;

	WSAStartup(MAKEWORD(2, 2), &wsdata);
	SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == INVALID_SOCKET)
	{
		cout << "Ŭ���̾�Ʈ ���� ���� ����" << endl;
		return 0;
	}

	cout << "Ŭ���̾�Ʈ ���� �����Ϸ�" << endl;

	ZeroMemory(&serverAddress, sizeof(serverAddress));
	inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(PORT);



	connect(clientSocket, (sockaddr*)&serverAddress, sizeof(serverAddress));
	cout << "�߱� ������ �����մϴ�." << endl;

	while (nm) {//��Ʈ������ 3�̵ɶ� ���� �ݺ�

		cout << " �� ���� �Է��� �ּ���(ex: 1 2 3)\n--> " << endl;
		/*Ű���� �Էµ� ������ ���ڸ� �о� ����*/
		cin >> clientNumber[0] >> clientNumber[1] >> clientNumber[2];
		/*�����͸� �����ϱ� ���ؼ� ��Ʈ��ũ ����Ʈ ���� ������� ������ ����*/
		for (i = 0; i < 3; i++)
			clientNumber[i] = htonl(clientNumber[i]);
		/*�Էµ� ������ ���� ������ ����*/
		send(clientSocket, (char*)clientNumber, sizeof(clientNumber), 0);

		recv(clientSocket, (char*)score, sizeof(score), 0);//�������� ������ ��Ʈ���Ͱ� ���� ������ �о� ����

	//��Ʈ��ũ ����Ʈ ���ĵ� �����͸� ȣ��Ʈ ����Ʈ �������Ŀ� ��Ʈ���Ͱ� ���� ����
		int strike = ntohl(score[0]);
		int ball = ntohl(score[1]);
		cout << strike << " ��Ʈ����ũ " << ball << " �� " << endl;
		/*��Ʈ������ 3�̸� ���α׷� ����*/
		if (strike == 3) {
			cout << " 3 ��Ʈ����ũ ���α׷��� ���� �մϴ�. " << endl;
			nm = 0;	  // ��� ����
		}
	}
	closesocket(clientSocket);
	WSACleanup();
	return 0;
}

