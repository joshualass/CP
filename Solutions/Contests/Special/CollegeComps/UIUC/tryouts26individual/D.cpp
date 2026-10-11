#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

/*
CE

2 100
50 10
90 90

*/

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

int solve(int n, int c, vector<array<int,3>> a) {
    return 67;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, c; cin >> n >> c;
    vector<array<int,3>> a(n);

    for(int i = 0; i < n; i++) {
        int d, s; cin >> d >> s;
        d = max(d, s);
        a[i] = {d, s, i + 1};
    }

    sort(a.begin(), a.end(), [&](const auto &lhs, const auto &rhs) -> bool {
        // if(lhs[0] != rhs[0]) {
        //     return lhs[0] > rhs[0];
        // }
        // return lhs[1] < rhs[1];
        // if(lhs[0] + lhs[1] == rhs[0] + rhs[1]) {
        //     return lhs[0] < rhs[0];
        // }
        // return lhs[0] + lhs[1] < rhs[0] + rhs[1];
        if(lhs[0] - lhs[1] == rhs[0] - rhs[1]) {
            return lhs[0] > rhs[0];
        }
        return lhs[0] - lhs[1] > rhs[0] - rhs[1];
    });

    vector<vector<int>> dp(n + 1, vector<int>(c + 1)), par(n + 1, vector<int>(c + 1));

    array<int,2> cur = {0,0};
    for(int i = 1; i <= n; i++) {
        auto [d, s, _] = a[i-1];
        // cout << "d : " << d << " s : " << s << " id : " << _ << endl;
        for(int j = 0; j <= c; j++) {

            dp[i][j] = dp[i-1][j];
            par[i][j] = 0;

            int prev = j - s;
            if(prev >= 0 && prev + d <= c && 1 + dp[i-1][prev] > dp[i][j]) {
                dp[i][j] = 1 + dp[i-1][prev];
                par[i][j] = 1;
            }

            if(dp[i][j] > dp[cur[0]][cur[1]]) {
                cur = {i, j};
            }
        }
    }

    // cout << "cur : " << cur << endl;

    vector<int> res;
    while(cur[0]) {
        if(par[cur[0]][cur[1]]) {
            res.push_back(a[cur[0] - 1][2]);
            cur[1] -= a[cur[0] - 1][1];
        }
        cur[0]--;
        // cout << "upd cur : " << cur << endl;
    }

    reverse(res.begin(), res.end());
    cout << sz(res) << '\n';
    for(int x : res) cout << x << " ";
    cout << '\n';

    return 0;
}
