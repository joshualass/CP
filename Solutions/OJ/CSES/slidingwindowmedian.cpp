#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k; cin >> n >> k;

    vector<int> a(n);
    for(int &x : a) cin >> x;

    Tree<array<int,2>> tree;
    for(int i = 0; i < k - 1; i++) {
        tree.insert({a[i],i});
    }

    for(int i = k - 1; i < n; i++) {
        tree.insert({a[i],i});
        if(i >= k) {
            tree.erase({a[i-k],i-k});
        }
        cout << (*tree.find_by_order((k - 1) / 2))[0] << " \n"[i == n - 1];
    }

    return 0;
}