pair<ll,ll> MODS[5] = {
    {(ll)998244353, (ll)9973},
    {(ll)1000000007, (ll)9931},
    {(ll)1000000009, (ll)9967},
    {(ll)1000000207, (ll)9949},
    {(ll)1000000409, (ll)9941}
};

struct stringhash {
    vector<ll> h[5];
    vector<ll> p[5];
    int n;

    stringhash(string s) {
        this->n = s.size();
        for(int i = 0; i < 5; i++) {
            p[i].push_back(1);
            h[i].push_back(0);
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
    }

    array<ll,5> get_hash(int l, int r) { //[l,r) because that's the cool, Andwerp way
        array<ll,5> a = {-1,-1,-1,-1,-1};
        for(int i = 0; i < 5; i++) {
            a[i] = (h[i][r] - h[i][l] * p[i][r-l] % MODS[i].first + MODS[i].first) % MODS[i].first;
        }
        return a;
    }

};