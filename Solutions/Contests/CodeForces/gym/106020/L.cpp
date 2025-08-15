#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
observations

if k_2 is odd, player 1 is able to force themselves to pickup on any element of their choice by forcing player 2 to pickup the previous item. 



*/

void solve() {
    
    int n, k1, k2; cin >> n >> k1 >> k2;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    int res = 0;
    if(k2 % 2 == 1) {
        res = n;
    } else {
        
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}