/*
2026 ICPC Asia Pacific Championship
Problem K
Time Display Stickers
*/

#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;
    string s; cin >> s;
    vector<int> cnts(10);
    for(char c : s) cnts[c - '0']++;

    int l = 0, r = n / 4;
    while(l != r) {
        int m = (l + r + 1) / 2;
        vector<int> t = cnts;
        int need_last = m;
        for(int j = 9; j >= 0; j--) {
            int sub = min(need_last, t[j]);
            need_last -= sub;
            t[j] -= sub;
        }
        if(need_last) {
            r = m - 1;
            continue;
        }
        need_last = m;
        for(int j = 5; j >= 0; j--) {
            int sub = min(need_last, t[j]);
            need_last -= sub;
            t[j] -= sub;
        }
        if(need_last) {
            r = m - 1;
            continue;
        }
        int rem = 0;
        rem += t[1] / 2;
        t[1] &= 1;
        rem += min(t[0], accumulate(t.begin(), t.end(), 0) / 2);
        if(rem >= m) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    cout << l << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}