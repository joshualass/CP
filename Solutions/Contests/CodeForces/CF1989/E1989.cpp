#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

//can't place numbers of length 2

/*

dp[i][j]
i - current length that is numbered
j - the number of unique colors used

*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<vector<T>> adj) {
    for(auto x : adj) {
        for(auto y : x) os << y << " ";
        os << "\n";
    }
    return os;
}

template<typename T>
struct Tree {
    static constexpr T base = 0;
    vector<T> v;
    int n, size;
    T comb(T a, T b) { //change this when doing maximum vs minimum etc.
        return (a + b) % MOD;
    }
    Tree(int n = 0, T def = base) {
        this->n = n; //max number of elements
        size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, def);
    }
    void update(int pos, T val) { //update 0 indexed, assignment
        assert(pos < n && pos >= 0);
        int curr = pos + size;
        v[curr] = val % MOD;
        while(curr != 1) {
            if(curr & 1) { //handles non-communative operations
                v[curr / 2] = comb(v[curr ^ 1], v[curr]);
            } else {
                v[curr / 2] = comb(v[curr], v[curr ^ 1]);
            }
            curr /= 2;
        }
    }
    bool isLeaf(int idx) {
        return idx >= size;
    }
    T at(int idx) {
        assert(idx >= 0 && idx < n);
        return v[idx + size];
    }
    T query(int l, int r) {//queries in range [l,r)
        return _query(1,0,size,l,r);
    }
    T _query(int idx, int currl, int currr, int &targetl, int &targetr) {
        if(currr <= targetl || currl >= targetr) return base;
        if(currl >= targetl && currr <= targetr) return v[idx];
        int mid = (currl + currr) / 2;
        return comb(
            _query(idx * 2, currl, mid, targetl, targetr),
            _query(idx * 2 + 1, mid, currr, targetl, targetr)
        );
    }
};


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, k; cin >> n >> k;
    
    
    
    vector<vector<ll>> dp(n+1,vector<ll>(k+1));
    vector<Tree<ll>> trees(k+1,Tree<ll>(n+1));
    
    dp[0][0] = 1; //starting point
    trees[0].update(0,1);
    for(int length = 1; length <= n; length++) {
        for(int color = 1; color <= k; color++) {
            //we can add 1, or 3+
            if(color == 1 && length == 2) dp[length][color] = 1;
            dp[length][color] = (dp[length][color] + dp[length-1][color-1] + trees[color-1].query(0,length - 2)) % MOD; 
            if(color == k) {
                dp[length][color] = (dp[length][color] + dp[length-1][color] + trees[color].query(0,length - 2)) % MOD;
            }
            if(color == k && length == n) {
                dp[length][color] = (dp[length][color] + dp[length - 2][color] + dp[length - 2][color - 1]) % MOD;
            }
            trees[color].update(length,dp[length][color]);
        }
    }
    
    // cout << "dp\n" << dp;
    
    cout << dp[n][k] << '\n';

    return 0;
}