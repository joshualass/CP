#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

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
    
    int n; cin >> n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    
    ll res = 0;
    
    auto work = [&]() -> void {
        Tree<array<ll,2>> tree;
        ll sum = 0;
        for(int i = 0; i < sz(a); i += 2) {
            tree.insert({sum, i});
            sum += a[i];
            res += tree.order_of_key({sum, LLONG_MIN});
            if(i + 1 < sz(a)) {
                sum -= a[i+1];
            }
        }
    };
    
    work();
    // cout << "first work res : " << res << endl;
    a.erase(a.begin());
    work();
    // cout << "second work res : " << res << endl;
    
    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}