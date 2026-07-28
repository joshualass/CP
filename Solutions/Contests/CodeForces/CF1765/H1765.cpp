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

    int n, m; cin >> n >> m;

    vector<int> a(n);
    for(int &x : a) {
        cin >> x;
        x--;
    }

    vector<vector<int>> deps(n);
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        deps[b].push_back(a);
    }

    auto check = [&]() -> int {

        // cout << "check a : " << a << endl;

        int mvp = -1;

        vector<int> ind(n), vis(n);
        vector<vector<int>> ata(n);
        for(int i = 0; i < n; i++) {
            if(a[i] == -1) {
                mvp = i;
            } else {
                ata[a[i]].push_back(i);
            }
            for(int to : deps[i]) ind[to]++;
        }

        int cnt = 0;
        queue<int> q;
        for(int x : ata[n - 1]) {
            if(ind[x] == 0) {
                vis[x] = 1;
                q.push(x);
            }
        }

        while(1) {
            int x;
            if(q.empty()) {
                return n - cnt;
            } else {
                x = q.front();
                q.pop();
            }
            // cout << "vis x : " << x << endl;
            cnt++;
            if(cnt == n) break;
            for(int other : ata[n - cnt - 1]) {
                if(ind[other] == 0 && vis[other] == 0 && other != mvp) {
                    // cout << "push other : " << other << endl;
                    vis[other] = 1;
                    q.push(other);
                }
            }
            for(int to : deps[x]) {
                ind[to]--;
                if(ind[to] == 0 && a[to] >= n - cnt - 1 && vis[to] == 0 && to != mvp) {
                    // cout << "push to : " << to << endl;
                    vis[to] = 1;
                    q.push(to);
                }
            }
        }

        return 42069;
        
    };

    for(int i = 0; i < n; i++) {
        int t = a[i];
        // int lo = 0, hi = a[i];
        // while(lo != hi) {
        //     int mid = (lo + hi) / 2;
        //     a[i] = mid;
        //     if(check()) {
        //         hi = mid;
        //     }  else {
        //         lo = mid + 1;
        //     }
        // }
        a[i] = -1;
        int res = check();
        a[i] = t;
        cout << res << " \n"[i == n - 1];
    }

    return 0;
}
