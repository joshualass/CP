#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

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
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

int maxdoubles(string s, int t) {
    int doubles = 0;
    for(int i = 1; i < s.size(); i++) {
        if(s[i] == t + '0' && s[i-1] == t + '0') {
            doubles++;
            i++;
        }
    }
    return min((int) s.size() / 4, doubles);
}

int dp(string s) {

    // cout << "s : " << s << '\n';

    vector<array<int,2>> dp(s.size() + 1, {0, 10000000}); // dp[i] stores {max value, minimum singles used}
    dp[0][1] = 0;

    for(int i = 1; i <= s.size(); i++) {

        int singles = s[i-1] == '1';
   
        if(dp[i-1][1] < s.size() / 2) {
            dp[i] = {dp[i-1][0] + singles, dp[i-1][1] + 1};
        }

        if(i >= 2) {
            int doubles = s[i-1] == '1' || s[i-2] == '1';
            if(dp[i-2][0] + doubles >= dp[i][0] && dp[i-2][1] <= dp[i][1]) {
                dp[i] = {dp[i-2][0] + doubles, dp[i-2][1]};
            }
        }

    }

    // cout << "dp : " << dp << '\n';

    return dp[s.size()][0];

}

int dpc(string s) {
    vector<vector<vector<int>>> dpc(s.size() + 1, vector<vector<int>>(s.size() / 2 + 1, vector<int>(s.size() / 4 + 1)));

    for(int i = 0; i < s.size(); i++) {
        for(int j = 0; j <= s.size() / 2; j++) {
            for(int k = 0; k <= s.size() / 4; k++) {
                if(j != s.size() / 2) {
                    dpc[i+1][j+1][k] = max(dpc[i+1][j+1][k], dpc[i][j][k] + (s[i] == '1'));
                }
                if(i + 1 < s.size() && k != s.size() / 4) {
                    dpc[i+2][j][k+1] = max(dpc[i+2][j][k+1], dpc[i][j][k] + (s[i] == '1' || s[i+1] == '1'));
                }
            }
        }
    }
    return dpc.back().back().back();
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // string s = "111111110000";

    // dp(s);

    for(ll i = 0; i < 1LL << 40; i++) {
        string s = "";
        string r = "";
        for(int j = 0; j < 40; j++) {
            if(i & (1 << j)) {
                s.push_back('1');
            } else {
                s.push_back('0');
            }
        }

        if(dpc(s) != dp(s)) {
            cout << "s : " << s << " dpc : " << dpc(s) << " dp : " << dp(s) << '\n';
            return 0;
        }
    }
    
    int n, m; cin >> n >> m;
    int lo = 0, hi = 0;
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        int countzero = count(s.begin(), s.end(), '0');
        int countone = count(s.begin(),s.end(), '1');
        lo += countone - maxdoubles(s,1); //find min that can be occupied
        hi += dp(s);
    }

    cout << lo << " " << hi << '\n';

    return 0;
}