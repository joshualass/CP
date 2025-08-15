#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
// const int MAXN = 2e5;
// int test[MAXN + 1];

/*
guess 1 - we try each of the button dependencies by themselves. 

Basis for the guess 
we should try to avoid pressing additional buttons. If these additional buttons were to decresae the lamp on count, then we should 
press these buttons by themselves. 

*/

void solve() {
    
    

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // for(int i = 1; i <= MAXN; i++) {
    //     for(int j = i; j <= MAXN; j += i) {
    //         test[i] ^= 1;
    //     }
    // }

    // int cnt = 0;

    // for(int i = 1; i <= MAXN; i++) {
    //     cnt += test[i];
    //     cout << ((double) cnt) / i << " \n"[i == MAXN];
    // }

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}