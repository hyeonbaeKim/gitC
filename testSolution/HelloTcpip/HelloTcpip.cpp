#include <WinSock2.h>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")
int main()
{
	//윈속 초기화
	//윈속(WinSock)은 윈도우에서 소켓 프로그래밍을 할 때 사용하는 네트워크 라이브러리입니다.
	//윈속을 사용하려면 반드시 초기화와 해제가 필요합니다.
	WSADATA wsa = {0};
	if(::WSAStartup(MAKEWORD(2,2), &wsa) != 0) //MAKEWORD(2,2): 윈속 버전 2.2
	{
		puts("Error : WSAStartup()");
		return 0;
	}

	//1. 접속대기 서버소켓 생성
	SOCKET hSocket = ::socket(AF_INET, SOCK_STREAM, 0); //AF_INET: IPv4 인터넷 프로토콜, SOCK_STREAM: TCP 소켓
	if(hSocket == INVALID_SOCKET)
	{
		puts("Error : socket()");
		return 0;
	}

	//2. 접속대기 서버소켓에 포트바인딩
	SOCKADDR_IN svrAddr = {};
	svrAddr.sin_family = AF_INET; //주소체계
	svrAddr.sin_port = htons(25000); //포트번호, htons: 호스트 바이트 순서를 네트워크 바이트 순서로 변환
	svrAddr.sin_addr.s_addr = htonl(INADDR_ANY); //IP주소, htonl: 호스트 바이트 순서를 네트워크 바이트 순서로 변환, INADDR_ANY: 모든 IP주소
	if(::bind(hSocket, (SOCKADDR*)&svrAddr, sizeof(svrAddr)) == SOCKET_ERROR)
	{
		puts("Error : 소켓에 IP주소와 포트를 바인딩 할 수 없습니다.");
		::closesocket(hSocket);
		return 0;
	}

	//3. 접속대기 서버소켓을 접속대기 상태로 만듦
	if(::listen(hSocket, SOMAXCONN) == SOCKET_ERROR) //SOMAXCONN: 최대 대기 큐 길이
	{
		puts("Error : 소켓을 접속대기 상태로 만들 수 없습니다.");
		::closesocket(hSocket);
		return 0;
	}

	//4. 클라이언트 접속 처리 및 대응
	SOCKADDR_IN clntAddr = {};
	int addrLen = sizeof(clntAddr);
	SOCKET hClient = 0; //서버통신용 소켓
	char szBuffer[128] = {};
	int nReceive = 0;

	//4.1 서버대기소켓이 클라이언트 연결을 받아들이고 서버통신소켓 개방
	while((hClient = :: accept(hSocket, (SOCKADDR*)&clntAddr, &addrLen)) != INVALID_SOCKET)
	{
		puts("클라이언트 접속됨");
		//4.2 클라이언트로부터 문자열을 수신함
		while((nReceive = ::recv(hClient, szBuffer, sizeof(szBuffer) ,0)))
		{// TCP 계층(운영체제 내부의 네트워크 버퍼)에 도착한 데이터를 애플리케이션 계층의 버퍼인 szBuffer에 복사합니다.
			::send(hClient, szBuffer, nReceive, 0); //szBuffer에 저장된 데이터를 다시 클라이언트로 전송
			puts(szBuffer);
			memset(szBuffer, 0, sizeof(szBuffer));
		}

		//4.3 클라이언트가 연결을 종료함
		::shutdown(hClient, SD_BOTH); //SD_BOTH: 송수신 모두 종료
		::closesocket(hClient);
		puts("클라이언트 접속 종료됨");
	}

	//5. 접속대기 서버소켓 종료
	::closesocket(hSocket);

	//윈속 해제
	::WSACleanup();
	return 0;
}