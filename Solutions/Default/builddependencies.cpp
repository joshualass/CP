#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void printV(const vector<int> &x, map<int,string> rev) {
    cout << " --- vector --- \n";
    // for(int y : x) {
    //     cout << y << " ";
    // }
    for(int i = 0; i < x.size(); i++) {
        cout << rev[i] << "- " << x[i] << "\n";
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    map<string,int> m;
    map<int,string> rev;
    vector<vector<int>> adj(n+1);
    vector<vector<int>> revadj(n+1);
    vector<int> deps(n);
    string burn; getline(cin,burn);
    for(int i = 0; i < n; i++) {
        string line; getline(cin,line);
        stringstream ss(line);
        string first;
        cout << "line: " << line << "\n";
        ss >> first;
        first.pop_back();
        int index = 0;
        cout << "first: " << first << "\n";
        if(m.find(first) == m.end()) {
            index = m.size();
            m[first] = index;
            // m.insert({index,first});
            rev[index] = first;
            // rev.insert({first,index});
        } else {
            index = m[first];
        }
        int total = 0;
        while(!ss.eof()) {
            string word; ss >> word;
            int to;
            if(m.find(word) == m.end()) {
                to = m.size();
                m[word] = to;
                // m.insert({to,word});
                rev[to] = word;
                // rev.insert({word,to});
            } else {
                index = m[word];
            }
            adj[to].push_back(index);
            revadj[index].push_back(to);
            total++;
        }
        deps[index] = total;
    }
    for(pair<string,int> p : m) {
        cout << p.first << " " << p.second << "\n";
    }
    string start; cin >> start;
    queue<string> q;
    printV(deps, rev);
    q.push(start);
    vector<bool> visited(n);
    while(q.size()) {
        string front = q.front();
        q.pop();
        int index = m[front];
        cout << front << "\n";
        for(int x : rev[index]) {
            deps[x]--;
        }
        visited[index] = true;
        for(int x : adj[index]) {
            // if(deps[x] == 0) {
            //     q.push(rev[x]);
            // }
            if(!visited[x]) {
                q.push(rev[x]);
            }
        }
    }

    return 0;
}