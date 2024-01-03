#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

array<ll,3> leetcode(vector<int> &v, int start, int stop) {
    int lo = 0, hi = 0;
    int bestlo = 0, besthi = 0;
    ll curr = 0;
    ll best = 0;

    for(int i = start; i < stop; i++) {
        curr += v[i];
        if(curr < 0) {
            lo = i + 1;
            hi = i + 1;
            curr = 0;
        } else {
            hi = i + 1;
            if(curr > best) {
                best = curr;
                bestlo = lo;
                besthi = hi;
            }
        }
    }

    return {best,bestlo,besthi};
}

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    vector<int> b(n);
    for(auto &x : a) cin >> x;
    for(auto &x : b) cin >> x;

    for(int i = 0; i < n; i++) {
        
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}