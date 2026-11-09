#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int M, s; cin >> M >> s;
    vector<int> a(M), b(M);
    for(int &x : a) cin >> x;
    for(int &x : b) cin >> x;

    vector<array<int,2>> moves(s);
    for(auto &x : moves) {
        for(auto &y : x) {
            cin >> y;
        }
    }

    map<vector<int>, int> m;
    queue<pair<vector<int>, int>> q;
    auto pushq = [&](vector<int> perm, int time) -> void {
        if(m.count(perm) == 0) {
            m[perm] = time;
            q.push({perm, time});
        }
    };
    
    vector<int> p(M);
    iota(p.begin(), p.end(), 0);
    pushq(p, 0);

    int res = INT_MAX;

    while(sz(q)) {
        auto [perm, time] = q.front();
        q.pop();

        int ok = 1;
        for(int i = 0; i < M; i++) {
            if(a[perm[i]] != b[i]) ok = 0;
        }
        if(ok) {
            res = min(res, time);
        }
        // cout << "perm : " << perm << endl;
        for(auto [start, len] : moves) {
            vector<int> c = perm;
            rotate(c.begin(), c.begin() + start, c.end());
            // cout << "c1 : " << c << endl;
            rotate(c.begin(), c.begin() + len - 1, c.begin() + len);
            // cout << "c2 : " << c << endl;
            rotate(c.begin(), c.end() - start, c.end());
            // cout << "start : " << start << " len : " << len << " c : " << c << endl;
            pushq(c, time + 1);
        }
    }

    if(res == INT_MAX) res = -1;
    cout << res << '\n';

    return 0;
}
