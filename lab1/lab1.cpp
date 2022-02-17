#include <windows.h>
#include <iostream>
#include <process.h>

using namespace std;

struct mystruct {
    long* array;
    int size;
};

mystruct object;

void worker() {
    cout << "\n" << "Numbers in the array divided by four:" << "\n";
    for (int i = 0; i < object.size; i++) {
        if (object.array[i] % 4 == 0)
            cout << object.array[i] << "\n";
        Sleep(12);
        i++;
    }
}

int main() {
    HANDLE hThread;
    DWORD IDThread;
    UINT IDThread1;

    object.size;
    cout << "Enter array size:" << "\n";
    cin >> object.size;
    cout << "\n";

    long* array = new long[object.size];
    cout << "Array:" << "\n";

    for (int i = 0; i < object.size; i++) {
        array[i] = rand();
        cout << array[i] << "\n";
    }

    object.array = array;
    cout << "\n";

    int worker_suspend_time, worker_restart_time;
    cout << "Enter worker suspend time"; // время работы worker до остановки
    cin >> worker_suspend_time;
    cout << "Enter worker resume time"; // время, пока worker "спит" до возобновления
    cin >> worker_restart_time;

    hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)worker, (mystruct*)&object, 0, &IDThread);

    if (hThread == NULL)
        return GetLastError();

    Sleep(worker_suspend_time);
    SuspendThread(hThread);
    Sleep(worker_restart_time);
    ResumeThread(hThread);
    WaitForSingleObject(hThread, INFINITE);
    TerminateThread(hThread, 0);
    CloseHandle(hThread);


    //Запуск потока с использованием _beginthreadex
    cout << "\n";
    cout << "-------------------------------------------";
    cout << "\n";

    hThread = (HANDLE)
        _beginthreadex(NULL, 0, (_beginthreadex_proc_type)worker, (mystruct*)&object, 0, &IDThread1);
    if (hThread == NULL)
        return GetLastError();
    WaitForSingleObject(hThread, INFINITE);
    TerminateThread(hThread, 0);
    CloseHandle(hThread);

    return 0;
}