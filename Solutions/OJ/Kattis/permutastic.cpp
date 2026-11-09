#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

pair<ll,ll> MODS[5] = {
    {(ll)998244353, (ll)9973},
    {(ll)1000000007, (ll)9931},
    {(ll)1000000009, (ll)9967},
    {(ll)1000000207, (ll)9949},
    {(ll)1000000409, (ll)9941}
};

ll ch[26][5];

struct stringhash {
    vector<ll> h[5];
    vector<ll> p[5];
    int n;

    vector<ll> ph[5];

    stringhash(string s) {
        this->n = s.size();
        for(int i = 0; i < 5; i++) {
            p[i].push_back(1);
            h[i].push_back(0);
            ph[i].push_back(0);
        }
        for(int i = 0; i < 5; i++) {
            for(int j = 0; j < n; j++) {
                p[i].push_back(p[i].back() * MODS[i].second % MODS[i].first);
            }
        }
        for(int i = 0; i < 5; i++) {
            for(int j = 0; j < n; j++) {
                h[i].push_back((h[i][j] * MODS[i].second + s[j]) % MODS[i].first);
            }
        }
        for(int i = 0; i < 5; i++) {
            for(int j = 0; j < n; j++) {
                ph[i].push_back(ph[i].back() + ch[s[j] - 'a'][i]);
            }
        }
    }

    array<ll,5> get_hash(int l, int r) { //[l,r) because that's the cool, Andwerp way
        array<ll,5> a = {-1,-1,-1,-1,-1};
        for(int i = 0; i < 5; i++) {
            a[i] = (h[i][r] - h[i][l] * p[i][r-l] % MODS[i].first + MODS[i].first) % MODS[i].first;
        }
        return a;
    }

    array<ll,5> get_set(int l, int r) {
        array<ll,5> res = {};
        for(int i = 0; i < 5; i++) {
            res[i] = ph[i][r] - ph[i][l];
        }
        return res;
    }

};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for(int i = 0; i < 26; i++) {
        for(int j = 0; j < 5; j++) {
            ch[i][j] = rng() % (1LL << 32);
        }
    }

    string s, t; cin >> s >> t;
    stringhash sh(s), th(t);
    set<array<ll,5>> vsh, vh;

    for(int i = 0; i < sz(s); i++) {
        for(int len = 3; i + len <= sz(s); len++) {
            vsh.insert(sh.get_hash(i, i + len));
        }
    }

    for(int i = 0; i < sz(t); i++) {
        for(int len = 3; i + len <= sz(t); len++) {
            if(vsh.count(th.get_hash(i, i + len))) {
                // cout << "vis string : " << t.substr(i, len) << endl;
                vh.insert(th.get_set(i, i + len));
            }
        }
    }

    cout << sz(vh) << '\n';

    return 0;
}
