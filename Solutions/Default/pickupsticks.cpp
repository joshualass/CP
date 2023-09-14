#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n,vector<int>(0));
    vector<int> left(n);
    set<int> removed;
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[--a].push_back(--b);
        left[b]++;
    }
    queue<int> q;
    for(int i = 0; i < n; i++) {
        q.push(i);
    }
    string out = "";
    while(q.size()) {
        int stick = q.front();
        q.pop();
        if(removed.find(stick) != removed.end()) {
            continue;
        }
        if(left[stick] == 0) {
            out += to_string(stick+1) + "\n";
            removed.insert(stick);
            for(int x : adj[stick]) {
                left[x]--;
                q.push(x);
            }
        }
    }
    bool flag = true;
    for(int i = 0; i < n; i++) {
        if(left[i] != 0) {
            flag = false;
            break;
        }
    }
    cout << (flag ? out : "IMPOSSIBLE");

    return 0;
}