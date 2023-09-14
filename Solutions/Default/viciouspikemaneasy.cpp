#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, t; cin >> n >> t;
    ll a, b,c, to; cin >> a >> b >> c >> to;
    vector<ll> v(n);
    v[0] = to;
    for(int i = 1; i < n; i++) {
        v[i] = 1+(a*v[i-1] + b)%c;
    }
    sort(v.begin(),v.end());
    ll pref = 0;
    ll time = 0;
    ll problems = 0;
    for(int i = 0; i < n; i++) {
        pref += v[i];
        if(pref > t) {
            break;
        }
        time += pref;
        problems++;
        if(time > 1000000007) {
            time %= 1000000007;
        }
    }
    cout << problems << " " << time << "\n";
    return 0;
}