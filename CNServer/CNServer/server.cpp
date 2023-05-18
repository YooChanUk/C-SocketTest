#include<iostream>
#include<stdlib.h>
#include<winsock2.h>
#include<time.h>
#pragma comment(lib,"ws2_32.lib")
#define PORT 5500
using namespace std;

int main()
{
	WSADATA wsdata;
	sockaddr_in serverAddress;

	int serverNumber[3] = { 0 };
	int fromClientNumber[3];
	int toClientScore[2];
	int index, i;
	int strike = 0;
	int ball = 0;
	int nm = 1;

	WSAStartup(MAKEWORD(2, 2), &wsdata); //ws2_32.DLL �ʱ�ȭ

	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0); //���� ���� ����
	cout << "���� ������ �����Ͽ����ϴ�." << endl;

	ZeroMemory(&serverAddress, sizeof(serverAddress)); //����ü�� 0���� �ʱ�ȭ

	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);//����IP���� �� �ڵ����� IP����
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(PORT);

	//���� ���Ͽ� �ּ� ��������
	bind(serverSocket, (sockaddr*)&serverAddress, sizeof(serverAddress));
	//Ŭ���̾�Ʈ ���� ��ٸ��� ����� ��ȯ
	listen(serverSocket, 5);
	cout << "Ŭ���̾�Ʈ�� ������ �����մϴ�." << endl;
	//Ŭ���̾�Ʈ�� ������ ����ϰ� Ŭ��� �����͸� �ְ�޴� Ŭ�� ���� ����
	SOCKET clientSocket = accept(serverSocket, NULL, NULL);
	cout << "Ŭ���̾�Ʈ�� �����߽��ϴ�." << endl;
	cout << "�߱� ���� ����" << endl;

	srand((unsigned)time(NULL));

	while ((serverNumber[0] == serverNumber[1]) ||
		(serverNumber[1] == serverNumber[2]) ||
		(serverNumber[2] == serverNumber[0]))
	{
		serverNumber[0] = rand() % 10;
		serverNumber[1] = rand() % 10;
		serverNumber[2] = rand() % 10;
	} // �迭�� ���� ���� ���������� �ݺ�

	cout << "�������� --> " << serverNumber[0] << serverNumber[1] << serverNumber[2] << endl;

	while (nm) //���� �ݺ��ϴٰ� ��Ʈ����ũ�� 3�� �Ǹ� ����
	{
		//Ŭ���̾�Ʈ�� �Է��� ������ ���ڸ� �а� fromClientNumber�� ����
		recv(clientSocket, (char*)fromClientNumber, sizeof(fromClientNumber), 0);
		//��Ʈ��ũ ����Ʈ ���ĵ� ���ڸ� ȣ��Ʈ ����Ʈ�� ������
		//�迭�� �� ���� ������ ���� ���� ntohl �Լ� ���

		for (index = 0; index < 3; index++)
		{
			fromClientNumber[index] = ntohl(fromClientNumber[index]);
		}

		cout << "Ŭ���̾�Ʈ�� �Է��� �� --> " << fromClientNumber[0] << fromClientNumber[1] << fromClientNumber[2] << endl;

		for (i = 0; i < 3; i++)
		{
			//������ ���ڰ� ����� serverNumber ���� i��° ���ڸ� ���� oneServerNumber�� ����
			int oneServerNumber = serverNumber[i];
			for (int j = 0; j < 3; j++)
			{
				//Ŭ���̾�Ʈ���� ������ ���ڰ� ����� fromClientNumber�� j��° ���ڸ� ������
				//oneClientNumber�� ����
				int oneClientNumber = fromClientNumber[j];

				if (oneServerNumber == oneClientNumber)
				{
					//���� ������ ��ġ�� Ŭ���̾�Ʈ ���� ��ġ�� ������
					if (i == j)
					{
						strike++;
					}
					else
					{
						ball++;
					}
				}
			}//end jfor
		}//end ifor

		cout << strike << "��Ʈ����ũ" << ball << "��" << endl;

		toClientScore[0] = htonl(strike);
		toClientScore[1] = htonl(ball);

		send(clientSocket, (char*)toClientScore, sizeof(toClientScore), 0);

		if (strike == 3)
		{
			cout << "3 ��Ʈ����ũ ���α׷��� �����մϴ�." << endl;
			nm = 0;
		}

		strike = ball = 0;
	}//while end

	closesocket(serverSocket);
	WSACleanup();
	return 0;
}