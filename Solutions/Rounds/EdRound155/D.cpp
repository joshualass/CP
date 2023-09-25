#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<ll> v(n);
    for(auto &x: v) cin >> x;
    ll cnt = 0;
    for(int i = 0; i < n; i++) {
        ll zeroindexes = 0;
        ll zerosum = 0;
        ll oneindexes = 0;
        ll onesum = 0;
        ll curr = 0;
        cout << "i: " << i << endl;
        for(int j = 0; j < n; j++) {
            
        }
        cout << "curr: " << curr << "\n";
    }


    return 0;
}