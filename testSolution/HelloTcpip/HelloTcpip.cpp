#include <WinSock2.h>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")
int main()
{
	//���� �ʱ�ȭ
	//����(WinSock)�� �����쿡�� ���� ���α׷����� �� �� ����ϴ� ��Ʈ��ũ ���̺귯���Դϴ�.
	//������ ����Ϸ��� �ݵ�� �ʱ�ȭ�� ������ �ʿ��մϴ�.
	WSADATA wsa = {0};
	if(::WSAStartup(MAKEWORD(2,2), &wsa) != 0) //MAKEWORD(2,2): ���� ���� 2.2
	{
		puts("Error : WSAStartup()");
		return 0;
	}

	//1. ���Ӵ�� �������� ����
	SOCKET hSocket = ::socket(AF_INET, SOCK_STREAM, 0); //AF_INET: IPv4 ���ͳ� ��������, SOCK_STREAM: TCP ����
	if(hSocket == INVALID_SOCKET)
	{
		puts("Error : socket()");
		return 0;
	}

	//2. ���Ӵ�� �������Ͽ� ��Ʈ���ε�
	SOCKADDR_IN svrAddr = {};
	svrAddr.sin_family = AF_INET; //�ּ�ü��
	svrAddr.sin_port = htons(25000); //��Ʈ��ȣ, htons: ȣ��Ʈ ����Ʈ ������ ��Ʈ��ũ ����Ʈ ������ ��ȯ
	svrAddr.sin_addr.s_addr = htonl(INADDR_ANY); //IP�ּ�, htonl: ȣ��Ʈ ����Ʈ ������ ��Ʈ��ũ ����Ʈ ������ ��ȯ, INADDR_ANY: ��� IP�ּ�
	if(::bind(hSocket, (SOCKADDR*)&svrAddr, sizeof(svrAddr)) == SOCKET_ERROR)
	{
		puts("Error : ���Ͽ� IP�ּҿ� ��Ʈ�� ���ε� �� �� �����ϴ�.");
		::closesocket(hSocket);
		return 0;
	}

	//3. ���Ӵ�� ���������� ���Ӵ�� ���·� ����
	if(::listen(hSocket, SOMAXCONN) == SOCKET_ERROR) //SOMAXCONN: �ִ� ��� ť ����
	{
		puts("Error : ������ ���Ӵ�� ���·� ���� �� �����ϴ�.");
		::closesocket(hSocket);
		return 0;
	}

	//4. Ŭ���̾�Ʈ ���� ó�� �� ����
	SOCKADDR_IN clntAddr = {};
	int addrLen = sizeof(clntAddr);
	SOCKET hClient = 0; //������ſ� ����
	char szBuffer[128] = {};
	int nReceive = 0;

	//4.1 ������������ Ŭ���̾�Ʈ ������ �޾Ƶ��̰� ������ż��� ����
	while((hClient = :: accept(hSocket, (SOCKADDR*)&clntAddr, &addrLen)) != INVALID_SOCKET)
	{
		puts("Ŭ���̾�Ʈ ���ӵ�");
		//4.2 Ŭ���̾�Ʈ�κ��� ���ڿ��� ������
		while((nReceive = ::recv(hClient, szBuffer, sizeof(szBuffer) ,0)))
		{// TCP ����(�ü�� ������ ��Ʈ��ũ ����)�� ������ �����͸� ���ø����̼� ������ ������ szBuffer�� �����մϴ�.
			::send(hClient, szBuffer, nReceive, 0); //szBuffer�� ����� �����͸� �ٽ� Ŭ���̾�Ʈ�� ����
			puts(szBuffer);
			memset(szBuffer, 0, sizeof(szBuffer));
		}

		//4.3 Ŭ���̾�Ʈ�� ������ ������
		::shutdown(hClient, SD_BOTH); //SD_BOTH: �ۼ��� ��� ����
		::closesocket(hClient);
		puts("Ŭ���̾�Ʈ ���� �����");
	}

	//5. ���Ӵ�� �������� ����
	::closesocket(hSocket);

	//���� ����
	::WSACleanup();
	return 0;
}