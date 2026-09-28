#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

vector<ll> grundylist(ll k) {

    vector<ll> a(101);
    for(int i = 1; i <= 100; i++) {
        vector<int> mexer(101);
        for(int j = 1; j <= i / k; j++) {
            mexer[a[i - j]] = 1;
        }
        for(int j = 0; j < 101; j++) {
            if(mexer[j] == 0) {
                a[i] = j;
                break;
            }
        }
    }

    return a;

}

ll getgrundy(ll a, ll k) {

    

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll k; cin >> k;
    cout << "grundy list for k : " << k << '\n';
    vector<ll> gl = grundylist(k);

    for(int i = 0; i < 100; i++) {
        cout << "i : " << i << " gl[i] : " << gl[i] << '\n';
    }
    
    // int n; cin >> n;
    // int g = 0;
    // for(int i = 0; i < n; i++) {
    //     ll a, k; cin >> a >> k;
    //     g ^= getgrundy(a,k);
    // }

    // cout << (g == 0 ? "Aoki" : "Takahashi") << '\n';

    return 0;
}