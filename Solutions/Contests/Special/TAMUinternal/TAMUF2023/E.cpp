#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;

    vector<vector<int>> adj(m); //which pets follows this command
    vector<vector<int>> rev(n); //each pet, the commands that it follows
    vector<int> deps(m); //before we do a command, there are pets we must resolve before it
    vector<int> pet_deps(n);
    vector<int> poses(n);

    for(auto &x: poses) {cin >> x;
    x--;}


    for(int i = 0; i < m; i++) {
        int cnt; cin >> cnt;
        char trash; cin >> trash;
        for(int j = 0; j < cnt; j++) {
            int num; cin >> num;
            adj[i].push_back(num - 1);
            rev[num - 1].push_back(i);
        }
    }

    queue<int> q;

    for(int i = 0; i < n; i++) { //for each pet
        for(int command : rev[i]) {
            if(command != poses[i]) {
                // cout << "adding dependency command: " << command << " pet: " << i << " poses[i]: " << poses[i] << '\n';
                deps[command]++;
            }
        }
    }

    for(int i = 0; i < m; i++) {
        if(deps[i] == 0) {
            q.push(i);
        }
    }

    // cout << "deps: " << deps << '\n';

    vector<bool> visited(n);

    while(q.size()) {
        int cmd = q.front();
        q.pop();
        // cout << "cmd: " << cmd << '\n';
        for(auto x : adj[cmd]) {
            if(poses[x] == cmd) {
                visited[x] = true;
                for(auto cmds : rev[x]) { //this command shares a common pet with current cmd
                    deps[cmds]--;
                    if(deps[cmds] == 0) {
                        q.push(cmds);
                    }
                }
            }
        }

        // for(auto pet : adj[cmd]) { //for each pet this command pertains to
        //     for(auto cmds : rev[pet]) { //this command shares a common pet with current cmd
        //         deps[cmds]--;
        //         if(deps[cmds] == 0) {
        //             q.push(cmds);
        //         }
        //     }
        // }
    }

    bool flag = true;
    for(int i = 0; i < n; i++) {
        if(visited[i] == false) {
            flag = false;
        }
    }

    cout << (flag ? "YES" : "NO") << '\n';

    return 0;
}