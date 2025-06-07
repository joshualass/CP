#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const int N = 2e5;
int dsu[N];
int sizes[N];

void dsubuild(int n = N) {
    for(int i = 0; i < n; i++) {
        dsu[i] = i;
        sizes[i] = 1;
    }
}

int find(int x) {
    if(dsu[x] == x) {
        return x;
    }
    dsu[x] = find(dsu[x]);
    return dsu[x];
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if(x == y) {
        return;
    }
    dsu[y] = x;
    sizes[x] += sizes[y];
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    dsubuild();

    int n, q; cin >> n >> q;
    priority_queue<array<ll,3>, vector<array<ll,3>>, greater<array<ll,3>>> pq;
    vector<array<ll,2>> a;

    auto get_dist = [&](ll x1, ll y1, ll x2, ll y2) -> ll {
        return abs(x1 - x2) + abs(y1 - y2);
    };

    auto add_pt = [&](int x, int y) -> void {
        for(int i = 0; i < a.size(); i++) {
            pq.push(array<ll,3>{get_dist(a[i][0], a[i][1], x, y), i, (ll) a.size()});
        }
        a.push_back({x, y});
    };

    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        add_pt(x, y);
    }

    for(int i = 0; i < q; i++) {
        int t; cin >> t;
        if(t == 1) {
            int x, y; cin >> x >> y;
            add_pt(x, y);
        } else if(t == 2) {
            ll k = -1;
            while(pq.size()) {
                auto [dist, a, b] = pq.top();
                if(find(a) != find(b)) {
                    k = dist;
                    break;
                }
                pq.pop();
            }
            while(pq.size() && pq.top()[0] == k) {
                auto [dist, a, b] = pq.top();
                pq.pop();
                merge(a, b);
            }
            cout << k << '\n';
        } else {
            int x, y; cin >> x >> y;
            x--; y--;
            cout << (find(x) == find(y) ? "Yes" : "No") << '\n';
        }
    }


    return 0;
}
