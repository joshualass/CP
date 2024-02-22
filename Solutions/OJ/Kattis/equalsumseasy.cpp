#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> v(n);
    for(int &x : v) cin >> x;

    unordered_map<int,int> m;
    pair<int,int> ans = {-1,-1};
    for(int i = 0; i < (1 << n); i++) {
        int sum = 0;
        for(int j = 0; j < 20; j++) {
            if((i >> j) & 1) {
                sum += v[j];
            }
        }
        if(m.count(sum)) {
            ans = {m[sum],i};
            break;
        }
        m[sum] = i;
    }
    // cout << "ans first : " << ans.first << " ans.second : " << ans.second << '\n';
    if(ans.first != -1) {
        for(int i = 0; i < 20; i++) {
            if(((ans.first >> i) & 1) && (((ans.second >> i) & 1) == 0)) {
                cout << v[i] << " ";
            }
        }
        cout << '\n';
        for(int i = 0; i < 20; i++) {
            if(((ans.second >> i) & 1) && (((ans.first >> i) & 1) == 0)) {
                cout << v[i] << " ";
            }
        }
        cout << '\n';
    } else {
        cout << "Impossible\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);

    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    
    int casi; cin >> casi;
    for(int i = 1; i <= casi; i++) {
        cout << "Case #" << i << ":\n";
        solve();
    }
    return 0;
}