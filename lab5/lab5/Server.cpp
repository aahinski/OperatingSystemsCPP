#include <iostream>
#include<conio.h>
#include<Windows.h>
using namespace std;

int main()
{
    HANDLE write, read;
    HANDLE end = CreateEvent(NULL, FALSE, FALSE, "end");
    if (end == NULL) {
        GetLastError();
    }
    int n;
    cout << "Enter array size \n";
    cin >> n;
    long* arr = new long[n];
    cout << "Enter N,M\n";
    int M, N;
    cin >> N >> M;
    cout << N << M;
    cout << "\n";
    DWORD size;
    HANDLE event = CreateEvent(NULL, FALSE, FALSE, "1");
    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = TRUE;
    CreatePipe(&read, &write, &sa, 0);
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    char a[80];
    wsprintf(a, "Client.exe %d %d %d", int(write), int(read), n);
    if (!CreateProcess(NULL, a, NULL, NULL, TRUE,
        CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
        GetLastError();
    }
    WriteFile(write, &M, sizeof(M), &size, NULL);
    WriteFile(write, &N, sizeof(N), &size, NULL);
    WriteFile(write, &n, sizeof(n), &size, NULL);
    SetEvent(event);

    WaitForSingleObject(end, INFINITE);
    DWORD sz;
    for (int i = 0; i < n; i++) {
        DWORD size;
        ReadFile(read, &arr[i], sizeof(arr[i]), &size, NULL);
    }
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    char q;
    cin >> q;
    while (q != 'q')
        cin >> q;
}