#include <bits/stdc++.h>
typedef long long ll;
typedef __int128_t lll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

#include <ext/pb_ds/assoc_container.hpp> //0-indexed
#include <ext/pb_ds/tree_policy.hpp>
#include <functional>
#include <ext/pb_ds/detail/standard_policies.hpp>
using namespace __gnu_pbds;
 
typedef tree<
pair<int, int>,
null_type,
less<pair<int, int>>,
rb_tree_tag,
tree_order_statistics_node_update> ordered_set;

void solve() {
    int n, m; cin >> n >> m;

    ordered_set a;
    int t = 0;
    vector<int> b(n);
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        a.insert({num,t++});
    }
    for(auto &x: b) cin >> x;
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());

    ll total_ops = 0;
    ll curr_ops = 0;

    int curr_m = 0;

    set<int> m_order;
    for(auto x : b) {
        if(x != 1) {
            m_order.insert(min(m,x-1));
        }
    }

    m_order.insert(m);
    a.insert({0,t++});

    int aptr = 0;
    int bptr = 0;
    for(auto m_value: m_order) {
        // a.erase(curr_m);
        a.erase(a.lower_bound({curr_m,0}));
        // a.insert(m_value);
        a.insert({m_value,t++});
        int aval = (*a.find_by_order(aptr)).first;
        int bval = b[aval + curr_ops];
        while(n - curr_ops > aptr && aval >= bval) {
            curr_ops++;
            bval = b[aval + curr_ops];
        }
        total_ops += (m_value - curr_m) * curr_ops;
        curr_m = m_value;
    }
    cout << total_ops << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}