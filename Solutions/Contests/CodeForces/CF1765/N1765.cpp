#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    
    string x; cin >> x;
    int n = sz(x);

    int k; cin >> k;

    vector<int> inc(n);
    int cur = 0;

    vector<vector<int>> idxs(10);

    for(int i = 0; i < n; i++) {
        idxs[x[i] - '0'].push_back(i);
    }

    while(cur < n) {
        int f = 0;
        // cout << "k : " << k << endl;
        for(int i = (cur ? 0 : 1); i < 10; i++) {
            if(lower_bound(idxs[i].begin(), idxs[i].end(), cur) != idxs[i].end()) {
                int val = *lower_bound(idxs[i].begin(), idxs[i].end(), cur);
                if(k >= val - cur) {
                    inc[val] = 1;
                    k -= val - cur;
                    cur = val + 1;
                    f = 1;
                    // cout << "cur : " << cur << " val : " << val << endl;
                    break;
                }
            }
        }
        assert(f);
    }

    // cout << "k : " << k << endl;
    // cout << "inc : " << inc << endl;

    for(int i = n - 1; i >= 0; i--) {
        if(k && inc[i]) {
            k--;
            inc[i] = 0;
        }
    }

    for(int i = 0; i < n; i++) {
        if(inc[i]) cout << x[i];
    }

    cout << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}