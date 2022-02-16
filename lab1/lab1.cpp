#include <windows.h>
#include <iostream>
#include <process.h>

using namespace std;

struct my_struct {
    volatile int* array;
    int size;
};

my_struct object;

void worker() {
    int i = 0;
    for (;i < object.size;) {
        if (object.array[i] % 4 == 0)
            cout << object.array[i] << ' ';
        Sleep(12);
        i++;
    }
}

int main() {
    HANDLE hThread;
    DWORD IDThread;
    UINT IDThread1;

    object.size = 100;

    volatile int* array = new int[object.size];
    cout << "Array:" << ' ';

    for (int i = 0; i < object.size; i++) {
        array[i] = rand();
        cout << array[i] << ' ';
    }

    object.array = array;

    int worker_suspend_time, worker_restart_time;
    cout << "Enter worker suspend time";
    cin >> worker_suspend_time;
    cout << "Enter worker restart time";
    cin >> worker_restart_time;

    hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)worker, (my_struct*)&object, 0, &IDThread);

    if (hThread == NULL)
        return GetLastError();

    Sleep(worker_suspend_time);
    SuspendThread(hThread);
    Sleep(worker_restart_time);
    ResumeThread(hThread);
    WaitForSingleObject(hThread, INFINITE);
    TerminateThread(hThread, 0);
    CloseHandle(hThread);



    cout << "----------------------";
    hThread = (HANDLE)
        _beginthreadex(NULL, 0, (_beginthreadex_proc_type)worker, (my_struct*)&object, 0, &IDThread1);
    if (hThread == NULL)
        return GetLastError();
    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);
    hThread = (HANDLE)
        _beginthreadex(NULL, 0, (_beginthreadex_proc_type)worker, (my_struct*)&object, 0, &IDThread1);
    if (hThread == NULL)
        return GetLastError();

    return 0;
}