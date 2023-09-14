#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    string s; cin >> s;

    vector<vector<int>> idxs(10);
    vector<int> ptrs(10);
    for(int i = 0; i < s.size(); i++) {
        idxs[s[i] - '0'].push_back(i);
    }

    int m; cin >> m;
    string l, r; cin >> l >> r;
    int idx = -1;
    for(int i = 0; i < m; i++) {
        int latest = -1;
        for(int t = 0; t <= 9; t++) {
            if(t >= l[i] - '0' && t <= r[i] - '0') {
                while(ptrs[t] < idxs[t].size() && idxs[t][ptrs[t]] <= idx) {
                    ptrs[t]++;
                }
                if(ptrs[t] == idxs[t].size()) {
                    // cout << "t: " << t << " ptrs[t]: " << ptrs[t] << " size: " << idxs[t].size() << "\n";
                    cout << "YES\n";
                    return;
                }
                latest = max(latest,idxs[t][ptrs[t]]);
            }
        }
        idx = latest;
        // cout << idx << " ";
    }
    cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int casi; cin >> casi;
    while(casi-->0) solve();
    return 0;
}