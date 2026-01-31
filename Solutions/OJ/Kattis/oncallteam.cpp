#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

/*
cool idea to solve by Geothermal that doesn't use marriage theorem
for each bit, we store all the sets that are found, but don't include that bit
this allows us to iterate over each engineer, and for each enginer with a bit turned on, 
we can mark all those sets as found and then add to the next bits
This approach sort of works because we assign each engineer only 1 task. 
*/

//sets current set to found and for each bit, adds the missing the current found sets that are missing that bit
// bitset<1 << 20> found {};
vector<int> found(1 << 20);
void addfound(int foundval, vector<vector<int>> &missing_sets) {
    found[foundval] = 1;
    for(int bit = 0; bit < missing_sets.size(); bit++) {
        if(((foundval >> bit) & 1) == 0) {
            // cout << "inserting to bit : " << bit << " fv : " << foundval << '\n';
            missing_sets[bit].push_back(foundval);
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;
    
    vector<vector<int>> missing_sets(m);
    addfound(0,missing_sets);

    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        unordered_set<int> next_found;
        for(int bit = 0; bit < m; bit++) {
            if(s[bit] == '1') {
                // cout << "i : " << i << " bit : " << bit << '\n';
                for(int ms : missing_sets[bit]) {
                    if(found[ms | (1 << bit)] == 0) {
                        // cout << "add nf : " << (ms | (1 << bit)) << '\n';
                        next_found.insert(ms | (1 << bit));
                    }
                }
                missing_sets[bit].clear();
            }
        }
        for(int nf : next_found) {
            addfound(nf,missing_sets);
        }
    }

    int ans = m;

    // cout << "found : " << found << '\n';

    for(int i = 0; i < 1 << m; i++) {
        if(found[i] == 0) {
            ans = min(ans, __builtin_popcount(i) - 1);
        }
    }

    cout << ans << '\n';

    return 0;
}