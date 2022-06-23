#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<Windows.h>
#include <conio.h>

int main()
{
    HANDLE eX[2];
    eX[0] = CreateEvent(NULL, FALSE, FALSE, "writer");
    eX[1] = CreateEvent(NULL, FALSE, FALSE, "reader");

    int n, m;
    std::cout << "Input number of Writer processes\n";
    std::cin >> n;
    m = n;
    HANDLE sem = CreateSemaphore(NULL, 2, 2, "semaphore");
    HANDLE* proc = new HANDLE[n + m];
    HANDLE events[2];
    HANDLE eventsR[2];

    eventsR[0] = CreateEvent(NULL, FALSE, FALSE, "r1");
    eventsR[1] = CreateEvent(NULL, FALSE, FALSE, "r2");
    HANDLE mut;
    DWORD* id = new DWORD[n + m];
    STARTUPINFO* st = new STARTUPINFO[n + m];
    PROCESS_INFORMATION* pi = new PROCESS_INFORMATION[n + m];
    char p[2];

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
    DWORD ind;
    for (int i = 0; i < m; i++) {
        ind = WaitForMultipleObjects(2, eventsR, FALSE, INFINITE);

        if (ind == 0) {
            std::cout << "A" << std::endl;
        }
        else {
            std::cout << "B" << std::endl;
        }
    }
    Sleep(100);
    
    for (int i = 0; i < n + m; i++) {
        ind = WaitForMultipleObjects(2, eX, FALSE, INFINITE);
        if (ind == 0) {
            std::cout << "Reader ended his work\n";
        }
        else {
            std::cout << "Writer ended his work\n";
        }
    }
    _getch();
}