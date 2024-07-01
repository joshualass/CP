#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    string s; cin >> s;
    int length = 0;
    int maxsort = 0;
    bool ok = 1;
    int unsorted = -1;
    for(char c : s) {
        if(c == '+') {
            length++;
        } else if(c == '-') {
            length--;
            maxsort = min(maxsort,length);
            if(unsorted > length) unsorted = -1;
        } else if(c == '0') {
            if(maxsort == length || length == 1) {
                ok = 0;
            } else if(unsorted == -1) {
                unsorted = length;
            }
        } else if(c == '1') {
            if(unsorted != -1) {
                ok = 0;
            } else {
                maxsort = length;
            }
        }
    }
    cout << (ok ? "YES" : "NO") << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}
