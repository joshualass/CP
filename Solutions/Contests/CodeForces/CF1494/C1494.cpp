#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

int solve1(vector<int> a, vector<int> b) {
    int on = 0;
    int lo = 0;
    for(int i = 0; i < b.size(); i++) {
        while(lo != a.size() && a[lo] < b[i]) lo++;
        if(lo != a.size() && a[lo] == b[i]) on++;
    }
    int res = on;

    int loon = 0;
    int los = -1;
    for(int i = 0; i < b.size(); i++) {
        // if(loon != a.size() && a[loon] < b[i]) loon++;
        while(loon != a.size() && a[loon] <= b[i]) {
            if(a[loon] == b[i]) on--;
            loon++;
        }
        while(los != b.size() - 1 && b[i] - b[los + 1] >= loon) los++;
        res = max(res, on + (i - los));
    }
    // cout << "res : " << res << '\n';
    return res;
}

void solve() {
    int n, m; cin >> n >> m;
    vector<int> a1;
    vector<int> a2;
    vector<int> b1;
    vector<int> b2;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        if(num > 0) {
            a1.push_back(num);
        } else {
            a2.push_back(-num);
        }
    }
    for(int i = 0; i < m; i++) {
        int num; cin >> num;
        if(num > 0) {
            b1.push_back(num);
        } else {
            b2.push_back(-num);
        }
    }
    reverse(a2.begin(), a2.end());
    reverse(b2.begin(), b2.end());
    cout << solve1(a1,b1) + solve1(a2,b2) << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}