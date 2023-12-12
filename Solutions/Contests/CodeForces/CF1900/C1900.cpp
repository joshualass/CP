#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

struct Node {
    int l, r, p;

    Node() {}
};

void solve() {
    int n; cin >> n;
    string str; cin >> str;

    vector<Node> v(n);
    for(int i = 0; i < n; i++) {
        int l, r; cin >> l >> r;
        l--; r--;
        v[i].l = l;
        v[i].r = r;
        if(l != -1) {
            v[l].p = i;
        }
        if(r != -1) {
            v[r].p = i;
        }
    }

    vector<int> visited(n,-1);

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq; //time, index
    pq.push({0,0});

    while(pq.size()) {
        pair<int,int> p = pq.top();
        pq.pop();

        if(visited[p.second] == -1) {
            visited[p.second] = p.first;
            switch(str[p.second]) {
                case 'L' :
                    if(v[p.second].l != -1) {
                        pq.push({p.first, v[p.second].l}); 
                    }
                    break;
                case 'R' :
                    if(v[p.second].r != -1) {
                        pq.push({p.first, v[p.second].r});
                    }
                    break;
                case 'U' : 
                    //we do not care
                    break;
            }
            if(v[p.second].l != -1) {
                pq.push({p.first + 1, v[p.second].l}); 
            }
            if(v[p.second].r != -1) {
                pq.push({p.first + 1, v[p.second].r});
            }
        }
    }
    int ans = INT_MAX;
    for(int i = 0; i < n; i++) {
        if(v[i].l == -1 && v[i].r == -1) {
            ans = min(ans, visited[i]);
        }
    }
    cout << ans << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}