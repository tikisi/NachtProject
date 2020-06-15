#include<iostream>
using namespace std;
using uint16 = unsigned short;

int main() {
    uint16 cliff;
    uint16 ladder;

    cout << "cliff: ";
    cin >> cliff;
    cout << "ladder: ";
    cin >> ladder;

    cout << (ladder | (cliff << 8)) << endl;
}