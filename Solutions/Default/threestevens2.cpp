#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    while(t-->0) {
        int m; cin >> m;
        vector<pair<int,int>> sizes(m);
        vector<vector<int>> adj(m);
        set<int> gone; 
        for(int i = 0; i < m; i++) {
            int n; cin >> n;
            sizes[i].second = i;
            sizes[i].first = n;
            for(int l = 0; l < n; l++) {
                int num; cin >> num;
                adj[i].push_back(num);
            }
        }
        bool flag = true;
        sort(sizes.begin(),sizes.end());
        vector<int> out(m);
        for(int i = 0; i < m; i++) {
            int day = sizes[i].second;
            bool found = false;
            for(int r = 0; r < adj[day].size(); r++) {
                if(gone.find(adj[day][r]) == gone.end()) {
                    out[day] = adj[day][r];
                    found = true;
                    gone.insert(adj[day][r]);
                    break;
                }
            }
            if(!found) {
                flag = false;
                break;
            }
        }
        if(flag) {
            for(int x : out) {
                cout << x << ' ';
            }
        } else {
            cout << "-1";
        }
        cout << '\n';
    }

    return 0;
}