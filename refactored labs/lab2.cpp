#include<Windows.h>
#include<conio.h>
#include <iostream>

int main(int argc, char* argv[]) {
    int* arr = new int[argc];
    for (int i = 0; i < argc; i++) {
        arr[i] = atoi(argv[i]);
        std::cout << arr[i] << ' ';
    }
    std::cout << '\n';
    int sum = 0;
    for (int i = 0; i < argc; i++) {
        sum += arr[i];
    }
    std::cout << sum << ' ';
    _getch();
}