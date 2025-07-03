#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<ll> v(n);

    for(auto &x: v) {cin >> x; x--;}

    ll score = 0;
    
    vector<ll> cnts(n);
    vector<ll> hi_idxs(n,-1);
    ll back_idx = 0;

    for(int i = 0; i < n; i++) {
        while(back_idx < hi_idxs[v[i]]) {
            if(cnts[back_idx] != 0 && v[back_idx] != v[i]) {
                cout << "adding : " << cnts[back_idx] << " back_idx : " << back_idx << " i : " << i << '\n';
                score += (cnts[back_idx] - 1) * (cnts[back_idx]) / 2;
                cnts[back_idx] = 0;
            }
            back_idx++;
        }
        hi_idxs[v[i]] = i;
        cnts[v[i]]++;
    }

    for(int i = 0; i < n; i++) {
        if(cnts[i] != 0) {
            cout << "end check adding : " << cnts[i] << " i : " << i << '\n';
            score += (cnts[i] - 1) * (cnts[i]) / 2;
        }
    }

    cout << score << '\n';

    return 0;
}