#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << '(' << p.first << ", " << p.second << ") ";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

vector<int> manacher_odd(string s) {
    int n = s.size();
    s = "$" + s + "^";
    vector<int> p(n + 2);
    int l = 1, r = 1;
    for(int i = 1; i <= n; i++) {
        p[i] = max(0, min(r - i, p[l + (r - i)]));
        while(s[i - p[i]] == s[i + p[i]]) {
            p[i]++;
        }
        if(i + p[i] > r) {
            l = i - p[i], r = i + p[i];
        }
    }
    return vector<int>(begin(p) + 1, end(p) - 1);
}

vector<int> manacher(string s) {
    string t;
    for(auto c: s) {
        t += string("#") + c;
    }
    auto res = manacher_odd(t + "#");
    for(auto &x : res) x--;
    return vector<int>(begin(res) + 1, end(res) - 1);
}

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    string s; cin >> s;

    vector<int> man = manacher(s);
    stringhash sh(s);

    // cout << "m : " << man << '\n';

    map<array<ll,5>,pair<int,int>> pals;

    //odd lengths 
    for(int i = 0; i < n; i++) {
        for(int j = man[i*2]/2; j >= 0; j--) {
            int l = i - j;
            int r = i + j + 1;
            if(pals.count(sh.get_hash(l,r))) break;
            pals[sh.get_hash(l,r)] = {l,r};
        }
    }

    for(int i = 0; i < n - 1; i++) {
        for(int j = man[i*2+1]/2; j >= 0; j--) {
            int l = i - j + 1;
            int r = i + j + 1;
            if(pals.count(sh.get_hash(l,r))) break;
            pals[sh.get_hash(l,r)] = {l,r};
        }
    }

    vector<ll> prefs(n+1);

    for(int i = 1; i <= n; i++) {
        prefs[i] = prefs[i-1] + s[i-1] - 'a' + 1;
    }

    ll score = 0;
    for(auto [u, v] : pals) {
        // cout << "v : " << v << '\n';
        score += prefs[v.second] - prefs[v.first];
    }
    cout << score << '\n';
    return 0;
}