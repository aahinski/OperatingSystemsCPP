#include <windows.h>
#include <iostream>
#include <process.h>

struct Array {
    long* array;
    int size;
};

void worker(Array* object) {
    std::cout << "\n" << "Numbers in the array divided by four:" << "\n";
    for (int i = 0; i < object->size; i++) {
        if (object->array[i] % 4 == 0)
            std::cout << object->array[i] << "\n";
        Sleep(12);
    }
}

int main() {
    HANDLE hThread;
    DWORD IDThread;
    UINT IDThread1;

    Array object;
    object.size;
    std::cout << "Enter array size:" << "\n";
    std::cin >> object.size;
    std::cout << "\n";

    long* array = new long[object.size];
    std::cout << "Array:" << "\n";

    for (int i = 0; i < object.size; i++) {
        array[i] = rand();
        std::cout << array[i] << "\n";
    }

    object.array = array;
    std::cout << "\n";

    int worker_suspend_time, worker_restart_time;
    std::cout << "Enter worker suspend time"; // время работы worker до остановки
    std::cin >> worker_suspend_time;
    std::cout << "Enter worker resume time"; // время, пока worker "спит" до возобновления
    std::cin >> worker_restart_time;

    hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)worker, (Array*)&object, 0, &IDThread);

    if (hThread == NULL)
        return GetLastError();

    Sleep(worker_suspend_time);
    SuspendThread(hThread);
    Sleep(worker_restart_time);
    ResumeThread(hThread);
    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);


    //Запуск потока с использованием _beginthreadex
    std::cout << "\n";
    std::cout << "-------------------------------------------";
    std::cout << "\n";

    hThread = (HANDLE)
        _beginthreadex(NULL, 0, (_beginthreadex_proc_type)worker, (Array*)&object, 0, &IDThread1);
    if (hThread == NULL)
        return GetLastError();
    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);

    return 0;
}