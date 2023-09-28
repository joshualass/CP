//https://cses.fi/105/submit/C
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // freopen("pcb.in","r",stdin);
    // freopen("pcb.out","w",stdout);    

    int n; cin >> n;
    vector<pair<int,int>> v(n);
    for(auto &x: v) cin >> x.first >> x.second;
    sort(v.begin(),v.end());
    set<int> s;
    for(int i = 0; i < n; i++) {
        if(s.size() && s.upper_bound(v[i].second) != s.begin()) {
            s.erase(--s.upper_bound(v[i].second));
        }
        s.insert(v[i].second);
    }
    cout << s.size() << "\n";
    return 0;
}