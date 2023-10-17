#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
struct chash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
template<typename T> using pb_set = gp_hash_table<T, null_type, chash>;  // unordered_set but faster
template<typename T, typename U> using pb_map = gp_hash_table<T, U, chash>; // unordered_map but faster

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << '(' << p.first << ", " << p.second << ") ";
    return os;
}

template<typename T, typename D>
std::ostream& operator<<(std::ostream& os, unordered_map<T,D> m) {
    for(auto &x: m) os << x.first << " - " << x.second << "| ";
    return os;
}

pb_map<int,pair<int,int>> dp[21];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, X; cin >> n >> X;
    vector<int> v(n);
    for(auto &x: v) cin >> x;
    dp[0][0] = {0,0};
    for(int i = 0; i < n; i++) {
        for(auto x : dp[i]) {
            // cout << "make here0?\n";
            for(int j = 0; j < n; j++) {
                // cout << "make here1?\n";
                if(((x.first >> j) & 1) == 0) {
                    pair<int,int> p = x.second;
                    // cout << "make here2?\n";
                    if(p.second + v[j] > X) {
                        p = {p.first+1,v[j]};
                    } else {
                        p = {p.first,p.second+v[j]};
                    }
                    if(dp[i+1].find(x.first | (1 << j)) == dp[i+1].end()) {
                        dp[i+1][x.first | (1 << j)] = p;
                    } else {
                        pair<int,int> next = dp[i+1][x.first | (1 << j)];
                        if(p.first < next.first || p.first == next.first && p.second < next.second) {
                            dp[i+1][x.first | (1 << j)] = p;
                        }
                    }
                } 
            }
        }
    }
    // for(int i = 0; i <= 4; i++) {
    //     cout << dp[i] << "\n";
    // }
    int cnt = dp[n][(1 << n) - 1].first + (dp[n][(1 << n) - 1].second + X - 1) / X;
    cout << cnt << "\n";
    return 0;
}