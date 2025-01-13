#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int MAX_DEPTH = 18;
const int MAX_N = 250000;

struct DoubleTrie {
    int dt[2];
    int ac[2];
    int cnt[2][2];
    int ec[2][2][MAX_DEPTH];
};

DoubleTrie t[MAX_N * MAX_DEPTH];
int p = 0;

void insert(int a, int b) {
    int cur = 0;
    for(int bit = MAX_DEPTH - 1; bit >= 0; bit--) {
        int dest = ((a & (1 << bit)) ^ (b & (1 << bit))) >> bit;
        if(t[cur].dt[dest] == 0) {
            t[cur].dt[dest] = ++p;
        }
        cur = t[cur].dt[dest];
        t[cur].ac[(a >> bit) & 1]++;
        t[cur].cnt[0][(a >> bit) & 1]++;
        t[cur].cnt[1][(b >> bit) & 1]++;
        for(int j = 0; j < MAX_DEPTH; j++) {
            t[cur].ec[0][(a >> bit) & 1][j] += (a >> j) & 1;
            t[cur].ec[1][(b >> bit) & 1][j] += (b >> j) & 1;
        }
    }
}

ll query(int a, int b) {
    int cur = 0;
    ll res = 0;
    for(int bit = MAX_DEPTH - 1; bit >= 0; bit--) {
        int abit = (a >> bit) & 1, bbit = (b >> bit) & 1;
        int dest = abit ^ bbit;
        if(t[cur].dt[dest ^ 1]) {
            int away = t[cur].dt[dest ^ 1];
            for(int j = bit; j >= 0; j--) {
                int cnta = t[away].ec[0][abit][j];
                int cntb = t[away].ec[1][bbit][j];
                if(((a >> j) & 1)) {
                    cnta = t[away].cnt[0][abit] - cnta;
                }
                if(((b >> j) & 1)) {
                    cntb = t[away].cnt[1][bbit] - cntb;
                }
                res += (1LL << j) * (cnta + cntb);
            }
        }
        cur = t[cur].dt[dest];
        res += (1LL << bit) * t[cur].ac[((a >> bit) & 1) ^ 1];
    }
    return res;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> a(n), b(n);
    for(int &x : a) cin >> x;
    for(int &x : b) cin >> x;
    
    ll res = 0;

    for(int i = 0; i < n; i++) {
        insert(a[i], b[i]);
        res += query(a[i], b[i]);
    }

    cout << res << '\n';

    return 0;
}