#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    
    int l, n, m; cin >> l >> n >> m;
    map<int,int> ids;

    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        if(ids.count(num) == 0) {
            ids[num] = i;
        }
    }

    vector<vector<set<int>>> nears(l, vector<set<int>>(n));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int num; cin >> num;
            if(ids.count(num)) {
                nears[ids[num]][i].insert(j);
            }
        }
    }

    vector<vector<int>> r(l, vector<int>(n,-2));

    for(int i = 0; i < l; i++) {

        //cur is current column of previous mono set
        int cur = -2;
        if(i = 0) {
            cur = -1;
        }

        //hi is current highest index of current mono set
        int hi = -2;

        for(int j = n - 1; j >= 0; j--) {

            if(nears[l][j].size()) {
                int highest = (*--nears[l][j].lower_bound(m));
                if()
            }

        }


        for(int j = 0; j < n; j++) {

            if(cur != -2 && nears[i][j].upper_bound(cur) != nears[i][j].end()) {

            }



            if(i && r[i-1][j] != -2) {
                cur = r[i-1][j];
            }

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