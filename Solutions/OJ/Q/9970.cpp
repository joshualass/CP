#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

/*

string problems are not for me

asymptotic behavior of 

3
PNPK
PNPKN
PNPKK

3
P
PN
PPK

3 4 - K P
3 5 - K N
4 5 - P N

bad idx - 8, 7

KNKPPKNKKNKPPKNKKNKPPKNKKNKPPKNKKNKPPKNK
KNKPPKNKPPKNKPPKNKPPKNKPPKNKPPKNKPPKNKPP
KNKPPKNKNKPPKNKNKPPKNKNKPPKNKNKPPKNKNKPPKN

KNKPPKNKKNKPPKNK
KNKPPKNKPP
KNKPPKNKNKPPKN

*/

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

int trie[1000001][3];
int cnts[1000001];
map<int,array<int,3>> _tm[1000001];
ll ttfang[1000001];
int p = 0;
ll res = 0;

map<char,int> m = {
    {'P', 0}, 
    {'K', 1},
    {'N', 2}
};

vi Z(const string & S) {
    vi z(sz(S));
    int l = -1, r = -1;
    rep(i, 1, sz(S)) {
        z[i] = i >= r ? 0 : min(r - i, z[i - 1]);
        while(i + z[i] < sz(S) && S[i + z[i]] == S[z[i]])
            z[i]++;
        if (i + z[i] > r)
            l = i, r = i + z[i];
    }
    return z;
}

int get_bad_idx(string &s, vector<int> &z, int plen) {

    assert(plen != s.size());

    int cur = plen; //stores next current check
    int res = plen; //stores total length of top of string

    for(int i = 0; i < 10; i++) {

        int nx = z[cur % s.size()];

        if(cur + nx == s.size()) { //complete match 
            res += nx;
            cur = nx;
        } else {
            return res + nx;
        }

    }

    return -1;

}

void insert(string s, vector<int> z) {

    int cur = 0;

    for(int i = 0; i < s.size(); i++) {
        
        int to = m[s[i]];
        if(trie[cur][to] == 0) {
            trie[cur][to] = ++p;
        }

        int c0 = (trie[cur][(to + 1) % 3] ? cnts[trie[cur][(to + 1) % 3]] : 0);
        int c1 = (trie[cur][(to + 2) % 3] ? cnts[trie[cur][(to + 2) % 3]] : 0);

        res += 1LL * c0 * c1; //add bad at here

        cur = trie[cur][to];

        cnts[cur]++;

        if(i + 1 < z.size()) { //if it is not cyclic after this 


            int bad_idx = get_bad_idx(s, z, i + 1);
            // cout << "s : " << s << '\n';
            // cout << "i : " << i + 1 << '\n';
            // cout << " bad idx : " << bad_idx << '\n';
            if(bad_idx == -1) continue;

            int bad_val = m[s[bad_idx % s.size()]];
            int good_val = m[s[bad_idx % (i + 1)]];

            // cout << "bad val : " << bad_val << '\n';

            for(int j = 0; j < 3; j++) {
                if(j != good_val && j != bad_val) {
                    ttfang[cur] += _tm[cur][bad_idx][j];
                }
            }

            _tm[cur][bad_idx][bad_val]++;

        }
    }

    res += ttfang[cur];

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n; cin >> n;
    vector<string> a(n);
    for(auto &x : a) cin >> x;

    sort(a.begin(), a.end(), [](const auto &lhs, const auto &rhs) {
        return lhs.size() < rhs.size();
    });

    for(int i = n - 1; i >= 0; i--) insert(a[i], Z(a[i]));

    cout << res << '\n';

    // ld res = 0;
    // for(int i = 1; i <= 60480; i++) res += 60480.0 / gcd(i, 60480);
    // cout << res << '\n';

    return 0;
}