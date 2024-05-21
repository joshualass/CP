#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

// ll dfs(int a, int b, map<pair<int,int>,ll> &m, vector<int> &parents, vector<ll> &w) {
//     // cout << "a : " << a << " b : " << b << endl;
//     if(a > b) swap(a,b);
//     if(m.count({a,b})) {
//         return m[{a,b}];
//     }
//     ll res = w[a] * w[b] + dfs(parents[a], parents[b],m,parents,w);
//     m[{a,b}] = res;
//     return res;
// }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("E.in","r",stdin);
    int n, q; cin >> n >> q;
    vector<int> parents(n+1);
    vector<ll> w(n+1);

    for(int i = 1; i <= n; i++) {
        cin >> w[i];
    }

    for(int i = 2; i <= n; i++) {
        cin >> parents[i];
    }

    map<pair<int,int>,ll> m;
    m[{0,0}] = 0;
    for(int i = 0; i < q; i++) {
        int a, b; cin >> a >> b;
        // dfs(a,b,m,parents,w);

        vector<pair<int,int>> pairs;
        while(a != 0) {
            pairs.push_back({a,b});
            a = parents[a];
            b = parents[b];
        }

        reverse(pairs.begin(), pairs.end());
        for(int i = 0; i < pairs.size(); i++) {
            a = pairs[i].first;
            b = pairs[i].second;
            if(a > b) swap(a,b);
            if(m.count({a,b}) == 0) {
                m[{a,b}] = 
            }
        }

        if(a > b) swap(a,b);
        cout << m[{a,b}] << '\n';
    }
    cout << "ENDED" << endl;
    return 0;
}