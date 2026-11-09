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

void solve() {
    
    int n; cin >> n;
    vector<int> a(n), b(n);
    int ok = 1;
    for(int &x : a) {
        cin >> x;
        x--;
    }
    
    for(int i = 0; i < n; i++) {
        cin >> b[i];
        b[i]--;
        if(a[i] > b[i]) ok = 0;
    }

    auto get_next = [&]() -> int {
        for(int i = 0; i < n; i++) {
            if(a[i] != b[i]) return i;
        }
        return n;
    };

    int cur = get_next();

    int p = min(cur, n - 1);
    vector<int> ops;

    while(cur != n && ok) {

        // cout << "cur : " << cur << endl;
        // cout << "a : " << a << endl;
        // cout << "b : " << b << endl;

        int add = b[cur] - a[cur];
        for(int i = 0; i < add; i++) {
            ops.push_back(1);
        }
        a[cur] += add;

        vector<int> p(n, -1);

        priority_queue<int, vector<int>, greater<int>> pq;
        p[cur] = cur;

        pq.push(cur);
        while(sz(pq)) {
            int x = pq.top();
            pq.pop();
            for(int i = a[x]; i <= b[x]; i++) {
                if(p[i] == -1) {
                    p[i] = x;
                    pq.push(i);
                }
            }
        }

        // cout << "p : " << p << endl;

        int nx = get_next();
        vector<int> path;

        // cout << "nx : " << nx << endl;
        
        if(nx == n) {
            break;
        } else if(p[nx] == -1) {
            ok = 0;
            break;
        }

        int t = nx;
        while(t != cur) {
            path.push_back(t);
            t = p[t];
        }

        reverse(path.begin(), path.end());

        // cout << "path : " << path << endl;

        for(int x : path) {
            int add = x - a[cur];
            for(int i = 0; i < add; i++) ops.push_back(1);
            a[cur] += add;
            ops.push_back(2);
            cur = a[cur];
        }
    }

    if(ok) {
        cout << sz(ops) << " " << p + 1 << '\n';
        cout << ops << '\n';
    } else {
        cout << "-1\n";
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}