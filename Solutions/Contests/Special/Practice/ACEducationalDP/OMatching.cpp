//https://usaco.guide/gold/dp-bitmasks
//https://atcoder.jp/contests/dp/tasks/dp_o?lang=en
/*
when matching, always match the first unmatched women
i.e. when 0 people are matched, matched the first women
when 1 people are matched, matched any man with the second women
this way is doable.
*/

#include <bits/stdc++.h>
typedef long long ll;
typedef __int128_t lll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
template<typename T> // pbds
using pbds = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

const int MAX_N = 21;

bool matches[MAX_N][MAX_N];
// unordered_map<int,int> dp[MAX_N + 1];

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
template<typename T, typename U> using pb_map = gp_hash_table<T, U, chash>; // unordered_map but faster
pb_map<int,int> dp[MAX_N + 1];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> matches[i][j];
        }
    }
    dp[0][0] = 1; //there is one way to start with 0 matches
    for(int i = 0; i < n; i++) {//current match count
        for(auto x : dp[i]) {
            for(int j = 0; j < n; j++) {
                if(((x.first >> j) & 1) == 0 && matches[j][i]) {
                    dp[i+1][x.first | (1 << j)] += x.second;
                    if(dp[i+1][x.first | (1 << j)] >= MOD) {
                        dp[i+1][x.first | (1 << j)] -= MOD;
                    }
                }
            }
        }
    }
    int num = (1 << n) - 1;
    cout << dp[n][num] << "\n";
    return 0;
}