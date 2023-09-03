#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

vector<vector<int>> adj;
vector<vector<int>> transpose;
map<string,int> words;
vector<int> weights;
int ticker = 0;
vector<bool> visited;
stack<int> s;

void printGraph(vector<vector<int>> adj) {
    for(int r = 0; r < adj.size(); r++) {
        cout << "i: " << r;
        for(int c = 0; c < adj[r].size(); c++) {
            cout << " " << adj[r][c];
        }
        cout << "\n";
    }
}

void DFS(int index) {
    visited[index] = true;
    // cout << "index: " << index << "\n";

    for(int x : adj[index]) {
        // cout << "testing? " << x << " " << !visited[x] << "\n";
        if(!visited[x]) {
            // cout << "DFSing: " << x << "\n";
            DFS(x);
        }
    }
    s.push(index);
}

int DFS2(int index) {
    visited[index] = true;
    int total = weights[index];
    // cout << "index: " << index << " total: " << total << " weights[index]: " << weights[index] << "\n";
    for(int x : transpose[index]) {
        if(!visited[x]) {
            total += DFS2(x);
        }
    }
    // cout << "total after: " << total << "\n";
    return total;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin >> n;
    int siz = n;
    string burn;
    getline(cin, burn);
    weights.resize(0);
    while(n-->0) {
        string line; getline(cin, line);
        stringstream ss(line);
        ss >> burn;
        string from;
        ss >> from;
        int from_index = -1;
        if(words.find(from) == words.end()) {
            words[from] = ticker;
            from_index = ticker++;
            weights.push_back(0);
            adj.push_back({});
            transpose.push_back({});
        } else {
            from_index = words[from];
        }
        weights[from_index]++;
        while(!ss.eof()) {
            string word;
            ss >> word;
            int to = -1;
            if(words.find(word) == words.end()) {
                words[word] = ticker;
                to = ticker++;
                weights.push_back(0);
                adj.push_back({});
                transpose.push_back({});
            } else {
                to = words[word];
            }
            adj[from_index].push_back(to);
            transpose[to].push_back(from_index);
        }
    }
    // for(auto entry : words) {
    //     cout << entry.first << " " << adj[entry.second].size() << "\n";
    // }
    visited.assign(ticker,false);
    for(int i = 0; i < ticker; i++) {
        if(!visited[i]) {
            DFS(i);
        }
    }
    visited.assign(ticker,false);
    int largest_comp = -1;
    while(s.size()) {
        int i = s.top();
        s.pop();
        // cout << i << "\n";
        if(!visited[i]) {
            largest_comp = max(largest_comp,DFS2(i));
        }
    }
    cout << siz - largest_comp << "\n";
    // cout << "\n\n";
    // printGraph(adj);
    // cout << "\ntranspose:\n";
    // printGraph(transpose);
    return 0;
}