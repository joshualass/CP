#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    vector<pair<vector<int>,string>> v(n);
    for(int i = 0; i < n; i++) {
        string name, clas, trash; cin >> name >> clas >> trash;
        v[i].second = name.substr(0,name.size()-1);
        int idx = 0;
        while(idx < clas.size()) {
            if(clas.substr(idx,5) == "upper") {
                v[i].first.push_back(0);
                idx += 6;
            } else if(clas.substr(idx,5) == "lower") {
                v[i].first.push_back(2);
                idx += 6;
            } else {
                v[i].first.push_back(1);
                idx += 7;
            }
        }
        reverse(v[i].first.begin(), v[i].first.end());
        while(v[i].first.size() < 10) v[i].first.push_back(1);
    }
    sort(v.begin(), v.end());
    for(int i = 0; i < n; i++) {
        cout << v[i].second << '\n';
    }
    cout << "==============================\n";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}