#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

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
    for(auto &x: m) os << x.first << " " << x.second << "\n";
    return os;
}

void solve() {
    int n; cin >> n;

    vector<string> m(2);
    for(auto &x : m) cin >> x;

    map<array<int,2>, int> dp;

    for(int low = 0; low < n; low++) {
        for(int i = 0; i <= 3 && low + i <= n; i++) {
            for(int j = 0; j <= 3 && low + j <= n; j++) {
                int u1 = -1, u2 = -1, u3 = -1, l1 = -1, l2 = -1, l3 = -1;
                if(low < n) {
                    u1 = m[0][low] == 'A';
                    l1 = m[1][low] == 'A';
                }
                if(low + 1 < n) {
                    u2 = m[0][low+1] == 'A';
                    l2 = m[1][low+1] == 'A';
                }
                if(low + 2 < n) {
                    u3 = m[0][low+2] == 'A';
                    l3 = m[1][low+2] == 'A';
                }
                if(i >= 3) {
                    int cnt = (u1 + u2 + u3 >= 2);
                    dp[{low+i,low+j}] = max(dp[{low+i,low+j}], dp[{low+i-3,low+j}] + cnt);
                }

                if(j >= 3) {
                    int cnt = (l1 + l2 + l3 >= 2);
                    dp[{low+i,low+j}] = max(dp[{low+i,low+j}], dp[{low+i,low+j-3}] + cnt);
                }

                if(i == 2 && j == 2) {
                    int cnt1 = (u1 + u2 + l2 >= 2);
                    dp[{low+i,low+j}] = max(dp[{low+i,low+j}], dp[{low+i-2,low+j-1}] + cnt1);

                    int cnt2 = (l1 + l2 + u2 >= 2);
                    dp[{low+i,low+j}] = max(dp[{low+i,low+j}], dp[{low+i-1,low+j-2}] + cnt2);
                }

                if(i == 2 && j == 1) {
                    int cnt = (u1 + u2 + l1 >= 2);
                    dp[{low+i,low+j}] = max(dp[{low+i,low+j}], dp[{low+i-2,low+j-1}] + cnt);
                }

                if(i == 1 && j == 2) {
                    int cnt = (l1 + l2 + u1 >= 2);
                    dp[{low+i,low+j}] = max(dp[{low+i,low+j}], dp[{low+i-1,low+j-2}] + cnt);
                }

            }
        }
    }

    // cout << "dp\n" << dp << '\n';

    cout << dp[{n,n}] << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}