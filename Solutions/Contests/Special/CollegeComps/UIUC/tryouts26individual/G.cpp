#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

array<ll,5> operator+(array<ll,5> lhs, array<ll,5> rhs) {
    array<ll,5> res = {};
    for(int i = 0; i < 5; i++) res[i] = lhs[i] + rhs[i];
    return res;
}

array<ll,5> operator-(array<ll,5> lhs, array<ll,5> rhs) {
    array<ll,5> res = {};
    for(int i = 0; i < 5; i++) res[i] = lhs[i] - rhs[i];
    return res;
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

template<typename T, typename D>
std::ostream& operator<<(std::ostream& os, map<T,D> m) {
    for(auto &x: m) os << x.first << " " << x.second << " | ";
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

    string s; cin >> s;
    map<char, array<ll,5>> m;
    for(char c = 'a'; c <= 'z'; c++) {
        array<ll,5> h = {};
        for(int i = 0; i < 5; i++) h[i] = rng() & INT_MAX;
        m[c] = h;
    }

    // cout << "m : " << m << endl;

    int n; cin >> n;
    vector<string> a(n);
    vector<array<ll,5>> hashes(n);

    for(int i = 0; i < n; i++) {
        cin >> a[i];
        array<ll,5> cur = {};
        for(char c : a[i]) cur = cur + m[c];
        hashes[i] = cur;
    }

    int len = sz(s);
    vector<array<ll,5>> p(len + 1);
    for(int i = 1; i <= len; i++) {
        p[i] = p[i-1] + m[s[i-1]];
    }

    vector<int> dp(len + 1), par(len + 1, -1);
    dp[0] = 1;
    for(int i = 1; i <= len; i++) {
        for(int j = 0; j < n; j++) {
            int k = sz(a[j]);
            if(i - k >= 0) {
                if(p[i] - p[i - k] == hashes[j] && dp[i - k] && s[i - k] == a[j][0] && s[i - 1] == a[j][k - 1]) {
                    par[i] = j;
                    dp[i] += dp[i - k];
                    // cout << "add transition i : " << i << " j : " << j << endl;
                }
            }
        }
        dp[i] = min(dp[i], 2);
    }

    // cout << "dp : " << dp << endl;

    if(dp[len] == 0) {
        cout << "impossible\n";
    } else if(dp[len] == 2) {
        cout << "ambiguous\n";
    } else {
        vector<string> res;
        int cur = len;
        while(cur) {
            int use = par[cur];
            res.push_back(a[use]);
            cur -= sz(a[use]);
        }
        reverse(res.begin(), res.end());
        cout << res << '\n';
    }

    return 0;
}
