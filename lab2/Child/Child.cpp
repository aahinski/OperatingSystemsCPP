#include<Windows.h>
#include<conio.h>
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
    int* arr = new int[argc];
    for (int i = 0; i < argc; i++) {
        arr[i] = atoi(argv[i]);
        cout << arr[i] << ' ';
    }
    cout << '\n';
    int sum = 0;
    for (int i = 0; i < argc; i++) {
        sum += arr[i];
    }
    cout << sum << ' ';
    _getch();
}