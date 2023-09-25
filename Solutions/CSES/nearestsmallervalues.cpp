#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<pair<int,int>> v(n);
    for(int i = 0; i < n; i++) {
        cin >> v[i].first;
        v[i].second = i;
    }

    sort(v.begin(),v.end(),[](const pair<int,int> &lhs, const pair<int,int>& rhs) {
        if(lhs.first == rhs.first) {
            return lhs.second > rhs.second;
        } else {
            return lhs.first < rhs.first;
        }
    });
    set<int> s; s.insert(INT_MAX);
    vector<int> ans(n);
    for(int i = 0; i < n; i++) {
        int idx = v[i].second;
        set<int>::iterator it = s.lower_bound(idx);
        if(it != s.begin()) {
            ans[idx] = *(--it) + 1;
        }
        s.insert(idx);
    }
    for(auto x : ans) cout << x << " ";
    cout << endl;
    return 0;
}