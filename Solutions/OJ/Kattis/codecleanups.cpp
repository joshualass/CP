#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    int cleanups = 0;
    int lo = 0;
    int dirtycount = 0;
    int dirtyscore = 0;
    for(int i = 0; i < 400; i++) {
        if(dirtyscore + dirtycount >= 20) {
            dirtycount = 0;
            dirtyscore = 0;
            cleanups++;
        }
        dirtyscore += dirtycount;
        if(lo != n && i == a[lo]) {
            dirtycount++;
            lo++;
        }
    }
    cout << cleanups << '\n';    
    return 0;
}