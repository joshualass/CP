#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, d; cin >> n >> d;
    vector<array<int,2>> a(n);
    set<int> s;
    for(auto &x : a) {
        for(auto &y : x) {
            cin >> y;
            s.insert(y);
        }
    }

    s.insert(d);

    map<int,int> cm;
    int p = 0;
    for(int x : s) cm[x] = p++;

    d = cm[d];
    for(auto &x : a) {
        for(auto &y : x) {
            y = cm[y];
        }
    }

    

    return 0;
}
