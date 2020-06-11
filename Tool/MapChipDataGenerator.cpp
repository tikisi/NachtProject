#include<iostream>
using namespace std;

using uint32 = unsigned int;

class MapChipData{
public:
    uint32 ef;
    uint32 at;
    uint32 hi;
    uint32 sp;
    uint32 gc;

    MapChipData() = default;
    operator uint32() const noexcept {
        return gc | sp << 16 | hi << 19 |
            at << 27 | ef << 28;
    } 
};

int main() {
    MapChipData m;

    cout << "ef: ";
    cin >> m.ef;
    cout << "at: ";
    cin >> m.at;
    cout << "hi: ";
    cin >> m.hi;
    cout << "sp: ";
    cin >> m.sp;
    cout << "gc: ";
    cin >> m.gc;

    cout << (uint32)m << endl;

    return 0;
}