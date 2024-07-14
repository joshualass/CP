/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

const int N = 5e3;
ll pcchoose[N + 1][N + 1];

void solve() {
    ll n; cin >> n;
    
    ll res = 0;
    for(ll subset_size = 0; subset_size <= n; subset_size++) { 
        
        for(ll under = 0; under <= subset_size; under++) { //under is the number of numbers that contribute to the mex, all values are < mexval
            ll over = subset_size - under;
            ll mexval = 1 + subset_size + under;
            ll under_poss = min(n, mexval - 1);
            ll over_poss = n - mexval;
            // ll under_ways = choose(under_poss, under);
            ll under_ways = pcchoose[under_poss][under];
            ll over_ways = 0;
            if(over == 0) {
                over_ways = 1;
            } else if(over_poss > 0 && over_poss >= over) {
                // over_ways = choose(over_poss, over);
                over_ways = pcchoose[over_poss][over];
            }
            ll add = mexval * under_ways % MOD * over_ways % MOD;
            // cout << "subset_size : " << subset_size << " under : " << under << " over : " << over << " mexval : " << mexval << " up : " << under_poss << " op : " << over_poss << " uw : " << under_ways << " ow : " << over_ways << " add : " << add << '\n';
            res = (res + add) % MOD;
        }
    }
    cout << res << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    for(int n = 0; n <= N; n++) {
        for(int k = 0; k <= n; k++) {
            if(k == 0 || k == n) {
                pcchoose[n][k] = 1;
            } else {
                pcchoose[n][k] = (pcchoose[n-1][k-1] + pcchoose[n-1][k]) % MOD;
            }
        }
    }

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}