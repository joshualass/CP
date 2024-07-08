#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

#include <ext/pb_ds/assoc_container.hpp> //0-indexed
#include <ext/pb_ds/tree_policy.hpp>
#include <functional>
using namespace __gnu_pbds;
template <class T>
using Tree =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

ll getInversions(vector<int> a) {

    Tree<pair<ll,ll>> ms;
    ll ops = 0;
    for(int i = 0; i < a.size(); i++) {
        ll add = ms.size() - ms.order_of_key({a[i],i});
        ops += add;
        ms.insert({a[i],i});
    }
    return ops;
}

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    set<int> sa;
    vector<int> b(n);
    set<int> sb;

    for(int i = 0; i < n; i++) {
        cin >> a[i];
        sa.insert(a[i]);
    }

    for(int i = 0 ; i < n; i++) {
        cin >> b[i];
        sb.insert(b[i]);
    }

    bool ok = 1;

    for(int x : sa) {
        if(sb.count(x) == 0) ok = 0;
    }

    if(getInversions(a) % 2 == getInversions(b) % 2 && ok) {
        cout << "YES\n";
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