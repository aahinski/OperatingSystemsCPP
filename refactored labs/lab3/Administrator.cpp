#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<Windows.h>
#include <conio.h>

int main() 
{
    int n, m;
    std::cout << "Input number of Reader processes\n";
    std::cin >> n;
    std::cout << "Input number of Writer processes\n";
    std::cin >> m;
    HANDLE sem = CreateSemaphore(NULL, 2, 2, "semaphore");
    HANDLE* proc = new HANDLE[n + m];
    HANDLE events[2];
    HANDLE mut;
    DWORD* id = new DWORD[n + m];
    STARTUPINFO* st = new STARTUPINFO[n + m];
    PROCESS_INFORMATION* pi = new PROCESS_INFORMATION[n + m];
    char p[2];
    p[0] = 'A';
    p[1] = 'B';
    for (size_t i = 0; i < 2; i++) {
        events[i] = (HANDLE)CreateEvent(NULL, FALSE, FALSE, p);
        if (events[i] == NULL) {
            GetLastError();
        }
    }
    mut = CreateMutex(NULL, FALSE, "mutex");
    if (mut == NULL) {
        GetLastError();
    }
    for (int i = 0; i < n; i++) {
        ZeroMemory(&st[i], sizeof(STARTUPINFO));
        st[i].cb = sizeof(STARTUPINFO);
        CreateProcess(NULL, (LPSTR)("Writer.exe"), NULL, NULL, FALSE,
                      CREATE_NEW_CONSOLE, NULL, NULL, &st[i], &pi[i]);
    }
    for (size_t i = n; i < n + m; i++) {
        ZeroMemory(&st[i], sizeof(STARTUPINFO));
        st[i].cb = sizeof(STARTUPINFO);
        CreateProcess(NULL, (LPSTR)("Reader.exe"), NULL, NULL, FALSE,
                      CREATE_NEW_CONSOLE, NULL, NULL, &st[i], &pi[i]);
    }
    int messageNumber;
    for (int i = 0; i < n; i++) {
        std::cout << "Input message 1 or 2\n";
        std::cin >> messageNumber;
        SetEvent(events[messageNumber - 1]);
    }

    _getch();
}