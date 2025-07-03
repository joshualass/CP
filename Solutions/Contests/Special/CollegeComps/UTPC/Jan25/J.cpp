#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
ll n, m, kv, kh;

const ll N = 2e5;
ll res = 0;
ll dsu[N];
ll sizes[N];

void dsubuild(ll n) {
    for(ll i = 0; i < n; i++) {
        dsu[i] = i;
        sizes[i] = 1;
    }
}

ll find(ll x) {
    if(dsu[x] == x) {
        return x;
    }
    dsu[x] = find(dsu[x]);
    return dsu[x];
}

void merge(ll x, ll y) {
    x = find(x);
    y = find(y);
    if(x == y) {
        return;
    }
    res -= 1LL * sizes[x] * sizes[x] - sizes[x] + 1LL * sizes[y] * sizes[y] - sizes[y];
    res += 1LL * (sizes[x] + sizes[y]) * (sizes[x] + sizes[y]) - (sizes[x] + sizes[y]);
    if(sizes[x] == sizes[y]) {
        dsu[y] = x;
        sizes[x] += sizes[y];
    } else {
        dsu[y] = x;
        sizes[x] += sizes[y];
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    dsubuild(N);
    cin >> n >> m >> kv >> kh;

    vector<set<ll>> r(n), c(m);
    for(ll i = 0; i < n; i++) {
        string s; cin >> s;
        for(ll j = 0; j < m; j++) {
            if(s[j] == '@') {
                r[i].insert(j);
                c[j].insert(i);
            }
        }
    }

    ll q; cin >> q;
    vector<array<ll,2>> ro(q);
    for(ll i = 0; i < q; i++) {
        ll x, y; cin >> x >> y;
        x--; y--;
        ro[i] = {x,y};
        r[x].insert(y);
        c[y].insert(x);
    }

    auto gdi = [&](ll x, ll y) -> ll {
        return x * m + y;
    };

    auto rrc = [&](ll x, ll y) -> bool {
        return r[x].lower_bound(y) == r[x].end() || (*r[x].lower_bound(y)) > y + kh;
        return 1;
    };

    auto crc = [&](ll x, ll y) -> bool {
        return c[y].lower_bound(x) == c[y].end() || (*c[y].lower_bound(x)) > x + kv;
    };

    auto getpts = [&](ll x, ll y) -> vector<array<ll,2>> {
        if(x < 0 || x >= n || y < 0 || y >= m) return {};
        vector<array<ll,2>> res;
        if(x - kv >= 0) { //go down
            if(crc(x-kv,y)) {
                res.push_back({x-kv,y});
            }
        }
        if(x + kv < n) {
            if(crc(x,y)) {
                res.push_back({x+kv,y});
            }
        }
        if(y - kh >= 0) {
            if(rrc(x,y-kh)) {
                res.push_back({x,y-kh});
            }
        }
        if(y + kh < m) {
            if(rrc(x,y)) {
                res.push_back({x,y+kh});
            }
        }
        return res;
    };

    auto tr = [&](ll x, ll y) -> bool {
        if(y + kh >= m || y < 0 || x < 0 || x >= n || rrc(x,y) == 0) return 0;
        vector<array<ll,2>> pts = getpts(x,y);
        for(auto [px, py] : pts) {
            merge(gdi(x,y+kh), gdi(px,py));
        }
        pts = getpts(x,y+kh);
        for(auto [px, py] : pts) {
            merge(gdi(x,y), gdi(px,py));
        }
        return 1;
    };

    auto tc = [&](ll x, ll y) -> bool {
        if(x + kv >= n || x < 0 || y < 0 || y >= m || crc(x,y) == 0) return 0;
        vector<array<ll,2>> pts = getpts(x,y);
        for(auto [px, py] : pts) {
            merge(gdi(x+kv,y), gdi(px,py));
        }
        pts = getpts(x+kv,y);
        for(auto [px, py] : pts) {
            merge(gdi(x,y), gdi(px,py));
        }
        return 1;
    };

    for(ll i = 0; i < n; i++) {
        for(ll j = 0; j < m; j++) {
            tr(i,j);
            tc(i,j);
        }
    }

    vector<ll> ans;
    ans.push_back(res);
    reverse(ro.begin(), ro.end());
    for(ll i = 0; i < q; i++) {
        auto [x, y] = ro[i];
        r[x].erase(y);
        c[y].erase(x);
        // cout << "i : " << i << " x : " << x << " y : " << y << '\n';
        ll sc = max(0LL,y-kh);
        if(r[x].lower_bound(y) != r[x].begin()) {
            sc = max(*--r[x].lower_bound(y) + 1, sc);
        }
        while(sc <= y) {
            // cout << "try tr x : " << x << " sc : " << sc << '\n';
            ll ok = tr(x,sc);
            if(ok == 0) break;
            sc++;
        }
        sc = max(0LL,x-kv);
        if(c[y].lower_bound(x) != c[y].begin()) {
            sc = max(*--c[y].lower_bound(x) + 1, sc);
        }
        while(sc <= x) {
            // cout << "try tc sc : " << sc << " y : " << y << '\n';
            ll ok = tc(sc,y);
            if(ok == 0) break;
            sc++;
        }
        ans.push_back(res);
    }
    reverse(ans.begin(), ans.end());
    for(ll i = 0; i <= q; i++) {
        cout << ans[i] << " \n"[i == q];
    }

    return 0;
}