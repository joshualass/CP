#include <bits/stdc++.h>
typedef long long ll;
// typedef __int128 lll;
typedef long double ld;
// typedef __float1238 lld;
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;

const int MAXN = 1000;
bitset<MAXN> g;
bitset<MAXN> ab;
bitset<MAXN> ssleft;
vector<bitset<MAXN>> bss(MAXN);
vector<bitset<MAXN>> toggled(MAXN);

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    g.reset();
    ab.reset();
    for(int i = 0; i < MAXN; i++) {
        bss[i].reset();
    }

    int n, m; cin >> n >> m;
    vector<array<vector<int>,2>> mem(m);

    for(int i = 0; i < m; i++) {
        int x; cin >> x;
        set<int> s;
        for(int j = 0; j < x; j++) {
            int y; cin >> y;
            y--;
            s.insert(y);
        }
        vector<int> a(s.begin(),s.end());
        vector<int> b;
        for(int j = 0; j < n; j++) {
            if(s.count(j) == 0) {
                b.push_back(j);
            }
        }
        if(b.size() < a.size()) swap(a,b);
        mem[i] = {a,b};
    }

    int ok = 1;
    int largest = -1;
    set<int> small_set;

    for(int i = 0; i < m; i++) {
        if(i == 0 || mem[i][0].size() < mem[largest][0].size()) {
            largest = i;
            small_set.clear();
            for(int s : mem[i][0]) {
                small_set.insert(s);
            }
        }
    }

    for(int i = 0; i < m; i++) {
        int hassmall = 0;
        for(int x : mem[i][0]) {
            if(small_set.count(x)) {
                hassmall = 1;
                break;
            }
        }
        if(!hassmall) {
            swap(mem[i][0],mem[i][1]);
        }
    }

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            toggled[i][j] = 1;
        }
        for(int x : mem[i][1]) {
            bss[i][x] = 1;
            toggled[i][x] = 0;
        }
        if(i == largest) {
            for(int x : mem[i][0]) {
                g[x] = 1;
            }
        }
    }

    // cout << "largest : " << largest << '\n';

    for(int i = 0; i < m; i++) {
        ab = g & bss[i];
        ssleft = bss[i];
        if(ab.count()) {
            // cout << "not ok subset i : " << i << "\n";
            ok = 0;
        }
        for(int j = 0; j < m; j++) {
            ab = bss[i] & bss[j];
            int cnt = ab.count();
            if(cnt && (cnt < min(mem[i][1].size(), mem[j][1].size()))) {
                // cout << "not ok intersect i : " << i << " j : " << j << "\n";
                ok = 0;
            }
            if(bss[i] != bss[j]) {
                if((bss[i] | bss[j]) == bss[i]) {
                    ssleft &= toggled[j];
                }
            }
        }
        if(ssleft.count() == 0) {
            // cout << "not ok 3 i : " << i << '\n';
            ok = 0;
        }
    }

    cout << ok << '\n';

    return 0;
}