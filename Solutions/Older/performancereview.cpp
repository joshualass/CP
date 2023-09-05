#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int SIZE = 1e5;

ll ans[SIZE];
ll times[SIZE];
ll manager;

ll post(ll index, vector<vector<ll>>& adj, vector<ll>& parents) {
    if(index != manager && adj[index].size() == 1) {
        return times[index];
    }
    ll sum = 0;
    for(int i = 0; i < adj[index].size(); i++) {
        if(adj[index][i] != parents[index]) {
            sum += post(adj[index][i], adj, parents);
        }
    }
    ans[index] = sum;
    return sum;

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<vector<ll>> adj(n);
    vector<ll> parents(n);

    for(int i = 0; i < n; i++) {
        ll m, r, t; cin >> m >> r >> t;
        times[i] = 

    }

    return 0;
}