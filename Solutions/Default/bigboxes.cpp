#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k; cin >> n >> k;
    vector<int> v(n);
    for(auto &x: v) cin >> x;
    int l = *max_element(v.begin(),v.end()), r = 1e9;
    while(r - l > 0) {
        int m = (l + r) / 2;
        int cnt = 1;
        int currweight = 0;
        for(int i = 0; i < v.size(); i++) {
            if(currweight + v[i] <= m) {
                currweight += v[i];
            } else {
                currweight = v[i];
                cnt++;
            }
        }
        
        if(cnt <= k) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    cout << l << "\n";
    return 0;
}