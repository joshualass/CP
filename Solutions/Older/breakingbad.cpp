#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    map<string,vector<string>> adj;
    for(int i = 0; i < n; i++) {
        string line; cin >> line;
        adj.insert({line,vector<string>(0)});
    }

    int m; cin >> m;
    for(int i = 0; i < m; i++) {
        string a,b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<set<string>> carries (2);
    bool flag = true;
    for(pair<string,vector<string>> p : adj) {
        string name = p.first;
        vector<string> lists = p.second;
        if(carries[0].find(name) != carries[0].end() || carries[1].find(name) != carries[1].end()) {
            continue;
        }
        queue<pair<string,int>> q;
        q.push({p.first,0});
        while(q.size()) {
            pair<string,int> item = q.front();
            q.pop();
            if(carries[0].find(item.first) != carries[0].end() || carries[1].find(item.first) != carries[1].end()) {  //check if it has been used
                if(((bool)(carries[0].find(item.first) == carries[0].end())) != (item.second % 2)) {// check if it's in wrong set
                    flag = false;
                    break;
                }
                continue;
            }
            carries[item.second % 2].insert(item.first);
            for(string x : adj[item.first]) {
                q.push({x, item.second + 1});
            }
        }
        if(!flag) {
            break;
        }
    }

    if(!flag) {
        cout << "impossible";
    } else {
        for(int i = 0; i < carries.size(); i++) {
            for(string x : carries[i]) {
                cout << x << " ";
            }
            cout << '\n';
        }
    }

    return 0;
}