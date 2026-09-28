#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;
ll SQN = 750;

//why no worky :(

std::ostream& operator<<(std::ostream& os, array<ll,3> s) {
    for(auto &x: s) os << x << " ";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

struct node {
    vector<bool> s;
    vector<ll> c;
    ll k, size;

    array<ll,3> l, r; //outside, inside, size

    node(vector<ll> c, ll k) {
        this->c = c;
        this->k = k;
        this->size = 0;
        this->s.assign(c.size(),0);
    }

    void toggle(ll idx) {
        if(s[idx]) {
            size++;
            s[idx] = 0;
        } else {
            size--;
            s[idx] = 1;
        }
        updateLeft();
        updateRight();
    }

    void updateLeft() {
        l = {-1,-1,0};
        for(ll i = 0; i < s.size(); i++) {
            if(s[i]) {
                if(l[0] == -1) {
                    l[0] = c[i];
                    l[1] = c[i];
                    l[2]++;
                } else if(c[i] - l[1] <= k) {
                    l[1] = c[i];
                    l[2]++;
                }
            }
        }
    }

    void updateRight() {
        r = {-1,-1,0};
        for(ll i = s.size() - 1; i >= 0; i--) {
            if(s[i]) {
                if(r[0] == -1) {
                    r[0] = c[i];
                    r[1] = c[i];
                    r[2]++;
                } else if(r[1] - c[i] <= k) {
                    r[1] = c[i];
                    r[2]++;
                }
            }
        }
    }

    array<ll,3> query(ll idx) {
        // cout << "idx : " << idx << '\n';
        // cout << "s : " << s << '\n';
        // cout << "c : " << c << '\n';
        array<ll,3> res = {c[idx],c[idx],1};
        for(ll i = idx + 1; i < s.size(); i++) {
            if(s[i] && c[i] - res[1] <= k) {
                res[1] = c[i];
                res[2]++;
            }
        }
        for(ll i = idx - 1; i >= 0; i--) {
            if(s[i] && res[0] - c[i] <= k) {
                res[0] = c[i];
                res[2]++;
            }
        }
        return res;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll q, k; cin >> q >> k;
    vector<array<ll,2>> queries(q);
    set<ll> s;

    for(ll i = 0; i < q; i++) {
        cin >> queries[i][0] >> queries[i][1];
        s.insert(queries[i][1]);
    }

    map<ll,array<ll,2>> m;
    vector<node> a;
    vector<ll> c;
    for(ll x : s) {
        m[x] = {(ll) a.size(),(ll)  c.size()};
        c.push_back(x);
        if(c.size() == SQN) {
            a.push_back(node(c,k));
            c.clear();
        }
    }

    if(c.size()) {
        a.push_back(node(c,k));
    }

    for(auto query: queries) {
        ll type = query[0];
        array<ll,2> id = m[query[1]];
        // cout << "query : " << query[0] << ", " << query[1] << '\n';
        if(type == 1) {
            a[id[0]].toggle(id[1]);
            // cout << "l : " << a[id[0]].l << " r : " << a[id[0]].r << '\n';
        } else {
            array<ll,3> res = a[id[0]].query(id[1]);
            assert(a[id[0]].s[id[1]]);
            // cout << "res : " << res << '\n';
            for(ll i = id[0] + 1; i < a.size(); i++) {
                if(a[i].size && a[i].l[0] - res[1] <= k) {
                    res[1] = a[i].l[1];
                    res[2] += a[i].l[2];
                }
            }
            for(ll i = id[0] - 1; i >= 0; i--) {
                if(a[i].size && res[0] - a[i].r[0] <= k) {
                    res[0] = a[i].r[1];
                    res[2] += a[i].r[2];
                }
            }
            cout << res[2] << '\n';
        }
    }

    return 0;
}