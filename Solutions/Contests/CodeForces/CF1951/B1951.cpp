#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

int countwins(vector<int> v, int idx) {
    int res = 0;
    int b = v[0];
    for(int i = 1; i < v.size(); i++) {
        b = max(b, v[i]);
        if(b == v[idx]) res++;
    }
    return res;
}

void solve() {
    int n, k; cin >> n >> k;
    k--;
    vector<int> v(n);
    for(int &x : v) cin >> x;

    int res = countwins(v,k);
    swap(v[0],v[k]);
    res = max(res, countwins(v,0));
    swap(v[0],v[k]);
    for(int i = 0; i < k; i++) {
        if(v[i] > v[k]) {
            swap(v[i], v[k]);
            res = max(res, countwins(v,i));
            swap(v[i], v[k]);
            break;
        }
    }
    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}