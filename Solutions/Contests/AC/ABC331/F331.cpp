#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

//does not work sometimes, but why?

ll hashes[26];
ll hashes1[26];

template<typename T>
struct Tree {
    static constexpr T base = 0;
    T f(T a, T b) {
        return a + b; //update this function for different types of queries, currently sum
    }
    vector<T> s; int n;
    Tree(int n = 0, T def = base) : s(n*2,def), n(n) {}
    void build() {
        for(int i = n - 1; i > 0; i--) s[i] = f(s[i*2],s[i*2+1]);
    }
    void update(int pos, T val) {
        for(s[pos += n] = val; pos /= 2;) s[pos] = f(s[pos*2],s[pos*2+1]);
    }
    T query(int l, int r) { //[l,r)
        T ans = base;
        for(l += n, r += n; l < r; l /= 2, r /= 2) {
            if(l & 1) ans = f(ans, s[l++]);
            if(r & 1) ans = f(s[--r],ans);
        }
        return ans;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // freopen("smallin.txt","r",stdin);
    // freopen("test.out","w",stdout);
    
    srand(chrono::steady_clock::now().time_since_epoch().count());
    set<ll> s;
    for(int i = 0; i < 26; i++) {
        ll nexthash = (RAND_MAX * (ll) rand() + (ll)rand()) % MOD;
        while(s.find(nexthash) != s.end()) {
            nexthash = (RAND_MAX * (ll) rand() + (ll)rand()) % MOD;
        }
        hashes[i] = nexthash;
        s.insert(nexthash);
        // cout << hashes[i] << '\n';
    }

    for(int i = 0; i < 26; i++) {
        ll nexthash = (RAND_MAX * (ll) rand() + (ll)rand()) % MOD;
        while(s.find(nexthash) != s.end()) {
            nexthash = (RAND_MAX * (ll) rand() + (ll)rand()) % MOD;
        }
        hashes1[i] = nexthash;
        s.insert(nexthash);
        // cout << hashes[i] << '\n';
    }

    int n, q; cin >> n >> q;

    Tree<ll> cnts(n);
    Tree<ll> fwdS(n);
    Tree<ll> RevS(n);
    Tree<ll> cnts1(n);
    Tree<ll> fwdS1(n);
    Tree<ll> RevS1(n);

    string str; cin >> str;

    for(int i = 0; i < n; i++) {
        ll hash = hashes[str[i] - 'a'];
        cnts.update(i, hash);
        fwdS.update(i, hash * (i + 1));
        RevS.update(i, hash * (n - i));
        hash = hashes1[str[i] - 'a'];
        cnts1.update(i, hash);
        fwdS1.update(i, hash * (i + 1));
        RevS1.update(i, hash * (n - i));
    }
    int cnt = 0;
    for(int i = 0; i < q; i++) {
        int type; cin >> type;
        if(type == 1) {
            ll idx; cin >> idx;
            char c; cin >> c;
            idx--;
            ll hash = hashes[c - 'a'];
            cnts.update(idx, hash);
            fwdS.update(idx, hash * (idx + 1));
            RevS.update(idx, hash * (n - idx));
            hash = hashes1[c - 'a'];
            cnts1.update(idx, hash);
            fwdS1.update(idx, hash * (idx + 1));
            RevS1.update(idx, hash * (n - idx));
            str[idx] = c;
        } else if(type == 2) {
            ll l, r; cin >> l >> r;
            l--; r--;
            bool ok = 1;
            // if(cnt == 4324 || cnt == 26071 || cnt == 26852 || cnt == 46805 || cnt == 49498) {
            //     cout << "str: " << str << " l : " << l << " r : " << r << '\n';
            // }
            {
                ll fwdStart = (l + r + 1) / 2;
                ll fS = fwdS.query(fwdStart, r + 1) - cnts.query(fwdStart, r + 1) * fwdStart;
                // cout << "f1 : " << fwdS.query(fwdStart, r + 1) << " s1 : " << cnts.query(fwdStart, r + 1) * fwdStart << '\n';
                ll revStart = (l + r) / 2;
                ll rS = RevS.query(l, revStart + 1) - cnts.query(l, revStart + 1) * (n - revStart - 1);
                if(fS != rS) ok = 0;
            }
            {
                ll fwdStart = (l + r + 1) / 2;
                ll fS = fwdS1.query(fwdStart, r + 1) - cnts1.query(fwdStart, r + 1) * fwdStart;
                // cout << "f1 : " << fwdS.query(fwdStart, r + 1) << " s1 : " << cnts.query(fwdStart, r + 1) * fwdStart << '\n';
                ll revStart = (l + r) / 2;
                ll rS = RevS1.query(l, revStart + 1) - cnts1.query(l, revStart + 1) * (n - revStart - 1);
                if(fS != rS) ok = 0;
            }
            // cout << "f2 : " << RevS.query(l, revStart + 1) << " s2 : " << cnts.query(l, revStart + 1) * (n - revStart - 1) << '\n';
            // cout << "fS : " << fS << " rS : " << rS << '\n';
            // if(cnt == 4324 || cnt == 26071 || cnt == 26852 || cnt == 46805 || cnt == 49498) {
            //     cout << "fS : " << fS << " rS : " << rS << '\n';
            // }

            if(r - l <= 100) {
                for(int i = 0; i <= r - l; i++) {
                    if(str[i + l] != str[r - i]) ok = 0;
                }
            }

            if(ok) {
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }
            cnt++;
        }
    }

    return 0;
}