#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<ll> v(n);
    for(ll &x: v) cin >> x;
    ll cnt = 0;
    bool flag = false;
    sort(v.begin(),v.end());
    for(int i = 0; i < n; i++) {
        if(v[i] > cnt + 1) {
            break;
        } else {
            cnt += v[i];
        }
    }
    cout << ++cnt<< "\n";

    return 0;
}