#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, w; cin >> n >> w;

    vector<vector<ll>> a(w+1);

    for(int i = 0; i < n; i++) {
        int b, c; cin >> b >> c;
        a[b].push_back(c);
    }

    vector<ll> dp(w+1);

    for(int i = 1; i <= w; i++) {
        if(a[i].size()) {
            // cout << "i : " << i << '\n';
            vector<ll> c(1,0);
            priority_queue<ll> pq;
            for(ll v : a[i]) {
                pq.push(v-1);
            }
            while(c.size() != w + 1) {
                ll v = pq.top();
                pq.pop();
                c.push_back(c.back() + v);
                pq.push(v-2);
            }
            // cout << "c : " << c << '\n';
            vector<ll> nextdp(w+1);
            for(int j = 1; j <= w; j++) {
                nextdp[j] = nextdp[j-1];
                for(int k = 0; j - k * i >= 0; k++) {
                    nextdp[j] = max(nextdp[j], dp[j - k * i] + c[k]);
                }
            }
            swap(dp,nextdp);
            // cout << "dp : " << dp << '\n';
        }
    }

    cout << dp[w] << '\n';

    return 0;
}