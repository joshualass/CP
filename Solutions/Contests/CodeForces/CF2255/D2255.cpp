#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

/*
3
6 7 17
*/

/*
nice bijection / transformation that everyone sees, gg. difficult when you don't see ig. 
for the future, try to formalize things to make math transformations / observations. 
*/

bool check(vector<int> a, int skip) {
    for(int i = sz(a) + skip - 1; i >= 0; i--) {
        int idx = max_element(a.begin(), a.end()) - a.begin();
        a[idx] = max(0LL, a[idx] - (1LL << i));
    }
    return accumulate(a.begin(), a.end(), 0LL) == 0;
}

void solve() {
    
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    sort(a.begin(), a.end());

    for(int skip = 0; skip < 30; skip++) {
        vector<int> b(a.begin(), a.begin() + min(n, 30));
        if(check(b, skip)) {
            cout << n + skip << '\n';
            return;
        }
    }
    assert(0);
    // int ops = 0;
    // for(int i = 0; i < 30; i++) {
    //     int idx = -1;
    //     for(int j = 0; j < n; j++) {
    //         if((a[j] & 1) && (idx == -1 || a[j] < a[idx])) {
    //             idx = j;
    //         }
    //     }
    //     for(int j = 0; j < n; j++) {
    //         if(j == idx) {
    //             a[j] >>= 1;
    //         } else {
    //             a[j] = (a[j] + 1) / 2;
    //         }
    //     }
    //     ops++;
    //     if(count(a.begin(), a.end(), 0) == n) break;
    // }

    // assert(count(a.begin(), a.end(), 0) + count(a.begin(), a.end(), 1) == n);
    // cout << ops + accumulate(a.begin(), a.end(), 0) << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}