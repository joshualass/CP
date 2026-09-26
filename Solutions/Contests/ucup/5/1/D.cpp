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

void solve() {
    
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    set<int> s(a.begin(), a.end());
    int ok = 1;
    for(int i = 0; i <= n / 2; i++) {
        if(s.count(n - i) == 0) ok = 0;
    }
    cout << ok << '\n';
}

map<vector<int>, int> dp;

int solve_slow(vector<int> a) {
    sort(a.begin(), a.end());
    int n = sz(a);

    if(dp.count(a) == 0) {
        if(sz(a) == 1) {
            dp[a] = a[0];
        } else {
            vector<int> p(n);
            iota(p.begin(), p.end(), 0);
            int res = 0;
            while(1) {
                vector<int> b(n);
                for(int i = 0; i < n; i++) {
                    b[i] = a[i] % max(1, a[p[i]]);
                }
                for(int i = 0; i < n; i++) {
                    int rem = *(b.begin() + i);
                    b.erase(b.begin() + i);
                    res = max(res, solve_slow(b));
                    b.insert(b.begin() + i, rem);
                }
                if(!next_permutation(p.begin(), p.end())) break;
            }
            dp[a] = res;
        }
        if(dp[a]) cout << "good a : " << a << endl;
        int ok = 1;
        set<int> s(a.begin(), a.end());
        for(int i = 0; i <= n / 2; i++) {
            if(s.count(n - i) == 0) ok = 0;
            // assert(s.count(n - i));
        }
        assert(ok == dp[a]);
    }
    // cout << "a : " << a << " dp[a] : " << dp[a] << endl;
    // for(int i = max(0, n - 2); i < n; i++) {
    //     // assert(n == sz(a));
    //     if(a[i] <= i) {
    //         //this tripped, think of 0 2 3
    //         assert(dp[a] == 0);
    //     }
    // }
    return dp[a];
}



signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for(int i = 0; i < 10000; i++) {
        int n = 6;
        vector<int> a(n);
        for(int j = 0; j < n; j++) {
            a[j] = rng() % n + 1;
        }
        if(solve_slow(a) > 1) {
            cout << "a : " << a << endl;
        }
    }

    cout << "all <= 1" << endl;

    // int casi; cin >> casi;
    // for(int i = 0; i < casi; i++) {

    //     solve();
    // }

    return 0;
}