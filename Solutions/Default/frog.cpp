//https://szkopul.edu.pl/problemset/problem/qDH9CkBHZKHY4vbKRBlXPrA7/site/?key=statement
// binary lifting problem. try to create reusable template here.
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

//fills vector<vector<T>> jumps with the binary jumps. MLE
// int jumps[1'000'000][64];

// template<typename T>
// void buildJumps(vector<T> &edges, vector<vector<T>> &jumps, int depth = 64) {
// void buildJumps(vector<T> &edges, int depth = 64) {
//     // jumps.assign(edges.size(), vector<T>(depth));
//     for(int i = 0; i < depth; i++) {
//         for(int j = 0; j < edges.size(); j++) {
//             if(i == 0) jumps[j][i] = (edges[j] == -1 ? j : edges[j]);
//             else jumps[j][i] = jumps[jumps[j][i-1]][i-1];
//         }
//     }
// }

//had MLE issue, just used dp and swap states. 
template<typename T>
void jumper(vector<T> &edges, vector<T> &ans, ll m, int depth = 64) {
    vector<vector<int>> jumps(edges.size(),vector<int>(2));
    for(int i = 0; i < depth; i++) {
        for(int j = 0; j < edges.size(); j++) {
            if(i == 0) {
                jumps[j][i] = edges[j];
            } else {
                jumps[j][i & 1] = jumps[jumps[j][i & 1 ^ 1]][i & 1 ^ 1];
            }
        }
        if((m >> i) & 1) {
            for(int j = 0; j < edges.size(); j++) {
                ans[j] = jumps[ans[j]][i & 1];
            }
        }
    }
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<vector<T>> adj) {
    for(auto &x : adj) {
        for(auto &y : x) os << y << " ";
        os << "\n";
    }
    return os;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, k, m; cin >> n >> k >> m;
    vector<ll> v(n);
    for(auto &x : v) cin >> x;
    vector<int> edges(n);
    int lptr = 0;
    int rptr = k;
    for(int i = 0; i < n; i++) {
        while(rptr != n - 1 && v[rptr + 1] - v[i] < v[i] - v[lptr]) {
            lptr++; rptr++;
        }
        int to = -1;
        if(v[rptr] - v[i] <= v[i] - v[lptr]) {
            to = lptr;
        } else {
            to = rptr;
        }
        edges[i] = to;
    }
    vector<int> ans(n);
    iota(ans.begin(),ans.end(),0);
    jumper(edges,ans,m);
    for(auto x : ans) cout << ++x << " ";
    cout << endl;
    return 0;
}