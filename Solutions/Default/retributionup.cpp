#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, p;
    cin >> n >> m >> p;
    vector<pair<int, int>> judges;
    vector<pair<int, int>> tars;
    vector<pair<int, int>> feathers;
    set<int> j;
    set<int> t;
    set<int> f;
    for(int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        judges.push_back({x, y});
    }
    for(int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        tars.push_back({x, y});
    }
    for(int i = 0; i < p; i++) {
        int x, y;
        cin >> x >> y;
        feathers.push_back({x, y});
    }

    priority_queue<pair<ld, pair<int,int>>, vector<pair<ld, pair<int, int>>>, greater<pair<ld, pair<int,int>>>> pq; //min heap
    for(int i = 0; i < n; i++) {
        for(int s = 0; s < m; s++) {
            pq.push({sqrt(pow(((ld)judges[i].first) - tars[s].first , 2) + pow(((ld)judges[i].second) - tars[s].second, 2)) , {i, s}}); // judge #, tar #
        }
    }
    ld total = 0;
    while(j.size() != n) {
        pair<ld, pair<int,int>> p = pq.top();
        total += p.first;
        j.insert(p.second.first);
        t.insert(p.second.second);
        while((pq.size()) && j.size() != 0 && (j.find(pq.top().second.first) != j.end() || t.find(pq.top().second.second) != t.end())) {
            pq.pop();
        }
    }
    pq = priority_queue<pair<ld, pair<int,int>>, vector<pair<ld, pair<int, int>>>, greater<pair<ld, pair<int,int>>>>();
    for(int i = 0; i < n; i++) {
        for(int s = 0; s < p; s++) {
            pq.push({sqrt(pow(((ld)judges[i].first) - feathers[s].first, 2) + pow(((ld)judges[i].second) - feathers[s].second, 2)), {i, s}});
        }
    }
    j.clear();
    while(j.size() != n) {
        pair<ld, pair<int,int>> p = pq.top();
        total += p.first;
        j.insert(p.second.first);
        f.insert(p.second.second);
        while((pq.size()) && j.size() != 0 && (j.find(pq.top().second.first) != j.end() || f.find(pq.top().second.second) != f.end())) {
            pq.pop();
        }
    }

    cout << fixed << setprecision(8) << total;

    return 0;
}