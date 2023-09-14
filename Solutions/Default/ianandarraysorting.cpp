#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    while(t-->0) {
        int n; cin >> n;
        vector<ll> v(n);
        for(ll &x: v) cin >> x;
        for(int i = 1; i < n - 1; i++) {
            if(v[i-1] > v[i]) {
                ll add = v[i-1] - v[i];
                v[i] += add;
                v[i+1] += add;
            }
        }
        for(int i = n - 2; i > 0; i--) {
            if(v[i+1] < v[i]) {
                ll add = v[i] - v[i+1];
                v[i] -= add;
                v[i-1] -= add;
            }
        }
        bool flag = true;
        for(ll x : v) {
            // cout << x << " ";
        }
        for(int i = 1; i < n; i++) {
            if(v[i-1] > v[i]) {
                flag = false;
                break;
            }
        }
        cout << (flag ? "YES" : "NO") << "\n";
    }

    return 0;
}