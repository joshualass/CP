#include <bits/stdc++.h>

using namespace std;
using ll = long long;

template<typename T>
ostream& operator<<(ostream& os, const deque<T>& d) {
    for (auto x : d) os << x << " ";
    return os;
}

int main() {

    ll n; cin >> n;
    map<string, set<string> > fileGraph;
    map<string , int> depen;
    deque<string> bfs;
    set<string> ttfang;
    
    cin.ignore();

    for (int i = 0; i < n; i++) {
        string f;
        getline(cin, f);

        stringstream files (f);

        files >> f;
        f = f.substr(0, f.size()-1);

        ttfang.insert(f);
            
        string dep;
    
        while (files >> dep) {
            fileGraph[dep].insert(f);
            depen[f]++;
        }
        if(depen[f] != 2) cout << "f : " << f << endl;
    }

    for(string x : ttfang) {
        if(depen.count(x) == 0) bfs.push_back(x);
    }

    cout << "bfs : " << bfs << endl;

    string recomp; cin >> recomp;
    set<string> comp;

    stack<string> dfs; dfs.push(recomp);

    while (!dfs.empty()) {
        string a = dfs.top(); dfs.pop();

        if (comp.count(a))
            continue;

        comp.insert(a);

        for (string d : fileGraph[a]) {
            dfs.push(d);
        }
    }

    while (!bfs.empty()) {
        string f = bfs.front();
        bfs.pop_front();

        if (comp.count(f))
            cout << f << "\n";
            

        for (auto depd : fileGraph[f]) {
            assert(depen[depd] > 0);
            depen[depd]--;
            if (depen[depd] == 0) {
                bfs.push_back(depd);
            }
        }
    }

    return 0;
}