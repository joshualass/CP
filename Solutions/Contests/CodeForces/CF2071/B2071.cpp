#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

bool issquare(ll x) {
    ll sq = sqrt(x);
    while(sq * sq < x) sq++;
    while(sq * sq > x) sq--;
    return sq * sq == x;
}

void solve() {
    int n; cin >> n;
    
    int ok = 1;
    vector<int> res;
    set<int> s;
    for(int i = 1; i <= n; i++) {
        s.insert(i);
    }

    ll sum = 0;

    while(s.size() && ok) {
        int val = -1;
        for(int x : s) {
            if(!issquare(sum + x)) {
                val = x;
                break;
            }
        }
        if(val == -1) {
            ok = 0;
            break;
        }
        res.push_back(val);
        s.erase(val);
        sum += val;
    }

    if(ok) {
        for(int i = 0; i < n; i++) {
            cout << res[i] << " \n"[i == n - 1];
        }
    } else {
        cout << "-1\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}