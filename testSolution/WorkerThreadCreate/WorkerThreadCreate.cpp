// WorkerThreadCreate.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>

DWORD WINAPI ThreadFunction(LPVOID data) //LPVOID�� void*�� ���� , DWORD�� unsigned long�� ����
{
	puts("*** Thread started ***");
	
	for(int i =0; i < 10; i++) 
		printf("Thread is running...%d\n",i);

	puts("*** Thread ended ***");
	return 0;
}

int main()
{
	DWORD dwThreadId = 0;
	//���ο� �����带 �����Ѵ�.
	
	HANDLE hThread = CreateThread( //- ��CreateThread�� �۾��� �����带 ������ �� ��, �� �����尡 ���� ��������� �ü���� �����ٷ��� �����մϴ�.
		NULL,                   // ���ȼӼ��� ��ӹ޴´�.
		0,                      // use default stack size  
		ThreadFunction,        // thread function name
		NULL,          // argument to thread function 
		0,                      // use default creation flags 
		&dwThreadId);   // returns the thread identifier

	for(int i=0; i < 10; i++) 
		printf("Main thread is running...%d\n", i);

	::CloseHandle(hThread);
	::Sleep(10); //- ���� �����忡�� 10�и��� ���� CPU�� �纸�϶�� �ǹ��Դϴ�.
	return 0;
}
// sleep�� ���� ��
//- ���� ������� ������ �ʰ� ��� ����ǹǷ�, �۾��� ������� ���������� CPU�� ����մϴ�.
//- �̷� ���� �� �����尡 ���� �����ư��� ����Ǹ�, ����� ���̰� �˴ϴ�.

//Sleep(10); �� ���� ��
//- ���� ������� �������� Sleep(10); �� ȣ���ϸ鼭 ��� ����ϴ�.
//- �� �ð� ���� �۾��� ������� CPU�� �� ���� ����� �� �־ ���� �����庸�� �ʰ� ���۵�����, ���������� ����� �� �ֽ��ϴ�.
//- ��������� ���� �����尡 ���� 10�� ��µǰ�, �� ������ �۾��� �����尡 ����˴ϴ�.

//for (int i = 0; i < 10; i++)
//	printf("Main thread is running...%d\n", i);
//
//Sleep(10);
//
//�� �ڵ�� ���� �����尡 ������ �� ���� ���� 10ms ���� ��� ���ٴ� ���Դϴ�.������ �� ���� �۾��� �����尡 ���� ����� ���� �ִ� ������ :
//-CreateThread ���� �۾��� �����尡 ��� �����ٸ��� �� ����
//- ���� �����尡 for ������ �����ϱ� ���� �۾��� �����尡 ���� CPU�� ����
//��, Sleep(10)�� ���� ���Ŀ� ���������, �۾��� �����尡 ���� ����Ǵ� �Ͱ��� �������� ������ �����ϴ�.

//�̷� ���� ������ ��Ȯ�ϰ� �����ϰ� �ʹٸ�, WaitForSingleObject, Event, CriticalSection ���� ����ȭ ������ ����ؾ� �ؿ�.






