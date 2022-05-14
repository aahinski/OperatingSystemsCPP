// Child.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<Windows.h>
#include <conio.h>
using namespace std;

int main()
{
	HANDLE mut = OpenMutex(SYNCHRONIZE, FALSE, "mutex");
	WaitForSingleObject(mut, INFINITE);
	HANDLE events[5];
	char p[2];
	for (size_t i = 0; i < 5; i++)
	{
		_itoa(i + 1, p, 10);
		events[i] = OpenEvent(SYNCHRONIZE, FALSE, p);
		if (events[i] == NULL) {
			GetLastError();
		}
	}
	DWORD ind;
	ind = WaitForMultipleObjects(4, events, FALSE, INFINITE);
	std::cout << "Message" << ind << '\n' << "From Admin to Reader";
	_getch();
	ReleaseMutex(mut);

}