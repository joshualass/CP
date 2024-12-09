#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

vector<int> lis(vector<int> &a) {

    // cout << "a : " << a << '\n';

    vector<int> liss(a.size(),-1);
    vector<int> res(a.size());

    for(int i = 0; i < a.size(); i++) {
        int l = -1, r = a.size() - 1;
        while(l != r) {
            int m = (l + r + 1) / 2;
            if(liss[m] == -1 || liss[m] >= a[i]) {
                r = m - 1;
            } else {
                l = m;
            }
        }
        // cout << "i : " << i << " l : " << l << '\n';
        liss[l+1] = a[i];
        res[i] = l + 2;
    }
    return res;
}

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    vector<int> flis = lis(a);
    reverse(a.begin(), a.end());
    vector<int> rlis = lis(a);
    reverse(flis.begin(),flis.end());
    // cout << "flis : " << flis << '\n';
    // cout << "rlis : " << rlis << '\n';
    int res = 0;
    for(int i = 0; i < n; i++) {
        if(flis[i] >= 2 && rlis[i] >= 2) {
            res = max(res, flis[i] + rlis[i] - 1);
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