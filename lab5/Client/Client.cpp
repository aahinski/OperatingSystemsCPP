#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<Windows.h>
#include<conio.h>
#include <set>
using namespace std;

int main(int argc, char* argv[])
{
    HANDLE end = OpenEvent(EVENT_ALL_ACCESS, FALSE, "end");
    HANDLE write = (HANDLE)atoi(argv[1]);
    HANDLE read = (HANDLE)atoi(argv[2]);
    HANDLE event = OpenEvent(SYNCHRONIZE, FALSE, "1");
    if (event == NULL) {
        GetLastError();
    }
    WaitForSingleObject(event, INFINITE);
    int M, N, n;
    DWORD s;
    ReadFile(read, &M, sizeof(M), &s, NULL);
    ReadFile(read, &N, sizeof(N), &s, NULL);
    ReadFile(read, &n, sizeof(n), &s, NULL);
    long* arr = new long[n];
    for (size_t i = 0; i < n; i++) {
        arr[i] = rand() % (M - N) + N;
    }
    cout << '\n';
    for (size_t i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    DWORD sz;
    for (size_t i = 0; i < n; i++) {
        DWORD r;
        WriteFile(write, &arr[i], sizeof(arr[i]), &r, NULL);
    }
    SetEvent(end);
    char q;
    cin >> q;
    while (q != 'q')
        cin >> q;
}