#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

template<typename T, typename D>
std::ostream& operator<<(std::ostream& os, map<T,D> m) {
    for(auto &x: m) os << x.first << " " << x.second << " | ";
    return os;
}

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

const int debug = 0;

map<ll,ll> huffslow(ll n, vector<array<ll,2>> a) {
    map<ll,ll> correct, ttfang;
    for(auto [l, r] : a) {
        for(int i = l; i <= r; i++) {
            ttfang[i]++;
        }
    }
    for(int k = 1; k <= n; k++) {
        int v = ttfang[k];
        int cnt = 0;
        for(int i = 1; i * k <= n; i++) cnt++;
        assert(cnt == n / k);
        cout << "k : " << k << " v : " << v << endl;
        correct[cnt * v]++;

    }

    return correct;
}

map<ll,ll> hufffast(ll n, map<ll, int> deltas) {
    ll nx = n;
    ll active = 0;

    auto it = deltas.end();
    map<ll,ll> huff;

    while(nx > 0) {
        ll cnt = n / nx;
        ll lo = n / (cnt + 1);

        ll cur = nx;

        while(it != deltas.begin() && prev(it)->first >= lo) {
            ll diff = cur - prev(it)->first;
            huff[active * cnt] += diff;
            it--;
            active += it->second;
            cur = it->first;
        }

        ll diff = cur - lo;
        huff[active * cnt] += diff;

        nx = lo;
    }

    for(auto it = huff.begin(); it != huff.end();) {
        if(it->second) {
            it++;
        } else {
            it = huff.erase(it);
        }
    }
    // huff.erase(0);
    return huff;
}

ll ttfang(map<ll,ll> freq) {
    priority_queue<ll, vector<ll>, greater<ll>> pq;
    for(auto [k, v] : freq) {
        for(int i = 0; i < v; i++) {
            pq.push(k);
        }
    }
    if(pq.size() == 1) {
        return pq.top();
    } else {
        ll res = 0;
        while(sz(pq) > 1) {
            ll first = pq.top();
            pq.pop();
            ll second = pq.top();
            pq.pop();
            res += first + second;
            pq.push(first + second);
        }
        return res;
    }
}

map<ll,ll> gethuff(ll n, ll m) {

    map<ll, int> deltas;
    vector<array<ll,2>> a;

    if(debug) {
        for(int i = 0; i < 1000; i++) {
            n = rng() % 100 + 1;
            m = rng() % 1000 + 1;
            a.clear();
            deltas.clear();
            for(int j = 0; j < m; j++) {
                ll l = rng() % n + 1, r = rng() % n + 1;
                if(l > r) swap(l, r);

                deltas[l - 1]--;
                deltas[r]++;
                a.push_back({l, r});
            }

            auto slow = huffslow(n, a);
            auto fast = hufffast(n, deltas);

            if(slow != fast) {
                cout << "n : " << n << endl;
                cout << "a : " << a << endl;
                cout << "slow : " << slow << endl;
                cout << "fast : " << fast << endl;
            }
            assert(slow == fast);
            auto huff = fast;

            ll res = 0;

            if(sz(huff) == 1 && huff.begin()->second == 1) {
                res = huff.begin()->first;
            } else {
                while(sz(huff) > 1 || huff.begin()->second >= 2) {
                    // cout << "huff : " << huff << endl;
                    auto [lo, cnt] = *huff.begin();
                    assert(cnt);
                    huff.erase(huff.begin());
    
                    if(cnt >= 2) {
                        ll pairs = cnt / 2;
                        res += pairs * lo * 2;
                        huff[lo * 2] += pairs;
                    }
    
                    if(cnt & 1) {
                        ll nx = huff.begin()->first;
                        assert(huff[nx] > 0);
                        huff[nx]--;
                        if(huff[nx] == 0) huff.erase(nx);
                        huff[lo + nx]++;
                        res += lo + nx;
                    }
                }
            }

            ll res_slow = ttfang(fast);
            if(res != res_slow) {
                cout << "huff : " << fast << endl;
                cout << "slow : " << res_slow << endl;
                cout << "fast : " << res << endl;
                assert(0);
            }

        }
        assert(0);
    } else {
        for(int i = 0; i < m; i++) {
            ll l, r; 
            cin >> l >> r;
            // l = 1, r = n;

            deltas[l - 1]--;
            deltas[r]++;
            a.push_back({l, r});
        }
        // if(n == 100) {
        //     auto [l, r] = a.back();
        //     cout << l << "-" << r << endl;
        //     assert(0);
        // }
        return hufffast(n, deltas);
        // return huffslow(n, a);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, m; cin >> n >> m;
    map<ll,ll> huff = gethuff(n, m);
    // cout << "huff : " << huff << endl;
    // cout << ttfang(huff) << '\n';
    // return 0;

    ll res = 0;

    if(sz(huff) == 1 && huff.begin()->second == 1) {
        cout << huff.begin()->first << '\n';
        return 0;
    }

    while(sz(huff) > 1 || huff.begin()->second >= 2) {
        // cout << "huff : " << huff << endl;
        auto [lo, cnt] = *huff.begin();
        assert(cnt);
        huff.erase(huff.begin());

        if(cnt >= 2) {
            ll pairs = cnt / 2;
            res += pairs * lo * 2;
            huff[lo * 2] += pairs;
        }

        if(cnt & 1) {
            ll nx = huff.begin()->first;
            assert(huff[nx] > 0);
            huff[nx]--;
            if(huff[nx] == 0) huff.erase(nx);
            huff[lo + nx]++;
            res += lo + nx;
        }
    }

    cout << res << '\n';

    return 0;
}
