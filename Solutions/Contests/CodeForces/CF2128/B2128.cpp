#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n; cin >> n;
    deque<int> d;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        d.push_back(x);
    }

    int p = 0;
    while(d.size() >= 2) {
        int f = d.front(), b = d.back();
        string res = "";
        if(f > p && b > p) {
            if(f > b) {
                res = "LR";
            } else {
                res = "RL";
            }
        } else if(f < p && b < p) {
            if(f < b) {
                res = "LR";
            } else {
                res = "RL";
            }
        } else {
            if(f > b) {
                res = "LR";
            } else {
                res = "RL";
            }
        }
        if(res == "LR") {
            p = d.back();
        } else {
            p = d.front();
        }
        d.pop_front();
        d.pop_back();
        assert(res == "LR" || res == "RL");
        cout << res;
    }
    if(d.size()) cout << 'L';
    cout << "\n";

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}