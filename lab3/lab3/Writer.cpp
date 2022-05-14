#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<Windows.h>
#include <conio.h>


int main()
{
	HANDLE events_P[5];
	char p_P[2];
	for (size_t i = 0; i < 5; i++)
	{
		_itoa(i + 1, p_P, 10);
		events_P[i] = (HANDLE)CreateEvent(NULL, FALSE, FALSE, p_P);
		if (events_P[i] == NULL) {
			GetLastError();
		}
	}
	HANDLE sem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, "semaphore");
	if (sem == NULL) {
		GetLastError();
	}
	bool b;
	WaitForSingleObject(sem, INFINITE);

	HANDLE events[4];
	char p[2];
	for (size_t i = 0; i < 4; i++)
	{
		_itoa(i + 1, p, 10);
		events[i] = OpenEvent(SYNCHRONIZE, FALSE, p);
		if (events[i] == NULL) {
			GetLastError();
		}
	}
	DWORD ind;
	ind = WaitForMultipleObjects(4, events, FALSE, INFINITE);
	std::cout << "Message" << ind << '\n' << "From Admin to Writer";
	SetEvent(events_P[ind + 1]);
	_getch();
	ReleaseSemaphore(sem, 1, NULL);
}