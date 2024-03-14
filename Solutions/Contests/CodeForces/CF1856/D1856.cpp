#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

int ask(int l, int r) {
    cout << "? " << l + 1 << " " << r + 1 << endl;
    int res; cin >> res;
    return res;
}

void solve() {
    int n; cin >> n;
    set<int> cand;
    for(int i = 0; i < n; i++) {
        cand.insert(i);
    }
    while(cand.size() > 1) {
        set<int> upd;
        if(cand.size() & 1) {
            upd.insert(*cand.begin());
            cand.erase(cand.begin());
        }
        while(cand.size()) {
            int l = *cand.begin();
            cand.erase(cand.begin());
            int r = *cand.begin();
            cand.erase(cand.begin());
            if(r - l == 1) {
                int res = ask(l,r);
                if(res == 1) {
                    upd.insert(l);
                } else {
                    upd.insert(r);
                }
            } else {
                int res1 = ask(l,r-1);
                int res2 = ask(l,r);
                if(res1 == res2) {
                    upd.insert(r);
                } else {
                    upd.insert(l);
                }
            }
        }
        swap(upd,cand);
    }
    cout << "! " << *cand.begin() + 1 << endl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}