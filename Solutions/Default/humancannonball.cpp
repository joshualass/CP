#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

ld distance_time(pair<ld,ld> one, pair<ld,ld> two) {
    ld x1 = one.first;
    ld y1 = one.second;
    ld x2 = two.first;
    ld y2 = two.second;
    ld distance = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    return 2 + abs(distance - 50) * .2;
}

ld distance_time_start(pair<ld,ld> one, pair<ld,ld> two) {
    ld x1 = one.first;
    ld y1 = one.second;
    ld x2 = two.first;
    ld y2 = two.second;
    ld distance = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    return distance * .2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<pair<ld,ld>> coords(0);
    for(int i = 0; i < 2; i++) {
        ld x, y; cin >> x >> y;
        coords.push_back({x,y});
    }    
    int cannons; cin >> cannons;
    for(int i = 0; i < cannons; i++) {
        ld x, y; cin >> x >> y;
        coords.push_back({x,y});
    } 

    vector<vector<ld>> distances(coords.size());
    vector<bool> visited(coords.size(),false);
    priority_queue<pair<ld,int>, vector<pair<ld,int>>, greater<pair<ld,int>>> pq;
    for(int i = 0; i < coords.size(); i++) {
        for(int j = 0; j < coords.size(); j++) {
            if(i == 0) {
                if(j != 0) {
                    ld distance = distance_time_start(coords[i],coords[j]);
                    pq.push({distance,j});
                }
            } else {
                distances[i].push_back(distance_time(coords[i],coords[j]));
            }
        }
    }
    visited[0] = true;
    ld ans = -1;
    while(pq.size()) {
        pair<ld,int> p = pq.top();
        pq.pop();
        if(p.second == 1) {
            ans = p.first;
            break;
        }
        if(visited[p.second]) {
            continue;
        }
        visited[p.second] = true;
        for(int i = 0; i < distances[p.second].size(); i++) {
            pq.push({p.first + distances[p.second][i], i});
        }
    }
    cout << fixed << setprecision(8) << ans << "\n";

    return 0;
}