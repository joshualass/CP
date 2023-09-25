#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, x; cin >> n >> x;
    vector<ll>v(n);
    for(auto&x:v)cin>>x;
    unordered_map<ll,pair<int,int>> m;
    vector<int> ans(0);
    for(int i = 1; i < n; i++) {
        for(int j = 0; j < i; j++) {
            if(m.find(v[j]+v[i]) == m.end()) {
                m[v[j]+v[i]] = {j,i};
            } 
        }
        for(int j = i + 2; j < n; j++) {
            if(m.find(x-(v[i+1]+v[j])) != m.end()) {
                ans = {m[x-(v[i+1]+v[j])].first, m[x-(v[i+1]+v[j])].second, i+1,j};
            }
        }
    }
    if(ans.size()) {
        for(auto &x: ans) cout << ++x << " ";
        cout << "\n";
    } else {
        cout << "IMPOSSIBLE\n";
    }


    return 0;
}