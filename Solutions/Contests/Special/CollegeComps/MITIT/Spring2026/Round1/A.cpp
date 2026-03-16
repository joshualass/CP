#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;
    string s; cin >> s;
    if(count(s.begin(), s.end(), 'M') != 1 || count(s.begin(), s.end(), 'I') != n || count(s.begin(), s.end(), 'T') != n) {
        cout << "-1\n";
        return;
    }

    auto is_good = [&]() -> bool {
        int ok = 1;
        if(s[0] != 'M') ok = 0;
        for(int i = 2; i < sz(s); i += 2) {
            if(s[i-1] != 'I' || s[i] != 'T') ok = 0;
        }
        return ok;
    };

    if(is_good()) {
        cout << "0\n";
        return;
    }

    rotate(s.begin(), s.begin() + s.find_first_of('M'), s.end());
    
    cout << (is_good() ? 1 : -1) << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}