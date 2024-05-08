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

void solve() {
    int n, m, d; cin >> n >> m >> d;
    vector<int> a(m);
    for(int &x : a) cin >> x;

    set<int> s(a.begin(), a.end());
    s.insert(1);
    s.insert(n+1);
    vector<int> v(s.begin(), s.end());

    int mincookies = 0;
    for(int i = 0; i < v.size() - 1; i++) {
        mincookies += 1 + (v[i+1] - v[i] - 1) / d;
    }

    a.push_back(n+1);
    // cout << "a : " << a << '\n';

    int decreases = 0;
    for(int i = 0; i < a.size() - 1; i++) {
        if(a[i] != 1) {
            int before;
            int total;
            if(i != 0) {
                before = 1 + (a[i] - a[i-1] - 1) / d;
                total = 1 + (a[i+1] - a[i-1] - 1) / d;
            } else {
                before = 1 + (a[i] - 1 - 1) / d;
                total = 1 + (a[i+1] - 1 - 1) / d;
            }
            int after = 1 + (a[i+1] - a[i] - 1) / d;
            // cout << "i : " << i << " b : " << before << " a : " << after << " t : " << total << '\n';
            if(total == before + after - 1) decreases++;
        }
    }
    if(decreases) {
        cout << mincookies - 1 << " " << decreases << '\n';
    } else {
        cout << mincookies << " " << m << '\n';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}