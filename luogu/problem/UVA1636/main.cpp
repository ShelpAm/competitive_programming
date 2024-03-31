#include <iostream>
#include <string>
using namespace std;
int main()
{
    string s;
    while (cin >> s) {
        int ones = 0;
        for (auto ch: s) {
            if (ch == '1') {
                ++ones;
            }
        }
        int zeros = s.size() - ones;
        double rotate = static_cast<double>(zeros) / (ones + zeros);
        double shoot = 0;
        for (int i = 0; i != s.size(); ++i) {
            if (s[i] == '0' && s[(i + 1) % s.size()] == '0') {
                ++shoot;
            }
        }
        shoot /= zeros;
        if (rotate == shoot) {
            cout << "EQUAL\n";
        }
        else if (rotate > shoot) {
            cout << "ROTATE\n";
        }
        else {
            cout << "SHOOT\n";
        }
    }
    return 0;
}
