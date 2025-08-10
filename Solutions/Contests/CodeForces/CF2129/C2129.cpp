#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

vector<int> dp(10000 + 1, 1e9), par(10000 + 1);
vector<int> v;

void pc() {

    dp[0] = 0;

    for(int i = 1; i <= 10000; i++) {
        int c = 1;
        while(c * (c + 1) / 2 <= i) {
            if(dp[i - c * (c + 1) / 2] + c * 2 + 1 < dp[i]) {
                dp[i] = dp[i - c * (c + 1) / 2] + c * 2 + 1; 
                par[i] = c;
            } 
            c++;
        }
    }
    int sum = 0;

    for(int i = 1; i <= 1 << 12; i <<= 1) {
        sum += dp[i];
        v.push_back(i);
    }
    sum += dp[8256];
    v.push_back(8256);
    assert(sum <= 1000);
}

void solve() {
    
    int n; cin >> n;

    auto ask = [&](vector<int> a) -> int {
        cout << "? " << a.size();
        for(int x : a) cout << " " << x + 1;
        cout << endl;
        int res; cin >> res;
        return res;
    };

    int open = -1, close = -1;

    auto set_open_close = [&]() {
        vector<int> a(n);
        iota(a.begin(), a.end(), 0);
        vector<int> l(a.begin(), a.begin() + (n + 1) / 2);
        vector<int> r(a.begin() + (n + 1) / 2, a.end());
        if(ask(a) == 0) {
            swap(l, r);
        }

        a = l;
        a.insert(a.end(), r.begin(), r.end());

        int lo = 2, hi = n;
        while(lo != hi) {
            int m = (lo + hi) / 2;
            vector<int> test(a.begin(), a.begin() + m);
            int res = ask(test);
            if(res) {
                hi = m;
            } else {
                lo = m + 1;
            }
        }

        // cout << "lo : " << lo << '\n';

        open = a[lo - 2], close = a[lo - 1];

    };


    set_open_close();

    // open = -1, close = -1;
    vector<int> res(n);

    // cout << "open : " << open << " close : " << close << endl;

    auto add_to_query = [&](int idx, int sum, vector<int> &query) -> void {
        while(sum) {
            int c = par[sum];
            for(int i = 0; i < c; i++) {
                query.push_back(idx);
                query.push_back(close);    
            }
            query.push_back(close);
            sum -= c * (c + 1) / 2;
        }
    };

    int cur = 0;
    while(cur != n) {
        int r = min(n, cur + (int) v.size());
        vector<int> query;
        for(int i = 0; i + cur < r; i++) {
            add_to_query(i + cur, v[i], query);
        }
        int f = ask(query);
        for(int i = r - 1 - cur; i >= 0; i--) {
            if(f < v[i]) {
                res[i + cur] = 1;
            } else {
                f -= v[i];
            }
        }
        cur = r;
    }

    cout << "! ";
    for(int x : res) cout << (x ? ')' : '(');
    cout << endl;

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    pc();

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}