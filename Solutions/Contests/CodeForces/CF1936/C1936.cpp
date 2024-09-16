#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

/*

read the editorial a while ago, but didn't understand what was happening.

thought about and idea arrived later. Editorial solution is not something I would come up with independently.
always nice to look at problem later

*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {

    ll n, m; cin >> n >> m;

    vector<vector<ll>> ar(n,vector<ll>(m)); //i - pokemon, j - attribute, store -> what rank in r. 
    vector<vector<ll>> avis(n,vector<ll>(m)); //i - pokemon, j - attribute, store -> if visited this pokemon for this attribute
    vector<vector<array<ll,2>>> r(m,vector<array<ll,2>>(n)); //i - attribute, j - rank, k - {attribute, pokemon at rank j}
    vector<map<ll,vector<ll>>> scores(m);
    vector<ll> costs(n); //cost of pokemon at index i
    vector<map<ll,ll>> minats(m); 

    for(ll &x : costs) cin >> x;

    for(ll i = 0; i < n; i++) {
        for(ll j = 0; j < m; j++) {
            cin >> r[j][i][0];
            r[j][i][1] = i;

            scores[j][r[j][i][0] - costs[i]].push_back(i);

        }
    }

    for(ll i = 0; i < m; i++) {
        sort(r[i].rbegin(), r[i].rend());
        for(ll j = 0; j < n; j++) {
            ar[r[i][j][1]][i] = j;
        }
    }

    vector<ll> vis(n,-1);

    priority_queue<array<ll,2>, vector<array<ll,2>>, greater<array<ll,2>>> pq; 
    pq.push({0,0});

    // need to maintain that when we visit an element, it is the next element with lowest cost. 
    while(pq.size()) {
        auto [cost, i] = pq.top();
        pq.pop();

        if(vis[i] != -1) continue;
        vis[i] = cost;

        cout << "i : " << i << " cost : " << cost << '\n';

        for(ll j = 0; j < m; j++) {
            //add all pokemon with greater attribute that haven't already been added. 
            int irank = ar[i][j];
            int iattribute = r[j][irank][0];

            for(ll k = irank; k >= 0; k--) {
                auto [attribute, pokemon] = r[j][k];
                if(avis[pokemon][j]) break;
                avis[pokemon][j] = 1;
                ll nc = cost + costs[pokemon];
                pq.push({nc, pokemon});
            }
            // add all pokemon with same level of attribute that haven't already been added. 
            for(ll k = irank + 1; k < n; k++) {
                if(r[j][k][0] == iattribute) {
                    auto [attribute, pokemon] = r[j][k];
                    if(avis[pokemon][j]) break;
                    avis[pokemon][j] = 1;
                    ll nc = cost + costs[pokemon];
                    pq.push({nc, pokemon});
                } else {
                    break;
                }
            }



            if(minats[j].lower_bound(cost) != minats[j].end() && )



            minat[j] = min(minat[j], cost + r[j][ar[i][j]][0]);

            if(scores[j].lower_bound())

            if(acr[i][j] != n - 1) { //next one should be next lowest cost. 
                auto [nextattribute, nextpokemon] = rc[j][acr[i][j] + 1];

                cout << "i : " << i << " j : " << j << " na : " << nextattribute << " np : " << nextpokemon << '\n';

                cout << "i : " << i << " pushnext : " << minat[j] - nextattribute + costs[nextpokemon] << " who : " << nextpokemon << '\n';
                cout << "comps of calc minato : " << minat[j] << " na : " << nextattribute << " cost : " << costs[nextpokemon] << '\n';

                pq.push({minat[j] - nextattribute + costs[nextpokemon], nextpokemon});
            }
        }
    }

    // cout << "allvis : " << vis << '\n';

    cout << vis[n-1] << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}