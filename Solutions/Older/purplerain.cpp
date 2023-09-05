#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string line;
    cin >> line;
    int red = 0;
    int ri = 0;
    int rm = 0;
    pair<int, int> rb;
    int blue = 0;
    int bi = 0;
    int bm = 0;
    pair<int, int> bb;

    for (int i = 0; i < line.size(); i++) {
        char c = line[i];
        if (c == 'B') {
            blue++;
            if (blue > bm) {
                bm = blue;
                bb = {bi, i};
            }
        } else {
            if (blue == 0) {
                bi = i + 1;
            } else {
                blue--;
            }
        }
        if (c == 'R') {
            red++;
            if (red > rm) {
                rm = red;
                rb = {ri, i};
            }
        } else {
            if (red == 0) {
                ri = i + 1;
            } else {
                red--;
            }
        }
    }

    if (rm == bm) {
        if (rb.first < bb.first) {
            cout << rb.first + 1 << " " << rb.second + 1;
        } else {
            cout << bb.first + 1 << " " << bb.second + 1;
        }
    } else if (rm > bm) {
        cout << rb.first + 1 << " " << rb.second + 1;
    } else {
        cout << bb.first + 1 << " " << bb.second + 1;
    }

    return 0;
}