#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    int prev;

    set<array<int,2>> s;

    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        if(i) {
            s.insert({min(num,prev),max(num,prev)});
        }
        prev = num;
    }
    bool ok = 1;

    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        if(i) {
            if(s.count({min(num,prev),max(num,prev)}) == 0) {
                ok = 0;
            }
        }
        prev = num;
    }

    cout << (ok ? "Bob" : "Alice") << '\n';


}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}