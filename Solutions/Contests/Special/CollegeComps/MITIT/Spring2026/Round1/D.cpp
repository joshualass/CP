#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

/*
had to be a little careful with memory for this impl ... 
another case of MLEing
problems seems quite hard
then i artificially tell myself to use a trie for these types of problems and then the solution is obvious
*/

const int MN = 4e5 + 5;
const int MD = 60;
int depth;
int trie[MN * MD][2], cnts[MN * MD], utility[MN * MD];
int p = 0;

void reset() {
    for(int i = 0; i <= p; i++) {
        trie[i][0] = 0;
        trie[i][1] = 0;
        cnts[i] = 0;
        utility[i] = 0;
    }
    p = 0;
}

void update(ll val, int cur, int cur_depth, int delta) {
    cnts[cur] += delta;
    if(cur_depth == depth) {
        if(cnts[cur]) {
            utility[cur] = -1e9;
        } else {
            utility[cur] = 0;
        }
        return;
    }
    int ch = (val >> cur_depth) & 1LL;
    if(trie[cur][ch] == 0) {
        trie[cur][ch] = ++p;
    }
    update(val, trie[cur][ch], cur_depth + 1, delta);
    // if(trie[cur][ch ^ 1] == 0) {
    //     trie[cur][ch ^ 1] = ++p;
    // }
    // cout << "update val : " << val << " cur : " << cur << " cur_depth : " << cur_depth << " delta : " << delta << endl;
    // cout << "cnts here : " << cnts[cur] << " left util : " << utility[trie[cur][0]] << " right utility : " << utility[trie[cur][1]] << endl;
    utility[cur] = cnts[cur] + max(trie[cur][0] ? utility[trie[cur][0]] : 0LL, trie[cur][1] ? utility[trie[cur][1]] : 0LL);
}

int query() {
    return utility[0];
}

void solve() {
    
    reset();

    int n, q; cin >> n >> q >> depth;
    vector<ll> a(n);
    for(int i = 0; i < n; i++) {
        ll x; cin >> x;
        a[i] = x;
        update(x, 0, 0, 1);
    }

    cout << query() - n << '\n';
    for(int qq = 0; qq < q; qq++) {
        ll i, v; cin >> i >> v;
        i--;
        update(a[i], 0, 0, -1);
        a[i] = v;
        update(a[i], 0, 0, 1);
        cout << query() - n << '\n';
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}