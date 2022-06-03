#include "Stack.h"
Stack st(100);
CRITICAL_SECTION cs1, cs2;

using namespace std;

DWORD WINAPI consumer(LPVOID n)
{
	EnterCriticalSection(&cs2);
	for (int i = 0; i < (int)n; i++) {
		cout << "Element consumed " << st.pop() << "\n";
	}
	LeaveCriticalSection(&cs2);
	return 0;
}DWORD WINAPI creator(LPVOID n)
{
	EnterCriticalSection(&cs1);
	for (int i = 0; i < (int)n; i++) {
		st.push((char)i);
		cout << "Element created " << (char)i << "\n";
	}
	LeaveCriticalSection(&cs1);
	return 0;
}
int main()
{
	cout << "Enter the size of stack";
	int n;
	cin >> n;
	st.maxSize = n;
	InitializeCriticalSection(&cs1);
	InitializeCriticalSection(&cs2);
	int creatorsQ;
	int consumersQ;
	cout << "Enter the quatinty of creators: ";
	cin >> creatorsQ;
	cout << "Enter the quantity of consumers: ";
	cin >> consumersQ;
	HANDLE* hConsumer = new HANDLE[consumersQ];
	HANDLE* hCreator = new HANDLE[creatorsQ];
	DWORD IDThread;

	int a;
	for (int i = 0; i < creatorsQ; i++) {
		cout << "Enter the quantity of elements to produce: ";
		cin >> a;
		hCreator[i] = CreateThread(NULL, 0, creator, (void*)a, 0, &IDThread);
		if (hCreator[i] == NULL) {
			for (int j = 0; j < i; j++) {
				CloseHandle(hCreator[j]);
			}
			delete[] hConsumer;
			delete[] hCreator;
			DeleteCriticalSection(&cs1);
			DeleteCriticalSection(&cs2);
			return GetLastError();
		}
		Sleep(10);
	}

	int b;
	for (int i = 0; i < consumersQ; i++) {
		cout << "Enter the quantity of elements to consume: ";
		cin >> b;
		hConsumer[i] = CreateThread(NULL, 0, consumer, (void*)b, 0, &IDThread);
		if (hConsumer[i] == NULL) {
			for (int j = 0; j < i; j++) {
				CloseHandle(hConsumer[j]);
			}
			delete[] hConsumer;
			delete[] hCreator;
			DeleteCriticalSection(&cs1);
			DeleteCriticalSection(&cs2);
			return GetLastError();
		}
		Sleep(10);
	}

	HANDLE* hGeneral = new HANDLE[creatorsQ + consumersQ];
	for (int i = 0; i < creatorsQ; i++) {
		hGeneral[i] = hCreator[i];
	}
	for (int i = 0; i < consumersQ; i++) {
		hGeneral[creatorsQ + i] = hConsumer[i];
	}
	WaitForMultipleObjects(consumersQ + creatorsQ, hGeneral, TRUE, INFINITE);

	for (int i = 0; i < consumersQ + creatorsQ; i++) {
		CloseHandle(hGeneral[i]);
	}
	delete[] hConsumer;
	delete[] hCreator;
	delete[] hGeneral;
	DeleteCriticalSection(&cs1);
	DeleteCriticalSection(&cs2);
	return 0;
}