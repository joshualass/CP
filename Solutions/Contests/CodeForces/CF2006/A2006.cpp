#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    
    int n; cin >> n;
    vector<int> a(n);
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        a[u]++;
        a[v]++;
    }

    string s; cin >> s;
    int one = 0, zero = 0, undecided = 0, stall = 0;
    for(int i = 1; i < n; i++) {
        if(a[i] == 1) {
            if(s[i] == '?') {
                undecided++;
            } else if(s[i] == '0') {
                zero++;
            } else {
                one++;
            }
        } else if(s[i] == '?') {
            stall++;
        }
    }

    // cout << "zero : " << zero << " one : " << one << " und : " << undecided << '\n';

    if(s[0] == '?') {
        if(one > zero) {
            cout << one + undecided / 2 << '\n';
        } else if(zero > one) {
            cout << zero + undecided / 2 << '\n';
        } else {
            cout << zero + (undecided + (stall & 1)) / 2 << '\n';
        }
    } else if(s[0] == '0') {
        cout << one + (undecided + 1) / 2 << '\n';
    } else {
        cout << zero + (undecided + 1) / 2 << '\n';
    }


}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}