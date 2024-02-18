#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

bool poss(vector<int> a, vector<int> b) {
    priority_queue<int> pq;
    for(int i : a) {
        if(i) pq.push(i);
    }
    sort(b.rbegin(), b.rend());
    for(int i : b) {
        vector<int> vals;
        while(i--) {
            if(pq.empty()) return 0;
            vals.push_back(pq.top());
            pq.pop();
        }
        for(int j : vals) {
            if(j != 1) pq.push(j-1);
        }
    }

    return 1;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;
    vector<int> rows(n);
    vector<int> cols(m);
    for(int &x : rows) cin >> x;
    for(int &x : cols) cin >> x;

    cout << (poss(rows,cols) && poss(cols,rows) ? "Yes" : "No") << '\n';

    return 0;
}