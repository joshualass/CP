#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

const ll inf = 1e18;

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<array<ll,2>> a(n);
    for(auto &x : a) for(auto &y : x) cin >> y;

    array<ll,2> s = {}, e = {};
    for(auto &x : s) cin >> x;
    for(auto &x : e) cin >> x;

    vector<ll> dists(n, inf);
    vector<int> par(n, -2), vis(n);

    ll last = inf;
    int last_par = -2;
    priority_queue<array<ll,2>, vector<array<ll,2>>, greater<array<ll,2>>> pq;

    pq.push({0, -1});
    while(pq.size()) {
        auto [dis, idx] = pq.top();
        pq.pop();
        if(idx != -1 && vis[idx]) continue;
        if(idx != -1) vis[idx] = 1;

        array<ll,2> cur = {};
        if(idx == -1) {
            cur = s;
        } else {
            cur = a[idx];
        }

        for(int i = 0; i < n; i++) {
            ll ndis = dis + (cur[0] - a[i][0]) * (cur[0] - a[i][0]) + (cur[1] - a[i][1]) * (cur[1] - a[i][1]);
            if(ndis < dists[i]) {
                pq.push({ndis, i});
                dists[i] = ndis;
                par[i] = idx;
            }
        }

        ll ldis = dis + (cur[0] - e[0]) * (cur[0] - e[0]) + (cur[1] - e[1]) * (cur[1] - e[1]);
        if(ldis < last) {
            last = ldis;
            last_par = idx;
        }
    }

    // cout << "d : " << dists << endl;
    // cout << "par : " << par << endl;
    // cout << "vis : " << vis << endl;

    // cout << "last : " << last << " lp : " << last_par << endl;

    assert(last_par != -2);

    if(last_par == -1) {
        cout << "-\n";
    } else {
        vector<int> res;
        while(last_par != -1) {
            res.push_back(last_par);
            last_par = par[last_par];
        }
        reverse(res.begin(), res.end());
        for(int x : res) cout << x << '\n';
    }

    return 0;
}
