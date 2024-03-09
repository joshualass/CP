#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

//reuse idea and code from subarraysumsii.cpp

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n; cin >> n;
    ll x = 0;
    unordered_map<ll,int> m;
    vector<ll> v(n);
    ll sum = 0;
    for(int i = 0; i < n; i++) {
        ll num; cin >> num;
        if(num < 0) num = n - ((-num) % n);
        num %= n;
        v[i] = num;
        sum = (sum + num) % n;
        if(m.find(sum) != m.end()) {
            m[sum]++;
        } else {
            m[sum] = 1;
        }
    }
    ll cnt = 0;
    sum = 0;
    for(int i = 0; i < n; i++) {
        if(m.find(x) != m.end()) {
            // cout << "adding? " << i << " x: " << x << " val: " << m[x] << "\n";
            cnt += m[x];
        }
        // sum += v[i];
        sum = (sum % n + v[i]) % n;
        m[sum]--;
        // x += v[i];
        x = (x % n + v[i]) % n;
    }
    cout << cnt << "\n";
    return 0;
}