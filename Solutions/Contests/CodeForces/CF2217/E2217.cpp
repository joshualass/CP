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
    
    int n; cin >> n;
    vector<int> p(n), d(n);
    for(int &x : p) cin >> x;
    for(int &x : d) cin >> x;

    vector<int> q(n);
    for(int i = n - 1; i >= 0; i--) {
        vector<int> c;
        for(int j = i + 1; j < n; j++) {
            if(p[j] > p[i]) c.push_back(q[j]);
        }
        if(sz(c) < d[i]) {
            cout << "-1\n";
            return;
        }
        c.push_back(n - i);
        sort(c.begin(), c.end());
        int val = c[sz(c) - 1 - d[i]];
        // cout << "i : " << i << " val : " << val << endl;
        q[i] = val;
        for(int j = i + 1; j < n; j++) {
            if(q[j] >= val) q[j]++;
        }
    }

    cout << q << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}