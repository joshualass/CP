#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int p, n; cin >> p >> n;
    set<string> bad;
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        bad.insert(s);
    }
    for(int i = 0; i < p; i++) {
        int cnt; cin >> cnt;
        int ok = 1;
        for(int j = 0; j < cnt; j++) {
            string s; cin >> s;
            if(bad.count(s)) ok = 0;
        }
        if(ok) cout << i + 1 << " ";
    }
    cout << '\n';

    return 0;
}
