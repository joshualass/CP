#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    vector<int> v(n);
    for(int &x : v) cin >> x;
    for(int i = 0; i < n; i++) {
        bool op = 0;
        for(int j = 0; j < v.size() - 1; j++) {
            if(v[j] > v[j+1] && v[j] >= 10) {
                op = 1;
                vector<int> a;
                int rem = v[j];
                v.erase(v.begin() + j);
                while(rem) {
                    a.push_back(rem % 10);
                    rem /= 10;
                }
                reverse(a.begin(),a.end());
                v.insert(v.begin() + j, a.begin(), a.end());
            }
        }
        if(op == 0) break;
    }
    cout << (is_sorted(v.begin(), v.end()) ? "Yes" : "No") << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}