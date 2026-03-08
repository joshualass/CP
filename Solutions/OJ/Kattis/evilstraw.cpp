#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    string s; cin >> s;
    int res = 0;
    while(s.size() >= 2) {
        int ops = INT_MAX;
        char best = '\0';
        for(char c = 'a'; c <= 'z'; c++) {
            size_t first = s.find_first_of(c), last = s.find_last_of(c);
            if(first != string::npos && first != last) {
                int t = first + sz(s) - (last + 1);
                if(t < ops) {
                    ops = t;
                    best = c;
                }
            }
        }
        if(best == '\0') {
            cout << "Impossible" << '\n';
            return;
        }
        res += ops;
        s.erase(s.begin() + s.find_last_of(best));
        s.erase(s.begin() + s.find_first_of(best));
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}