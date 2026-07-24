#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()
const int H = 2;

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

template<class T, size_t L>
array<T, L> operator^(array<T, L> &lhs, array<T, L> &rhs) {
    array<T, L> res = {};
    for(int i = 0; i < L; i++) res[i] = lhs[i] ^ rhs[i];
    return res;
}

//balanced arrays where every element appears k times
ll solve_freq(int n, int k, vector<int> a) {

    // cout << "k : " << k << endl;
    
    vector<vector<int>> b(n);
    vector<int> stops(n, n);

    for(int i = 0; i < n; i++) {
        b[a[i]].push_back(i);
        if(sz(b[a[i]]) > k) {
            stops[b[a[i]][sz(b[a[i]]) - k - 1]] = min(stops[b[a[i]][sz(b[a[i]]) - k - 1]], i);
        }
    }

    for(int i = n - 2; i >= 0; i--) {
        stops[i] = min(stops[i], stops[i+1]);
    }

    vector<vector<array<ll, H>>> h(n);
    
    for(int i = 0; i < n; i++) {
        array<ll, H> t = {};
        for(int j = 0; j < min(sz(b[i]), k); j++) {
            h[i].push_back({});
            if(j == k - 1) {
                h[i].back() = t;
            } else {
                for(int k = 0; k < H; k++) {
                    h[i].back()[k] = rng();
                }
            }
            t = t ^ h[i].back();
        }
    }
    
    map<array<ll,H>, vector<int>> m;
    array<ll, H> cur = {};
    m[cur].push_back(0);
    
    vector<array<ll,H>> hashes(n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < sz(b[i]); j++) {
            hashes[b[i][j]] = h[i][j%sz(h[i])];
        }
    }
    
    for(int i = 0; i < n; i++) {
        cur = cur ^ hashes[i];
        m[cur].push_back(i + 1);
    }

    cur = {};
    
    ll res = 0;
    for(int i = 0; i < n; i++) {
        int add = upper_bound(m[cur].begin(), m[cur].end(), stops[i]) - upper_bound(m[cur].begin(), m[cur].end(), i);
        // cout << "i : " << i << " add : " << add << endl;
        res += add;
        cur = cur ^ hashes[i];
    }

    return res;

}

ll solve_dist(int n, int k, vector<int> a) {


    return 0;

}

void solve() {
    
    int n, k; cin >> n >> k;
    vector<int> a(n), b(k);
    for(int &x : a) {
        cin >> x;
        x--;
    }
    for(int &x : b) cin >> x;

    for(int i = 0; i < k; i++) {
        cout << solve_freq(n, b[i], a) << " " << solve_dist(n, b[i], a) << '\n';
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for(int i = 0; i < 20; i++) cout << rng() % 3 + 1 << " ";
    cout << endl;

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}   