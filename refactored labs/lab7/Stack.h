#pragma once
#include<windows.h>
#include<iostream>

class Stack
{
	char* stack;
	int realSize;
	HANDLE hPushSemaphore;
	HANDLE hPopSemaphore;

	public:

	int maxSize;

	Stack(int size) : realSize(0), maxSize(size) {
		hPushSemaphore = CreateSemaphore(NULL, maxSize, maxSize, NULL);
		hPopSemaphore = CreateSemaphore(NULL, 0, maxSize, NULL);
		stack = new char[size];
	}

	~Stack();
	void push(char c);
	char pop();
};