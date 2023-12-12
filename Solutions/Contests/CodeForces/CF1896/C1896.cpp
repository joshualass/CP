#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << '(' << p.first << ", " << p.second << ") ";
    return os;
}

void solve() {
    int n, x; cin >> n >> x;

    vector<pair<int,int>> a(n);
    vector<int> b(n);
    
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        a[i] = {num,i};
    }
    for(int i = 0; i < n; i++) {
        cin >> b[i];
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    vector<int> ans(n);

    bool poss = 1;
    for(int i = 0; i < x; i++) {
        // cout << "> match : " << a[n-x+i] << " with : " << b[i] << '\n';
        ans[a[n-x+i].second] = b[i];
        if(a[n-x+i].first <= b[i]) poss = 0;
    }
    for(int i = x; i < n; i++) {
        // cout << "<= match : " << a[i-x] << " with : " << b[i] << '\n';
        ans[a[i-x].second] = b[i];
        if(a[i-x].first > b[i]) poss = 0;
    }
    if(poss) {
        cout << "YES\n";
        for(auto x : ans) cout << x << " ";
        cout << '\n';
    } else {
        cout << "NO\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}