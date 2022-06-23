#include<iostream>
#include<windows.h>

int comp(const _int8* i, const _int8* j) {
    return *i - *j;
}

int main() {
    char 	c;
    HANDLE 	hNamedPipe;
    char 	pipeName[80];
    DWORD 	dwBytesWritten;
    DWORD 	dwBytesRead;
    printf("Waiting for connection with Server ...\n");
    wsprintfA(pipeName, "\\\\%s\\pipe\\demo_pipe", "машина-каша");

    hNamedPipe = CreateFileA(
            pipeName,				// имя канала
            GENERIC_READ | GENERIC_WRITE,		// читаем и записываем в канал
            FILE_SHARE_READ | FILE_SHARE_WRITE,	// разрешаем чтение и запись в канал
            (LPSECURITY_ATTRIBUTES)NULL,		// защита по умолчанию
            OPEN_EXISTING,				// открываем существующий канал
            FILE_ATTRIBUTE_NORMAL,			// атрибуты по умолчанию
            (HANDLE)NULL				// дополнительных атрибутов нет
    );
    if (hNamedPipe == INVALID_HANDLE_VALUE) {
        std::cerr << "Connection with the named pipe failed." << std::endl
             << "The last error code: " << GetLastError() << std::endl;
        std::cout << "Press any char to finish the client: ";
        std::cin >> c;
        return (0);
    }
    
    int M, N, n;
    if (!ReadFile(
            hNamedPipe,
            &n,
            sizeof(int),
            &dwBytesRead,
            (LPOVERLAPPED)NULL
    ))
    {
        std::cerr << "Data reading from the named pipe failed." << std::endl
             << "The last error code: " << GetLastError() << std::endl;
        CloseHandle(hNamedPipe);
        std::cout << "Press any char to finish the server: ";
        std::cin >> c;
        return (0);
    }
    
    if (!ReadFile(
            hNamedPipe,
            &N,
            sizeof(int),
            &dwBytesRead,
            (LPOVERLAPPED)NULL
    ))
    {
        std::cerr << "Data reading from the named pipe failed." << std::endl
             << "The last error code: " << GetLastError() << std::endl;
        CloseHandle(hNamedPipe);
        std::cout << "Press any char to finish the server: ";
        std::cin >> c;
        return (0);
    }
    
    if (!ReadFile(
            hNamedPipe,
            &M,
            sizeof(int),
            &dwBytesRead,
            (LPOVERLAPPED)NULL
    ))
    {
        std::cerr << "Data reading from the named pipe failed." << std::endl
             << "The last error code: " << GetLastError() << std::endl;
        CloseHandle(hNamedPipe);
        std::cout << "Press any char to finish the server: ";
        std::cin >> c;
        return (0);
    }
    
    long* a = new long[n];
    printf("Array:\n");
    for (size_t i = 0; i < n; i++) {
        a[i] = rand() % (M - N) + N;
    }
    std::cout << '\n';
    for (size_t i = 0; i < n; i++) {
        std::cout << a[i] << " ";
    }
    
    if (!WriteFile(
            hNamedPipe,
            a,
            sizeof(long) * n,
            &dwBytesWritten,
            (LPOVERLAPPED)NULL
    ))
    {
        std::cerr << "Data writing to the named pipe failed." << std::endl
             << "The last error code: " << GetLastError() << std::endl;
        CloseHandle(hNamedPipe);
        std::cout << "Press any char to finish the server: ";
        std::cin >> c;
        return (0);
    }
    
    printf("Press any key to continue.");
    std::cin.get();
    char q;
    std::cin >> q;
    while (q != 'q') {
        std::cin >> q;
    }
    delete[] a;
}