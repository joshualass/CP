#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n, q; cin >> n >> q;
    vector<int> v(n);

    for(auto &x: v) cin >> x;

    int sum = reduce(v.begin(), v.end());
    
    set<int> onecnt;
    for(int i = 0; i < n; i++) {
        if(v[i] == 1) onecnt.insert(i);
    }

    for(int i = 0; i < q; i++) {
        int type; cin >> type;
        if(type == 1) {
            int val; cin >> val;
            int highest_odd = -1;
            int highest_even = -1;
            
            if(sum & 1) {
                highest_odd = sum;
                int twos = max(*onecnt.begin(),n - 1 - (*--onecnt.end()));
                 
            }

            // if((val == sum || sum - 2 >= val || sum - 1 == val && (v.front() == 1 || v.back() == 1)) 
            // && (((val & 1) == (sum & 1)) || onecnt.size() >= 2 || )) {
            //     cout << "YES\n";
            // } else {
            //     cout << "NO\n";
            // }
        } else {
            int i, u; cin >> i >> u;
            i--;
            if(v[i] == 1 && u == 2) onecnt.erase(i);
            if(v[i] == 2 && u == 1) onecnt.insert(i);
            sum += u - v[i];
            v[i] = u;
        }
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}