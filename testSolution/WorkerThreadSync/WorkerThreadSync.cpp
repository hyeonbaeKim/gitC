#include <iostream>
#include <Windows.h>

DWORD WINAPI ThreadFunction(LPVOID pParam) //LPVOID�� void*�� ���� , DWORD�� unsigned long�� ����
{
	puts("*** Thread started ***");

	for (int i = 0; i < 10; i++)
	{
		printf("Thread is running...%d\n", i);
		::Sleep(1); //- �۾��� �����忡�� 1�и��� ���� CPU�� �纸�϶�� �ǹ��Դϴ�.
	}

	//�����尡 ������ ���� �̺�Ʈ�� ��Ʈ
	puts("���� �̺�Ʈ ��Ʈ ��");
	//�� �Լ��� ȣ���ϸ� main�Լ��� WaitForSingleObject�� ����ϴ�.
	::SetEvent(pParam);
	puts("���� �̺�Ʈ ��Ʈ ��");
	puts("*** Thread ended ***");
	return 0;
}

int main()
{
	//�̺�Ʈ ��ü ����
	HANDLE hEvent = ::CreateEvent(
		NULL, //���ȼӼ�
		FALSE, //�ڵ����� ���� ��ȯ
		FALSE, //�ʱ� ���´� false
		NULL); //�̺�Ʈ �̸� ����

	DWORD dwThreadId = 0;

	HANDLE hThread = CreateThread( 
		NULL,                   
		0,                     
		ThreadFunction,        
		hEvent,          // ��argument to thread function 
		0,                      
		&dwThreadId);   

	for (int i = 0; i < 10; i++)
	{
		printf("Main thread is running...%d\n", i);
		//i���� 3�̸� �̺�Ʈ�� ��Ʈ�Ǳ⸦ ������ ��ٸ���
		if(i == 3 && ::WaitForSingleObject(hEvent, INFINITE) == WAIT_OBJECT_0)
		{
			//�̺�Ʈ�� ��Ʈ�� ���
			puts("�����̺�Ʈ�� �����߽��ϴ�.");
			::CloseHandle(hEvent);
			hEvent = NULL;
		}
	}

	::CloseHandle(hThread);
	return 0;
}