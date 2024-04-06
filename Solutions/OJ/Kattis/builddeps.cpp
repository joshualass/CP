#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T, typename D>
std::ostream& operator<<(std::ostream& os, map<T,D> m) {
    for(auto &x: m) os << x.first << " " << x.second << " | ";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<vector<T>> adj) {
    for(auto x : adj) {
        for(auto y : x) os << y << " ";
        os << "\n";
    }
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    unordered_map<string,int> mid;
    unordered_map<int,string> rid;
    vector<vector<int>> adj(n);
    cin.ignore();
    for(int i = 0; i < n; i++) {
        string s;
        getline(cin,s);
        // cout << "s : " << s << '\n';

        stringstream ss(s);
        string f; ss >> f;
        f = f.substr(0,f.size() - 1);
        if(mid.count(f) == 0) {
            mid[f] = mid.size();
            rid[mid[f]] = f;
        }
        int id = mid[f];
        while(!ss.eof()) {
            ss >> f;
            if(mid.count(f) == 0) {
                mid[f] = mid.size();
                rid[mid[f]] = f;
            }
            int did = mid[f];
            adj[did].push_back(id);
        }
    }

    vector<int> idg(n);
    for(int i = 0; i < n; i++) {
        for(int to : adj[i]) {
            idg[to]++;
        }
    }

    vector<string> res;
    queue<int> q;
    for(int i = 0; i < n; i++) {
        if(idg[i] == 0) {
            q.push(i);
        }
    }

    string goon; cin >> goon;
    vector<int> order;
    while(q.size()) {
        int i = q.front();
        q.pop();
        // res.push_back(rid[i]);
        order.push_back(i);
        for(int to : adj[i]) {
            idg[to]--;
            if(idg[to] == 0) {
                q.push(to);
            }
        }
    }

    // cout << "mid : " << mid << '\n';
    // cout << "adj\n" << adj;
    vector<bool> needed(n);
    needed[mid[goon]] = 1;

    for(int i = 0; i < n; i++) {
        if(needed[order[i]] == 1) {
            res.push_back(rid[order[i]]);
            for(int to : adj[order[i]]) {
                // cout << "snt : " << to << '\n';
                needed[to] = 1;
            }
        }
    }

    for(string s : res) {
        cout << s << '\n';
    }

    return 0;
}