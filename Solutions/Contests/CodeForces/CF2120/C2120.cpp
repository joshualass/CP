#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

#include <ext/pb_ds/assoc_container.hpp> //0-indexed
#include <ext/pb_ds/tree_policy.hpp>
#include <functional>
using namespace __gnu_pbds;
/*
order_of_key (k) : Number of items strictly smaller than k .
find_by_order(k) : K-th element in a set (counting from zero).
*/
template <class T>
using Tree =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

void solve() {
    
    ll n, m; cin >> n >> m;
    
    if(m < n || m > n * (n + 1) / 2) {
        cout << "-1\n";
        return;
    }

    Tree<int> os;
    for(int i = 0; i < n; i++) os.insert(i);
    
    m -= n;
    m = n * (n - 1) / 2 - m;
    
    // cout << "need decrease : " << m << '\n';
    
    vector<int> res(n);
    for(ll i = n - 1; i >= 0; i--) {
        int go = min(m, i);
        m -= go;
        int pos = *os.find_by_order(go);
        res[pos] = i;
        os.erase(pos);
    }
    
    cout << res[0] + 1 << '\n';
    for(int i = 1; i < n; i++) {
        cout << res[i-1] + 1 << " " << res[i] + 1 << '\n';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}