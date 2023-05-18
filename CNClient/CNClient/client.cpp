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
		cout << "클라이언트 소켓 생성 실패" << endl;
		return 0;
	}

	cout << "클라이언트 소켓 생성완료" << endl;

	ZeroMemory(&serverAddress, sizeof(serverAddress));
	inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(PORT);



	connect(clientSocket, (sockaddr*)&serverAddress, sizeof(serverAddress));
	cout << "야구 게임을 시작합니다." << endl;

	while (nm) {//스트라익이 3이될때 까지 반복

		cout << " 세 수를 입력해 주세요(ex: 1 2 3)\n--> " << endl;
		/*키보드 입력된 세개의 숫자를 읽어 들임*/
		cin >> clientNumber[0] >> clientNumber[1] >> clientNumber[2];
		/*데이터를 전송하기 위해서 네트워크 바이트 정렬 방식으로 데이터 정렬*/
		for (i = 0; i < 3; i++)
			clientNumber[i] = htonl(clientNumber[i]);
		/*입력된 세개의 숫자 서버로 전송*/
		send(clientSocket, (char*)clientNumber, sizeof(clientNumber), 0);

		recv(clientSocket, (char*)score, sizeof(score), 0);//서버에서 전달한 스트라익과 볼의 개수를 읽어 들임

	//네트워크 바이트 정렬된 데이터를 호스트 바이트 정렬한후에 스트라익과 볼에 대입
		int strike = ntohl(score[0]);
		int ball = ntohl(score[1]);
		cout << strike << " 스트라이크 " << ball << " 볼 " << endl;
		/*스트라익이 3이면 프로그램 종료*/
		if (strike == 3) {
			cout << " 3 스트라이크 프로그램을 종료 합니다. " << endl;
			nm = 0;	  // 결쇠 변수
		}
	}
	closesocket(clientSocket);
	WSACleanup();
	return 0;
}

