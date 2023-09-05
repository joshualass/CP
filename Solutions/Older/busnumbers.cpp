#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
// int ary[400001] = {};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int m; cin >> m;
    vector<int> ary (400001);
    for(int l = 1; l * l * l <= 400000; l++) {
        for(int r = l; l * l * l + r * r * r <= 400000; r++) {
            ary[l * l * l + r * r * r]++;
        }
    }
    int num = 0;
    for(int i = m; i > 0; i--) {
        if(ary[i] >= 2) {
            num = i;
            break;
        }
    }
    cout << (num == 0 ? "none" : to_string(num));

    return 0;
}