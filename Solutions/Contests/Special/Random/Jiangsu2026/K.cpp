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
    
    int n, a; cin >> n >> a;
    vector<int> v(n);
    for(int &x : v) cin >> x;

    set<int> s;

    for(int i = 0; i < n; i++) {
        if(v[i] > a) s.insert(i);
    }

    multimap<int,int> sells;

    ll money = 0;
    int buys = 0;

    for(int i = 0; i < n; i++) {
        if(v[i] <= a) {
            money -= v[i];
            buys++;
            if(s.upper_bound(i) != s.end()) {
                int idx = *s.upper_bound(i);
                // sells.insert(idx);
                sells.insert({v[idx], idx});
                money += v[idx];
                s.erase(idx);
            }
        }
    }

    int q; cin >> q;
    vector<array<int,2>> qs(q);
    for(int qq = 0; qq < q; qq++) {
        int b; cin >> b;
        qs[qq] = {b, qq};
    }

    vector<ll> res(q);

    sort(qs.begin(), qs.end());
    for(auto [b, qidx] : qs) {
        while(sz(sells) && sells.begin()->first < b) {
            auto [price, idx] = *sells.begin();
            sells.erase(sells.begin());
            money -= price;
            while(s.upper_bound(idx) != s.end()) {
                int sidx = *s.upper_bound(idx);
                s.erase(sidx);
                if(v[sidx] >= b) {
                    money += v[sidx];
                    sells.insert({v[sidx], sidx});
                    break;
                }
            }
        }
        res[qidx] = money + 1LL * (buys - sz(sells)) * v[n - 1];
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}