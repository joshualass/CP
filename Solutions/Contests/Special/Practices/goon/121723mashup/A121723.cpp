#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;

    vector<ll> middles;
    ll s1 = 0, s2 = 0;
    for(int i = 0; i < n; i++) {
        int s; cin >> s;
        vector<ll> v(s);
        for(auto &x: v) cin >> x;
        if(s & 1) {
            middles.push_back(v[s/2]);
        }
        for(int j = 0; j < s / 2; j++) {
            s1 += v[j];
        }
        for(int j = (s + 1) / 2; j < s; j++) {
            s2 += v[j];
        }
    }

    sort(middles.rbegin(),middles.rend());

    // cout << "middles : " << middles << '\n';
    
    for(int i = 0; i < middles.size(); i++) {
        if(i & 1) {
            s2 += middles[i];
        } else {
            s1 += middles[i];
        }
    }
    cout << s1 << " " << s2 << '\n';
    return 0;
}