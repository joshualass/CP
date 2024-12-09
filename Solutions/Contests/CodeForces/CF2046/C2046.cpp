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
    int n; cin >> n;
    
    vector<array<int,2>> a(n);
    for(auto &x : a) cin >> x[0] >> x[1];
    
    sort(a.begin(), a.end());
    
    auto checkposs = [&](int cnt) -> array<int,2> {
        if(cnt == 0) return {0,0};
        Tree<array<int,2>> tl, tr;
        for(int i = 0; i < n; i++) {
            tr.insert({a[i][1], i});
        }
        
        for(int i = 0; i < n; i++) {
            tl.insert({a[i][1],i});
            tr.erase({a[i][1],i});
            while(i != n - 1 && a[i+1][0] == a[i][0]) {
                i++;
                tl.insert({a[i][1],i});
                tr.erase({a[i][1],i});
            }
            if(cnt * 2 > tl.size() || cnt * 2 > tr.size()) continue;
            int miny = max((*tl.find_by_order(cnt - 1))[0], (*tr.find_by_order(cnt - 1))[0]);
            if(tl.size() - tl.order_of_key({miny + 1, -1}) >= cnt && tr.size() - tr.order_of_key({miny + 1, -1}) >= cnt) {
                return {a[i][0], miny};
            }
        }
        
        return {INT_MAX,INT_MAX};
    };
    
    int l = 0, r = n / 4;
    while(l != r) {
        int m = (l + r + 1) / 2;
        array<int,2> pos = checkposs(m);
        if(pos[0] != INT_MAX) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    cout << l << '\n';
    array<int,2> res = checkposs(l);
    cout << res[0] + 1 << " " << res[1] + 1 << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}