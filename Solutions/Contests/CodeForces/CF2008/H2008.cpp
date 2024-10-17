#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

// first tried and failed working on transitions between different mods. 
//However, it is best to consider them independently and use the fact that you are calculating the median of a mod.
// Try breaking into the blocks and binary searching the median. 

// int sim(vector<int> a, int x) {
//     for(int i = 0; i < a.size(); i++) {
//         while(a[i] >= x) a[i] -= x;
//     }
//     sort(a.begin(), a.end());
//     return a[a.size() / 2];
// }

// void solve() {
//     int n; cin >> n;
//     vector<int> a(n);
//     for(int &x : a) cin >> x;
//     for(int i = 1; i <= n; i++) {
//         cout << "i : " << i << " sim : " << sim(a,i) << '\n';
//     }
// }

int solvemed(vector<int> &cntless, int x) {

    int underneeded = (cntless.size() + 1) / 2;
    int l = 0, r = x - 1;
    while(l != r) {
        int m = (l + r) / 2;

        int tcl = 0;
        int i = 0;
        while(i < cntless.size()) {
            int prevcnt = 0;
            if(i) {
                prevcnt = cntless[i-1];
            }
            int nextless = cntless[min((int) cntless.size() - 1, i + m)];
            tcl += nextless - prevcnt;
            i += x;
        }

        if(tcl >= underneeded) {
            r = m;
        } else {
            l = m + 1;
        }
    }

    return l;

}

void solve() {
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    sort(a.begin(), a.end());
    vector<int> cntless(n+1);
    int lp = 0;
    for(int i = 0; i <= n; i++) {
        while(lp != n && a[lp] <= i) lp++;
        cntless[i] = lp;
    }

    vector<int> medians(n+1);
    for(int i = 1; i <= n; i++) {
        medians[i] = solvemed(cntless, i);
    }

    for(int i = 0; i < q; i++) {
        int x; cin >> x;
        cout << medians[x] << " \n"[i == q - 1];
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}