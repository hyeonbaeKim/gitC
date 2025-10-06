#include <iostream>
#include <Windows.h>

DWORD WINAPI ThreadFunction(LPVOID pParam) //LPVOID는 void*와 동일 , DWORD는 unsigned long과 동일
{
	puts("*** Thread started ***");

	for (int i = 0; i < 10; i++)
	{
		printf("Thread is running...%d\n", i);
		::Sleep(1); //- 작업자 스레드에게 1밀리초 동안 CPU를 양보하라는 의미입니다.
	}

	//쓰레드가 끝나기 전에 이벤트를 세트
	puts("종료 이벤트 세트 전");
	//이 함수를 호출하면 main함수의 WaitForSingleObject가 깨어납니다.
	::SetEvent(pParam);
	puts("종료 이벤트 세트 후");
	puts("*** Thread ended ***");
	return 0;
}

int main()
{
	//이벤트 객체 생성
	HANDLE hEvent = ::CreateEvent(
		NULL, //보안속성
		FALSE, //자동으로 상태 전환
		FALSE, //초기 상태는 false
		NULL); //이벤트 이름 없음

	DWORD dwThreadId = 0;

	HANDLE hThread = CreateThread( 
		NULL,                   
		0,                     
		ThreadFunction,        
		hEvent,          // ★argument to thread function 
		0,                      
		&dwThreadId);   

	for (int i = 0; i < 10; i++)
	{
		printf("Main thread is running...%d\n", i);
		//i값이 3이면 이벤트가 세트되기를 무한정 기다린다
		if(i == 3 && ::WaitForSingleObject(hEvent, INFINITE) == WAIT_OBJECT_0)
		{
			//이벤트가 세트된 경우
			puts("종료이벤트를 감지했습니다.");
			::CloseHandle(hEvent);
			hEvent = NULL;
		}
	}

	::CloseHandle(hThread);
	return 0;
}