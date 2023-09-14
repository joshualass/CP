#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n; cin >> n;
    vector<ll> v(n);
    for(ll &x: v) cin >> x;

    int keeps = 0;
    int keep1 = -1;
    int keep2 = -1;
    for(int i = 0; i < n; i++) {
        if(keep1 == -1) {
            keep1 = i;
            keeps++;
        } else if(keep2 == -1) {
            if(v[i] != v[keep1]) {
                keep2 = i;
                keeps++;
            }
        } else {
            if(v[keep2] > v[keep1] && v[keep2] > v[i]) {
                keeps++;
                keep1 = keep2;
                keep2 = i;
            } else if(v[keep2] < v[keep1] && v[keep2] < v[i]) {
                keeps++;
                keep1 = keep2;
                keep2 = i;
            } else if(v[keep2] > v[keep1] && v[i] > v[keep2]) {
                keep2 = i;
            } else if(v[keep2] < v[keep1] && v[i] < v[keep2]) {
                keep2 = i;
            }
        }
    }
    cout << keeps << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int casi; cin >> casi;
    while(casi-->0) solve();
    return 0;
}