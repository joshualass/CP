#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> rooms;
    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        pq.push({x,y, i});
    }
    vector<int> ans(n);
    while(pq.size()) {
        vector<int> v = pq.top();
        pq.pop();
        if(rooms.empty() || rooms.top().first > v[0]) {
            rooms.push({v[1]+1,rooms.size()+1});
            ans[v[2]] = rooms.size();
        } else {
            pair<int,int> room = rooms.top();
            rooms.pop();
            ans[v[2]] = room.second;
            rooms.push({v[1]+1,room.second});
        }
    }
    cout << rooms.size() << "\n";
    for(auto x : ans) cout << x << " ";
    cout << "\n";
    return 0;
}