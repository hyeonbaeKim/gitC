// WorkerThreadCreate.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>

DWORD WINAPI ThreadFunction(LPVOID data) //LPVOID는 void*와 동일 , DWORD는 unsigned long과 동일
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
	//새로운 스레드를 생성한다.
	
	HANDLE hThread = CreateThread( //- ★CreateThread는 작업자 스레드를 생성만 할 뿐, 그 스레드가 언제 실행될지는 운영체제의 스케줄러가 결정합니다.
		NULL,                   // 보안속성을 상속받는다.
		0,                      // use default stack size  
		ThreadFunction,        // thread function name
		NULL,          // argument to thread function 
		0,                      // use default creation flags 
		&dwThreadId);   // returns the thread identifier

	for(int i=0; i < 10; i++) 
		printf("Main thread is running...%d\n", i);

	::CloseHandle(hThread);
	::Sleep(10); //- 메인 스레드에게 10밀리초 동안 CPU를 양보하라는 의미입니다.
	return 0;
}
// sleep이 없을 때
//- 메인 스레드는 멈추지 않고 계속 실행되므로, 작업자 스레드와 경쟁적으로 CPU를 사용합니다.
//- 이로 인해 두 스레드가 서로 번갈아가며 실행되며, 출력이 섞이게 됩니다.

//Sleep(10); 이 있을 때
//- 메인 스레드는 마지막에 Sleep(10); 을 호출하면서 잠깐 멈춥니다.
//- 이 시간 동안 작업자 스레드는 CPU를 더 많이 사용할 수 있어서 메인 스레드보다 늦게 시작되지만, 연속적으로 실행될 수 있습니다.
//- 결과적으로 메인 스레드가 먼저 10번 출력되고, 그 다음에 작업자 스레드가 실행됩니다.

//for (int i = 0; i < 10; i++)
//	printf("Main thread is running...%d\n", i);
//
//Sleep(10);
//
//이 코드는 메인 스레드가 루프를 다 돌고 나서 10ms 동안 잠깐 쉰다는 뜻입니다.하지만 그 전에 작업자 스레드가 먼저 실행될 수도 있는 이유는 :
//-CreateThread 직후 작업자 스레드가 즉시 스케줄링될 수 있음
//- 메인 스레드가 for 루프를 시작하기 전에 작업자 스레드가 먼저 CPU를 받음
//즉, Sleep(10)은 루프 이후에 실행되지만, 작업자 스레드가 먼저 실행되는 것과는 직접적인 관련이 없습니다.

//이런 실행 순서를 정확하게 제어하고 싶다면, WaitForSingleObject, Event, CriticalSection 같은 동기화 도구를 사용해야 해요.






