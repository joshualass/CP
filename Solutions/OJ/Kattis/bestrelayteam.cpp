#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<pair<pair<double,double>, string>> a(n);
    for(auto &x : a) {
        cin >> x.second >> x.first.first >> x.first.second;
    }
    ld bestscore = 1e9;
    vector<string> bestnames;
    sort(a.begin(), a.end(), [](auto &lhs, auto &rhs) -> bool {
        return lhs.first.second < rhs.first.second;
    });
    for(int i = 0; i < n; i++) {
        vector<string> names;
        names.push_back(a[i].second);

        ld currscore = a[i].first.first;
        for(int j = 0; names.size() != 4; j++) {
            if(i != j) {
                currscore += a[j].first.second;
                names.push_back(a[j].second);
            }
        }
        // cout << "cs : " << currscore << '\n';
        if(currscore < bestscore) {
            // currscore = bestscore;
            bestscore = currscore;
            bestnames = names;
        }
    }

    cout << bestscore << '\n';
    for(auto x : bestnames) cout << x << '\n';

    return 0;
}