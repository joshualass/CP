#include <bits/stdc++.h>
typedef long long ll;
typedef __int128_t lll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q; cin >> n >> q;
    vector<pair<vector<pair<ll,ll>>,ll>> sums(0);
    for(int i = 0; i < q; i++) {
        string type; cin >> type;
        if(type == "ADD") {
            vector<pair<ll,ll>> add(0);
            for(int i = 0; i < n; i++) {
                ll li, ri; cin >> li >> ri;
                add.push_back({li,ri});
            }
            ll x; cin >> x;
            sums.push_back({add,x});
        } else if(type == "SUM") {
            ll sum = 0;
            vector<pair<ll,ll>> query(0);
            for(int j = 0; j < n; j++) {
                ll li, ri; cin >> li >> ri;
                query.push_back({li,ri});
            }
            for(int j = 0; j < sums.size(); j++) {
                ll mult = sums[j].second;
                for(int k = 0; k < n; k++) { //dimension
                    if(query[k].first > sums[j].first[k].second || query[k].second < sums[j].first[k].first) {
                        mult = 0;
                    }
                    // cout << "mult: " << mult << " lo: " <<  max(query[k].first, sums[j].first[k].first) << " hi: " << min(query[k].second, sums[j].first[k].second) << "\n";
                    mult *= min(query[k].second, sums[j].first[k].second) - max(query[k].first, sums[j].first[k].first) + 1;
                    mult %= MOD;
                    if(mult == 0) break;
                }
                if(mult) {
                    sum += mult;
                    sum %= MOD;
                }
            }
            cout << sum << "\n";
        }
    }

    return 0;
}