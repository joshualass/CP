#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

int solve_slow(int n, vector<int> a) {
    map<ll,int> m;
    int big = -1;
    for(int i = 1; i < 1 << n; i++) {
        ll res = 1;
        for(int j = 0; j < n; j++) {
            if((i >> j) & 1) {
                res *= a[j];
            }
        }
        m[res]++;
        if(m[res] > m[big]) big = res;
    }

    if(m[big] >= (1 << n - 1)) return big;
    return -1;
}

int solve(int n, vector<int> a) {

    map<int,int> m;
    for(int x : a) m[x]++;
    m.erase(1);
    if(sz(m) >= 2) return -1;
    for(auto [k, v] : m) {
        if(v > 2) return -1;
        return k;
    }
    return 1;
    
    // if(n == 1) return a[0];

    // if(n == 2) {
    //     if(a[0] == a[1]) {
    //         return a[0];
    //     } else {
    //         if(a[0] == 1) return a[1];
    //         if(a[1] == 1) return a[0];
    //         return -1;
    //     }
    // } else {
    //     if(count(a.begin(), a.end(), 1) == n) {
    //         return 1;
    //     } else {
    //         return -1;
    //     }
    // }



}



signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // for(int i = 0; i < 10000; i++) {
    //     int n = rng() % 5 + 1;
    //     vector<int> a(n);
    //     for(int j = 0; j < n; j++) {
    //         a[j] = rng() % 10 + 1;
    //     }
    //     if(solve_slow(n, a) != solve(n, a)) {
    //         cout << "a : " << a << endl;
    //         cout << "fast : " << solve_slow(n, a) << endl;
    //         cout << "slow : " << solve(n, a) << endl;
    //         return 0;
    //     }
    // }

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {
        int n; cin >> n;
        vector<int> a(n);
        for(int &x : a) cin >> x;
        cout << solve(n, a) << '\n';
    }

    return 0;
}