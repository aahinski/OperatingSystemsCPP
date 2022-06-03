#include "Stack.h"

Stack::~Stack() {
	delete[] stack;
	CloseHandle(hPopSemaphore);
	CloseHandle(hPushSemaphore);
}

void Stack::push(char c) {
	WaitForSingleObject(hPushSemaphore, INFINITE);
	ReleaseSemaphore(hPopSemaphore, 1, NULL);
	stack[realSize] = c;
	realSize++;
}

char Stack::pop() {
	WaitForSingleObject(hPopSemaphore, INFINITE);
	ReleaseSemaphore(hPushSemaphore, 1, NULL);
	realSize--;
	return stack[realSize];
}