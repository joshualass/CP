#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

/*
First create prefix sums for each element
Next notice that after applying the operation is equivalent to swapping 2 elements in the prefix sums
Count number of swaps needed to make nondecreasing (if we have a decrease, then we have a negative value at that position)
Can't swap first or last elements, so need to make sure all elements in between those values
*/

/*
order_of_key (k) : Number of items strictly smaller than k .
find_by_order(k) : K-th element in a set (counting from zero).
*/
#include <ext/pb_ds/assoc_container.hpp> //0-indexed
#include <ext/pb_ds/tree_policy.hpp>
#include <functional>
using namespace __gnu_pbds;
template <class T>
using Tree =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<ll> pref(n+1);
    for(int i = 0; i < n; i++) {
        cin >> pref[i+1];
        pref[i+1] += pref[i];
    }

    if(*min_element(pref.begin() + 1, pref.end() - 1) < 0 || *max_element(pref.begin() + 1, pref.end() - 1) > pref[n]) {
        cout << "-1\n";
        return 0;
    }

    // cout << "prevs : " << pref << '\n';

    Tree<pair<ll,ll>> ms;
    ll ops = 0;
    for(int i = 0; i <= n; i++) {
        ll add = ms.size() - ms.order_of_key({pref[i],i});
        // cout << "i : " << i << " adding : " << add << '\n';
        ops += add;
        ms.insert({pref[i],i});
    }
    cout << ops << '\n';

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 1e9 + 7;

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
    
//     int n; cin >> n;
//     vector<ll> a(n);
//     for(ll &x : a) cin >> x;

//     priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>> pq;
//     for(int i = n - 2; i > 0; i--) {
//         if(a[i] < 0) {
//             // s.push(i);
//             pq.push({a[i],i});
//         }
//     }

//     int ops = 0;
//     while(pq.size() && ops < 1e6) {
//         // int i = s.top();
//         // s.pop();
//         auto [val, i] = pq.top();
//         pq.pop();
//         if(a[i] == val) {
//             if(a[i] < 0) {
//                 ops++;
//                 a[i-1] += a[i];
//                 a[i+1] += a[i];
//                 a[i] *= -1;
//                 if(i + 1 != n - 1 && a[i+1] < 0) pq.push({a[i+1],i+1});
//                 if(i - 1 != 0 && a[i-1] < 0) pq.push({a[i-1],i-1});
//             }
//         }
//     }

//     bool ok = 1;
//     for(int x : a) {
//         if(x < 0) ok = 0;
//     }

//     if(ok) {
//         cout << ops << '\n';
//     } else {
//         cout << "-1\n";
//     }

//     return 0;
// }