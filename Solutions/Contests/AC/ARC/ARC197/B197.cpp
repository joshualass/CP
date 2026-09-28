#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    sort(a.begin(), a.end());

    int l = 0, r = n - 1;
    while(l != r) {
        int m = (l + r + 1) / 2;
        ll sum = accumulate(a.begin(), a.begin() + m, 0LL);
        int ok = 0;
        int lo = -1;
        // cout << "m : " << m << " starting sum : " << sum << "\n";
        for(int hi = m; hi < n; hi++) {
            sum += a[hi];
            sum -= a[hi-m];
            while(lo + 1 <= hi - m && 1LL * a[lo+1] * (m + lo + 1) <= sum) {
                sum += a[++lo];
            }
            // cout << "lo : " << lo << " hi : " << hi << " sum : " << sum << '\n';
            if(1LL * a[hi-m+1] * (m + lo + 1) > sum) ok = 1;
        }
        if(ok) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    cout << l << '\n';
}

int solve(int n, vector<int> a) {
    
    sort(a.begin(), a.end());

    int l = 0, r = n - 1;
    while(l != r) {
        int m = (l + r + 1) / 2;
        ll sum = accumulate(a.begin(), a.begin() + m, 0LL);
        int ok = 0;
        int lo = -1;
        // cout << "m : " << m << " starting sum : " << sum << "\n";
        for(int hi = m; hi < n; hi++) {
            sum += a[hi];
            sum -= a[hi-m];
            while(lo + 1 <= hi - m && 1LL * a[lo+1] * (m + lo + 1) <= sum) {
                sum += a[++lo];
            }
            // cout << "lo : " << lo << " hi : " << hi << " sum : " << sum << '\n';
            if(1LL * a[hi-m+1] * (m + lo + 1) > sum) ok = 1;
        }
        if(ok) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    return l;
}

int solve_slow(int n, vector<int> a) {

    int res = 0;
    for(int i = 0; i < 1 << n; i++) {
        ll s = 0;
        for(int j = 0; j < n; j++) {
            if((i >> j) & 1) s += a[j];
        }
        int c = 0;
        for(int j = 0; j < n; j++) {
            if(((i >> j) & 1) && 1LL * a[j] * __builtin_popcount(i) > s) c++;
        }
        res = max(res, c);
    }

    return res;

}

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // int n, m; cin >> n >> m;

    // for(int i = 0; i < 1000; i++) {
    //     vector<int> a(n);
    //     for(auto &x : a) x = rng() % m + 1;
    //     int s = solve(n, a), slow = solve_slow(n, a);
    //     if(s != slow) {
    //         cout << "s : " << s << " slow : " << slow << '\n';
    //         cout << "n : " << n << '\n';
    //         cout << "a : " << a << '\n';
    //         return 0;
    //     }
    // }

    // cout << "ALL OK!\n";

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}