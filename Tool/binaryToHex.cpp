#include<iostream>
#include<string>
#include<cmath>
using namespace std;
using uint32 = unsigned int;

uint32 ctoi(char c) {
	switch (c) {
		case '0': return 0;
		case '1': return 1;
	}

	return 0;
}

uint32 Dec(string s) {
    uint32 value = 0;
    for(int i = 0; i <= s.size(); ++i) {
        value += pow(2, i) * ctoi(s[s.size() - i - 1]);
    }

    return value;
}

int main() {
    string s;
	cin >> s;

    cout << hex << Dec(s) << endl;
}