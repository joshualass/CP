#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const int N = 2e5;
const int depth = 20;

int comps[N];
bool incycle[N];
int depths[N]; //depth from the cycle OR index in the cycle
int edges[N][depth];
vector<vector<int>> reserves;
bool visited[N];

void dfscomps(int n, int id) {
    if(!visited[n]) {
        visited[n] = true;
        comps[n] = id;
        dfscomps(edges[n][0], id);
        for(auto &x: reserves[n]) {
            dfscomps(x, id);
        }
    }
}

int findcyclenode(int n) {
    if(visited[n]) {
        return n;
    }
    visited[n] = true;
    return findcyclenode(edges[n][0]);
}

int setcycle(int n, int cycle, int &p) {
    if(n == p && cycle) {
        return cycle;
    }
    incycle[n] = true;
    depths[n] = cycle++;
    return setcycle(edges[n][0], cycle, p);
}

void setdepths(int n, int d) {
    if(visited[n]) {
        return;
    }
    visited[n] = true;
    if(!incycle[n]) {
        d++;
        // cout << "setting depths " << n << " " << d << "\n";
        depths[n] = d;
        for(auto &x: reserves[n]) {
            setdepths(x, d);
        }
    } else {
        // cout << "n? " << n << "\n";
        for(auto &x: reserves[n]) {
            setdepths(x, d);
        }       
    }
}

void clearvisited(int n) {
    if(visited[n]) {
        visited[n] = false;
        clearvisited(edges[n][0]);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    fill(begin(comps), begin(comps) + N, -1);
    fill(begin(incycle), begin(incycle) + N, false);
    fill(begin(visited), begin(visited) + N, false);
    map<int,int> cyclesizes;
    int n, q; cin >> n >> q;
    reserves.assign(n, {});
    //set edges
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        --num;
        edges[i][0] = num;
        reserves[num].push_back(i);
    }
    int idx = 0;
    //first find components
    for(int i = 0; i < n; i++) {
        if(comps[i] == -1) {
            dfscomps(i, idx);
            idx++;
        }
    }
    fill(begin(visited), begin(visited) + N, false);
    idx = 0;
    //set whether in cycle as well as the depth in cycle or depth from being in the cycle
    for(int i = 0; i < n; i++) {
        if(comps[i] == idx) {
            int n = findcyclenode(i);
            clearvisited(i);
            cyclesizes[idx] = setcycle(n, 0, n);
            setdepths(n, 0);
            idx++;
        }
    }
    //do binary lifts
    for(int p = 1; p < depth; p++) {
        for(int i = 0; i < n; i++) {
            edges[i][p] = edges[edges[i][p-1]][p-1];
        }
    }
    //now I'm done with preprocessing ?!

    // for(auto x : cyclesizes) {
    //     cout << x.first << " " << x.second << "\n";
    // }
    for(int i = 0; i < 10; i++) {
        // cout << "i: " << i << " depths[i]: " << depths[i] << "\n";
    }
    for(int i = 0; i < 10; i++) {
        // cout << "i: " << i << " incycle[i]: " << incycle[i] << "\n";
    }

    for(int i = 0; i < q; i++) {
        int a, b; cin >> a >> b;
        a--;
        b--;
        if((!incycle[b] && (incycle[a] || (!incycle[a] && depths[b] > depths[a]))) || comps[a] != comps[b]) {
            cout << "-1\n";
        } else {
            if(incycle[a] && incycle[b]) {//both nodes in cycle
                int size = cyclesizes[comps[a]];
                cout << (depths[b] - depths[a] + size) % size << "\n";
            } else if(!incycle[a] && !incycle[b]) {//neither in cycle, try moving a to b
                int moves = depths[a] - depths[b];
                int k = depths[a] - depths[b];
                int p = 0;
                while(k != 0) {
                    if(k & 1) {
                        a = edges[a][p];
                    }
                    k >>= 1;
                    p++;
                }
                cout << (a == b ? moves : -1) << "\n";
            } else { //b is in cycle while a is not
                int moves = depths[a];
                int k = depths[a];
                int p = 0;
                // cout << "a: " << a << " b: " << b << "\n";
                while(k != 0) {
                    if(k & 1) {
                        a = edges[a][p];
                    }
                    k >>= 1;
                    p++;
                }
                // cout << "a: " << a << " b: " << b << "\n";
                int size = cyclesizes[comps[a]];
                cout << moves + (depths[b] - depths[a] + size) % size << "\n";
            }
        }
    }

    return 0;
}