#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;
    vector<string> mat;

    string s = "";
    for(int i = 0; i < m + 2; i++) {
        s.push_back('.');
    }
    mat.push_back(s);
    for(int i = 0; i < n; i++) {
        string b; cin >> b;
        mat.push_back(".");
        mat.back().append(b);
        mat.back().push_back('.');
    }
    mat.push_back(s);

    vector<vector<int>> dists(n+2,vector<int>(m+2,-1));

    priority_queue<array<int,3>, vector<array<int,3>>, greater<array<int,3>>> pq;
    pq.push({0,0,0});

    while(pq.size()) {
        array<int,3> = pq.top();
        pq.pop();
    }


    return 0;
}