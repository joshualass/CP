#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<vector<pair<ll, ll>>> routes (n);
    vector<ll> best(n, -1);
    priority_queue<pair<ll, ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>> pq;
    for(int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        routes[a-1].push_back({b - 1,c}); // inserting index, length
    }
    pq.push({0, 0});
    while(!pq.empty()) {
        pair<ll, ll> p = pq.top();
        //length index
        pq.pop();
        if(best[p.second] != -1) {
            continue;
        }
        for(int i = 0; i < routes[p.second].size(); i++) {
            pq.push({routes[p.second][i].second + p.first, routes[p.second][i].first});
        }
        best[p.second] = p.first;
    }
    for(int i = 0; i < n; i++) {
        cout << best[i] << ' ';
    }

    return 0;
}