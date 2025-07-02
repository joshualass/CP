#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
current ideas 
have dp state
# nodes
# parity diff
# size of previous layer
# binom count

have binom because a lot of the states can be 

We can optimize the state by noticing all the edges on the same layer is like that of the binomial distribution. for each pair of 
nodes, we can choose to or not choose to have an edge between the pair on the same level. However, this does not work for the edges 
between layers as a node must have some edge, so it's not 0/1 distribution for all of these edges ... don't know how to fix 
and run in time. 
*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

ll dp[31][31][31][436];
ll choose[1001][1001];

vector<ll> mul(vector<ll> a, vector<ll> b) {
    vector<ll> res(a.size() + b.size() - 1);
    for(int i = 0; i < a.size() + b.size() - 1; i++) {
        for(int l = 0; l <= i; l++) {
            res[i] += 
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // ll n, p; cin >> n >> p;

    // dp[1][n / 2 - 1][1][0] = 1;

    // for(ll sz = 0; sz <= n; sz++) {
    //     for(ll par = 0; par <= n; par++) {
    //         for(ll pl = 1; pl <= n; pl++) {
    //             for(ll bin = 0; bin <= n * (n - 1) / 2; bin++) {
    //                 if(dp[sz][par][pl][bin]) {
    //                     for(ll nl = 1; nl + par <= n && sz + nl <= n; nl++) {



    //                     }
    //                 }
    //             }
    //         }
    //     }
    // }

    int nl, pl; cin >> nl >> pl;

    vector<int> total(nl * pl + 1);
    vector<int> targ(nl * pl + 1);
    vector<int> bad(nl * pl + 1);

    for(int i = 0; i < 1 << (nl * pl); i++) {
        int ok = 1;
        for(int j = 0; j < pl; j++) {
            if(((i >> (j * nl)) & ((1 << nl) - 1)) == 0) ok = 0;
        }
        total[__builtin_popcount(i)]++;
        if(ok) targ[__builtin_popcount(i)]++;
        else bad[__builtin_popcount(i)]++;
    }

    cout << "total : " << total << '\n';
    cout << "targ : " << targ << '\n';
    cout << "bad : " << bad << '\n';

    return 0;
}
