#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int R, C; cin >> R >> C;

    vector<vector<int>> a(R,vector<int>(C));
    vector<vector<int>> b(R,vector<int>(C));

    for(auto& x : a) for(auto& y : x) cin >> y;
    for(auto &x: b) for(auto &y : x) cin >> y;

    vector<int> permR(R);
    iota(permR.begin(),permR.end(),0);
    vector<int> permC(C);
    iota(permC.begin(), permC.end(),0);

    map<vector<int>, int> distR;
    map<vector<int>, int> distC;

    queue<pair<vector<int>,int>> q;
    q.push({permR,0});

    while(q.size()) {
        auto p = q.front();
        q.pop();
        vector<int> v = p.first;
        if(distR.find(v) != distR.end()) continue;
        distR[v] = p.second;
        for(int i = 0; i < R - 1; i++) {
            swap(v[i],v[i+1]);
            if(distR.find(v) == distR.end()) {
                q.push({v,p.second+1});
            }
            swap(v[i],v[i+1]);
        }
    }

    q.push({permC,0});

    while(q.size()) {
        auto p = q.front();
        q.pop();
        vector<int> v = p.first;
        if(distC.find(v) != distC.end()) continue;
        distC[v] = p.second;
        for(int i = 0; i < C - 1; i++) {
            swap(v[i],v[i+1]);
            if(distC.find(v) == distC.end()) {
                q.push({v,p.second+1});
            }
            swap(v[i],v[i+1]);
        }
    }
    int ans = INT_MAX;
    for(auto pR : distR) {
        for(auto pC : distC) {
            bool ok = 1;
            for(int i = 0; i < R; i++) {
                for(int j = 0; j < C; j++) {
                    if(a[pR.first[i]][pC.first[j]] != b[i][j]) {
                        ok = 0;
                    }
                }
            }
            if(ok) {
                ans = min(ans, pR.second + pC.second);
            }
        }
    }
    cout << (ans == INT_MAX ? -1 : ans) << '\n';

    return 0;
}