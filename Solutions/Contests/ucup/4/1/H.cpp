#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

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

    ll n, m, k; cin >> n >> m >> k;
    vector<vector<ll>> a(k, vector<ll>(n));

    for(auto &x : a) for(auto &y : x) cin >> y;

    auto work = [&]() -> ll {
        // cout << "a : " << a << " m : " << m << endl;
        vector<array<ll,3>> pq;
        ll cnt = 0;
        vector<ll> res(n);
        for(int z = 0; z < n; z++) {
            // cout << "i : " << z << endl;
            vector<ll> b;
            for(int j = 0; j < k; j++) {
                b.push_back(a[j][z]);
            }
            sort(b.begin(), b.end());
            int med = (k - 1) / 2;
            res[z] = b[med];
            cnt += b[med];
            if(k % 2 == 0) {
                pq.push_back({0, b[med+1] - b[med], z});
                med++;
            }
            for(int i = med + 1; i < k; i++) {
                array<ll,3> push = {i - med, b[i] - b[i-1], z};
                // cout << "push : " << push << endl;
                pq.push_back(push);
            }
        }

        if(cnt > m) return LLONG_MAX;

        sort(pq.rbegin(), pq.rend());

        // cout << "cnt : " << cnt << " m : " << m << endl;

        while(cnt < m) {
            auto [cost, len, idx] = pq.back();
            pq.pop_back();
            ll sub = min(len, m - cnt);
            cnt += sub;
            res[idx] += sub;
        }

        // cout << "a : " << a << endl;
        // cout << "res : " << res << endl;

        ll ans = 0;
        for(int i = 0; i < k; i++) {
            for(int j = 0; j < n; j++) {
                ans += abs(a[i][j] - res[j]);
            }
        }

        return ans / 2;
    };

    if(work() == LLONG_MAX) {
        ll t = 0;
        for(auto &x : a) {
            for(auto &y : x) {
                y = 1000000000 - y;
            }
        }
        for(auto &y : a[0]) {
            t += y;
        }
        m = t;
    }

    cout << work() << '\n';

    return 0;
}
