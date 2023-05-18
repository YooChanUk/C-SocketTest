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

	WSAStartup(MAKEWORD(2, 2), &wsdata); //ws2_32.DLL 초기화

	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0); //서버 소켓 생성
	cout << "서버 소켓을 생성하였습니다." << endl;

	ZeroMemory(&serverAddress, sizeof(serverAddress)); //구조체를 0으로 초기화

	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);//현재IP대입 및 자동으로 IP리턴
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(PORT);

	//서버 소켓에 주소 정보설정
	bind(serverSocket, (sockaddr*)&serverAddress, sizeof(serverAddress));
	//클라이언트 접속 기다리는 대기모드 전환
	listen(serverSocket, 5);
	cout << "클라이언트의 접속을 감시합니다." << endl;
	//클라이언트의 접속을 허락하고 클라와 데이터를 주고받는 클라 소켓 생성
	SOCKET clientSocket = accept(serverSocket, NULL, NULL);
	cout << "클라이언트가 접속했습니다." << endl;
	cout << "야구 게임 시작" << endl;

	srand((unsigned)time(NULL));

	while ((serverNumber[0] == serverNumber[1]) ||
		(serverNumber[1] == serverNumber[2]) ||
		(serverNumber[2] == serverNumber[0]))
	{
		serverNumber[0] = rand() % 10;
		serverNumber[1] = rand() % 10;
		serverNumber[2] = rand() % 10;
	} // 배열에 같은 수가 없을때까지 반복

	cout << "서버숫자 --> " << serverNumber[0] << serverNumber[1] << serverNumber[2] << endl;

	while (nm) //무한 반복하다가 스트라이크가 3이 되면 종료
	{
		//클라이언트가 입력한 세개의 숫자를 읽고 fromClientNumber에 대입
		recv(clientSocket, (char*)fromClientNumber, sizeof(fromClientNumber), 0);
		//네트워크 바이트 정렬된 숫자를 호스트 바이트로 재정렬
		//배열로 된 여러 데이터 추출 위해 ntohl 함수 사용

		for (index = 0; index < 3; index++)
		{
			fromClientNumber[index] = ntohl(fromClientNumber[index]);
		}

		cout << "클라이언트가 입력한 수 --> " << fromClientNumber[0] << fromClientNumber[1] << fromClientNumber[2] << endl;

		for (i = 0; i < 3; i++)
		{
			//서버의 숫자가 저장된 serverNumber 에서 i번째 숫자를 꺼내 oneServerNumber에 대입
			int oneServerNumber = serverNumber[i];
			for (int j = 0; j < 3; j++)
			{
				//클라이언트에서 전송한 숫자가 저장된 fromClientNumber의 j번째 숫자를 꺼내서
				//oneClientNumber에 대입
				int oneClientNumber = fromClientNumber[j];

				if (oneServerNumber == oneClientNumber)
				{
					//서버 숫자의 위치와 클라이언트 숫자 위치가 같으면
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

		cout << strike << "스트라이크" << ball << "볼" << endl;

		toClientScore[0] = htonl(strike);
		toClientScore[1] = htonl(ball);

		send(clientSocket, (char*)toClientScore, sizeof(toClientScore), 0);

		if (strike == 3)
		{
			cout << "3 스트라이크 프로그램을 종료합니다." << endl;
			nm = 0;
		}

		strike = ball = 0;
	}//while end

	closesocket(serverSocket);
	WSACleanup();
	return 0;
}