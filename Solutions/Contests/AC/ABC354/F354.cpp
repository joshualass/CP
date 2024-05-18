#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

vector<int> getLIS(vector<int> a) {
    int n = a.size();
    vector<int> lis(n,INT_MAX);
    vector<int> res(n);
    for(int i = 0; i < n; i++) {

        int l = -1, r = n - 2;
        while(l != r) {
            int m = (l + r + 1) / 2;
            if(a[i] > lis[m]) {
                l = m;
            } else {
                r = m - 1;
            }
        }

        res[i] = l + 1;
        lis[l+1] = a[i];

    }

    // cout << "a : " << a << '\n';
    // cout << "lis : " << lis << '\n';
    // cout << "res : " << res << '\n';

    return res;
}

void solve() {
    int n; cin >> n;

    vector<int> a(n);
    for(int &x : a) cin >> x;

    vector<int> lis1 = getLIS(a);
    reverse(a.begin(), a.end());
    for(int i = 0; i < n; i++) a[i] *= -1;
    vector<int> lis2 = getLIS(a);
    reverse(lis2.begin(), lis2.end());

    int hi = 0;
    for(int i = 0; i < n; i++) {
        hi = max(hi, lis1[i] + lis2[i]);
    }

    vector<int> res;
    for(int i = 0; i < n; i++) {
        if(lis1[i] + lis2[i] == hi) {
            res.push_back(i+1);
        }
    }

    cout << res.size() << '\n';
    for(int i = 0; i < res.size(); i++) {
        cout << res[i] << " \n"[i == res.size() - 1];
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}