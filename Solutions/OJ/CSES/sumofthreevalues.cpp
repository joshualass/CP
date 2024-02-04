#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, x; cin >> n >> x;
    vector<pair<ll,int>> v(n);
    for(int i = 0; i < n; i++) {
        cin >> v[i].first; v[i].second = i;
    }
    sort(v.begin(),v.end());
    vector<int> ans(0);
    for(int i = 0; i < n; i++) {
        ll half = v[i].first;
        int lptr = i + 1;
        int rptr = n - 1;
        while(lptr < rptr) {    
            if(half + v[lptr].first + v[rptr].first == x) {
                ans = {v[i].second,v[lptr].second,v[rptr].second};
                break;
            } else if(half + v[lptr].first + v[rptr].first > x) {
                rptr--;
            } else {
                lptr++;
            }
        }
    }
    sort(ans.begin(),ans.end());
    if(ans.size()) {
        for(auto &x:ans)cout << x+1 << " ";
    } else {
        cout << "IMPOSSIBLE\n";
    }
    return 0;
}