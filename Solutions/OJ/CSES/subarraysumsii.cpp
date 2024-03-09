#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

//idea is to preprocess all the sums and number of ways to make each sum with subarrays starting with 0
//then reuse these values for 1 and so on ...
//make sure to remove the sum including previous index and to adjust the target value so we are able to reuse the values

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, x; cin >> n >> x;
    unordered_map<ll,int> m;
    vector<ll> v(n);
    ll sum = 0;
    for(int i = 0; i < n; i++) {
        ll num; cin >> num;
        v[i] = num;
        sum += num;
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
        sum += v[i];
        m[sum]--;
        x += v[i];
    }
    cout << cnt << "\n";
    return 0;
}