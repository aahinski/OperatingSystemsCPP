#include<windows.h>
#include <iostream>
#include<time.h>
#include<random>
using namespace std;
int main()
{
	char 	c;	// ��������� ������
	SECURITY_ATTRIBUTES sa;	// �������� ������
	SECURITY_DESCRIPTOR sd;	// ���������� ������
	HANDLE 	hNamedPipe;
	DWORD 	dwBytesRead;		// ��� ����� ����������� ����
	DWORD 	dwBytesWrite;		// ��� ����� ���������� ����
	int n;
	printf("Enter array dimension :\t");
	cin >> n;
	long* a = new long[n];
	cout << "Enter N,M\n";
	int M, N;
	cin >> N >> M;
	cout << N << M;
	cout << "\n";
	// ������������� ��������� ������
	sa.nLength = sizeof(sa);
	sa.bInheritHandle = FALSE;	// ���������� ������ �������������
	// �������������� ���������� ������
	InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);
	// ������������� �������� ������, �������� ������ ���� �������������
	SetSecurityDescriptorDacl(&sd, TRUE, NULL, FALSE);
	sa.lpSecurityDescriptor = &sd;
	// ������� ����������� ����� ��� ������
	hNamedPipe = CreateNamedPipeA(
		"\\\\.\\pipe\\demo_pipe",	// ��� ������
		PIPE_ACCESS_DUPLEX,		// ������ �� ������ � ����� � �����
		PIPE_TYPE_MESSAGE | PIPE_WAIT,	// ���������� �������� ���������
		1,		// ������������ ���������� ����������� ������ 
		0,		// ������ ��������� ������ �� ���������
		0,		// ������ �������� ������ �� ���������
		INFINITE,	// ������ ���� ����� 500 ��
		&sa		// ������ ��� ���� �������������
	);

	if (hNamedPipe == INVALID_HANDLE_VALUE)
	{
		cerr << "Creation of the named pipe failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		cout << "Press any char to finish server: ";
		cin >> c;
		return 0;
	}

	cout << "The server is waiting for connection with a client." << endl;
	if (!ConnectNamedPipe(
		hNamedPipe,
		(LPOVERLAPPED)NULL
	))
	{
		cerr << "The connection failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		CloseHandle(hNamedPipe);
		cout << "Press any char to finish the server: ";
		cin >> c;
		return 0;
	}
	if (!WriteFile(
		hNamedPipe,
		&n,
		sizeof(int),
		&dwBytesWrite,
		(LPOVERLAPPED)NULL
	))
	{
		cerr << "Data writing to the named pipe failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		CloseHandle(hNamedPipe);
		cout << "Press any char to finish the server: ";
		cin >> c;
		return (0);
	}
	if (!WriteFile(
			hNamedPipe,
			&N,
			sizeof(int),
			&dwBytesWrite,
			(LPOVERLAPPED)NULL
	))
	{
		cerr << "Data writing to the named pipe failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		CloseHandle(hNamedPipe);
		cout << "Press any char to finish the server: ";
		cin >> c;
		return (0);
	}
	if (!WriteFile(
				hNamedPipe,
				&M,
				sizeof(int),
				&dwBytesWrite,
				(LPOVERLAPPED)NULL
	))
	{
		cerr << "Data writing to the named pipe failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		CloseHandle(hNamedPipe);
		cout << "Press any char to finish the server: ";
		cin >> c;
		return (0);
	}


	if (!ReadFile(
		hNamedPipe,
		a,
		n * sizeof(long),
		&dwBytesRead,
		(LPOVERLAPPED)NULL
	))
	{
		cerr << "Data reading from the named pipe failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		CloseHandle(hNamedPipe);
		cout << "Press any char to finish the server: ";
		cin >> c;
		return (0);
	}

	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
	char q;
	cin >> q;
	while (q != 'q')
		cin >> q;

	CloseHandle(hNamedPipe);
	delete[] a;
	return 0;
}