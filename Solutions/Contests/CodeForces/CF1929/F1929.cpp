#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void dfs(int i, vector<pair<int,int>> &childs, vector<int> &inorder, vector<ll> &vals) {
    if(childs[i].first != -1) {
        dfs(childs[i].first,childs,inorder,vals);
    }
    inorder.push_back(i);
    if(childs[i].second != -1) {
        dfs(childs[i].second, childs, inorder,vals);
    }
}

void solve() {
    ll n, c; cin >> n >> c;
    vector<pair<int,int>> childs(n);
    vector<ll> vals(n);
    for(int i = 0; i < n; i++) {
        cin >> childs[i].first >> childs[i].second >> vals[i];
        if(childs[i].first > 0) childs[i].first--;
        if(childs[i].second > 0) childs[i].second--;
    }
    vector<int> inorder;
    inorder.push_back(1);
    dfs(0,childs,inorder,vals);
    inorder.push_back(c);

    ll ans = 1;

    

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}