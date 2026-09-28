#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<int> v(n);

    for(auto &x: v) cin >> x;
    v.push_back(MOD);

    int prev = 0;
    bool increasing = true;
    int peak_idx = -1;
    vector<bool> actions(n);
    for(int i = 0; i < n + 1; i++) {
        if(increasing && v[i] >= prev) {
            // cout << "if1\n";
        } else if(increasing && v[i] < prev) {
            // cout << "if2\n";
            peak_idx = i - 1;
            increasing = false;
        } else if(!increasing && v[i] <= prev) {
            // cout << "if1\n";
        } else {
            // cout << "peak valley : " << peak_idx << " " << i << '\n';
            actions[peak_idx] = 1;
            actions[i - 1] = 1;
            increasing = 1;
        }
        prev = v[i];
    }

    for(auto x : actions) cout << x << " ";

    return 0;
}