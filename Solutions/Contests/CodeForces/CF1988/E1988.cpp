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

vector<ll> bfchecker(vector<int> a) {
    vector<ll> res(a.size());
    for(int i = 0; i < a.size(); i++) {
        int t = a[i];
        a.erase(a.begin() + i, a.begin() + i + 1);
        for(int j = 0; j < a.size(); j++) {
            for(int k = j; k < a.size(); k++) {
                int lo = INT_MAX;
                for(int l = j; l <= k; l++) {
                    lo = min(lo, a[l]);
                }
                res[i] += lo;
            }
        }
        a.insert(a.begin() + i, t);
    }
    return res;
}

// vector<ll> solve(vector<int> a) {
//     int n = a.size();

void solve() {

    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    vector<vector<int>> minlefts(n);
    vector<vector<int>> minrights(n);
    stack<int> min1;
    stack<int> min2;

    for(int i = 0; i < n; i++) {
        while(min2.size() && a[i] < a[min2.top()]) {
            minrights[min2.top()].push_back(i);
            min2.pop();
        }
        vector<int> tomin2;
        while(min1.size() && a[i] < a[min1.top()]) {
            minrights[min1.top()].push_back(i);
            // min2.push(min1.top());
            tomin2.push_back(min1.top());
            min1.pop();
        }
        if(tomin2.size()) {
            for(int j = tomin2.size() - 1; j >= 0; j--) {
                min2.push(tomin2[j]);
            }
        }
        min1.push(i);
    }

    while(min1.size()) min1.pop();
    while(min2.size()) min2.pop();

    for(int i = n - 1; i >= 0; i--) {
        while(min2.size() && a[i] < a[min2.top()]) {
            minlefts[min2.top()].push_back(i);
            min2.pop();
        }
        vector<int> tomin2;
        while(min1.size() && a[i] < a[min1.top()]) {
            minlefts[min1.top()].push_back(i);
            // min2.push(min1.top());
            tomin2.push_back(min1.top());
            min1.pop();
        }
        if(tomin2.size()) {
            for(int j = tomin2.size() - 1; j >= 0; j--) {
                min2.push(tomin2[j]);
            }
        }
        min1.push(i);
    }

    vector<ll> p(n + 1);

    for(int i = 0; i < n; i++) {

        // p.assign(n+1, 0LL);

        int yl2 = (minlefts[i].size() >= 2 ? minlefts[i][1] : -1);
        int yl1 = (minlefts[i].size() >= 1 ? minlefts[i][0] : -1);
        int x = i;
        int yr1 = (minrights[i].size() >= 1 ? minrights[i][0] : n);
        int yr2 = (minrights[i].size() >= 2 ? minrights[i][1] : n);

        // cout << "i : " << i << " yl2 : " << yl2 << " yl1 : " << yl1 << " x : " << x << " yr1 : " << yr1 << " yr2 : " << yr2 << '\n';

        if(yl1 != -1) {
            ll addpreyl1 = 1LL * a[i] * (yr1 - x) * (x - yl1);
            p[0] += addpreyl1;
            p[yl1] -= addpreyl1;

            ll add = 1LL * a[i] * (yr1 - x) * (x - yl2 - 1);
            p[yl1] += add;
            p[yl1 + 1] -= add;
        }

        ll addyl1x = 1LL * a[i] * (yr1 - x) * (x - yl1 - 1);
        p[yl1 + 1] += addyl1x;
        p[x] -= addyl1x;

        ll addxyr1 = 1LL * a[i] * (yr1 - x - 1) * (x - yl1);
        p[x+1] += addxyr1;
        p[yr1] -= addxyr1;

        if(yr1 != n) {
            ll addpostyr1 = 1LL * a[i] * (yr1 - x) * (x - yl1);
            p[yr1 + 1] += addpostyr1;
            p[n] -= addpostyr1;

            ll add = 1LL * a[i] * (yr2 - x - 1) * (x - yl1);
            p[yr1] += add;
            p[yr1 + 1] -= add;
        }

        // cout << "i : " << i << " p : " << p << '\n';

    }

    ll cur = 0;
    // vector<ll> res(n);

    for(int i = 0; i < n; i++) {
        cur += p[i];
        cout << cur << " \n"[i == n - 1];
        // res[i] = cur;
    }
    // return res;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // int sz; cin >> sz;
    // vector<int> p(sz);
    // iota(p.begin(), p.end(), 1);

    // while(next_permutation(p.begin(), p.end())) {
    //     if(solve(p) != bfchecker(p)) {
    //         cout << "bad : " << p << '\n';
    //         cout << "from solve : " << solve(p) << '\n';
    //         cout << "from bfchecker : " << bfchecker(p) << '\n';
    //         return 0;
    //     }
    // }

    // cerr << "all g!\n";

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}

//not sure what I tried, but I knew it didn't work at the time. 

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 998244353;

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

// //range minimum query. O(1) query, O(n) build/memory. fast.
// template<typename T>
// struct RMQ  {
//     vector<T> elements;
//     int n;
//     static const int block_size = 30; // block size. adjust accordingly
//     vector<int> mask;
//     vector<int> sparse_table;
//     int op(int x, int y) { //update this method to determine what value we are trying to find. Currently set to minimum (return index of minimum element)
//         return elements[x] < elements[y] ? x : y;
//     }
//     int least_significant_bit(int x) {return x & -x;}
//     int most_significant_bit_index(int x) {return 31 - __builtin_clz(x);}
//     int small_query(int r, int size = block_size) {return r - most_significant_bit_index(mask[r] & ((1<<size)-1));}
//     RMQ() {} //need this to satisfy master goon's requirements
//     RMQ (const vector<T>& input) {build(input);}
//     void build (const vector<T>& input) {
//         elements = input;
//         n = input.size();
//         mask.assign(n,0);
//         sparse_table.assign(n,0);
//         int curr_mask = 0;
//         for(int i = 0; i < n; i++) {
//             curr_mask = (curr_mask<<1) & ((1<<block_size)-1);
//             while(curr_mask > 0 && op(i, i - most_significant_bit_index(least_significant_bit(curr_mask))) == i) curr_mask ^= least_significant_bit(curr_mask);
//             curr_mask |= 1;
//             mask[i] = curr_mask;
//         }
//         for(int i = 0; i < n/block_size; i++) sparse_table[i] = small_query(block_size * i + block_size - 1);
//         for(int j = 1; (1<<j) <= n/block_size; j++) for(int i = 0; i + (1<<j) <= n / block_size; i++) sparse_table[n / block_size * j + i] = op(sparse_table[n / block_size * (j - 1) + i], sparse_table[n / block_size * (j - 1) + i + (1<<(j-1))]);
//     }
//     T query(int l, int r) {//query(l,r) returns the element from the minimum of v[l..r] [l,r)
//         // r++;
//         if(r - l + 1 <= block_size) return elements[small_query(r, r - l + 1)];
//         int ans = op(small_query(l + block_size - 1), small_query(r)); 
//         int x = l / block_size + 1;
//         int y = r / block_size - 1;
//         if(x <= y) {
//             int j = most_significant_bit_index(y - x + 1);
//             ans = op(ans, op(sparse_table[n / block_size * j + x], sparse_table[n / block_size * j + y - (1 << j) + 1]));
//         }
//         return elements[ans]; //return the value
//         // return ans;        //return the index with value
//     }
// };

// /*
//         //search for the first index where a[idx] < a[i]
//         int lo = i + 1, hi = n;
//         while(lo != hi) {
//             int m = (lo + hi) / 2;
//             if(rmq.query(i+1,m) < a[i]) {
//                 hi = m;
//             } else {
//                 lo = m + 1;
//             }
//         }
//         r[i] = 1LL * a[i] * (lo - i);
//         if(lo < n) {
//             r[i] += r[lo];
//         }
        
// */

// void solve() {
//     int n; cin >> n;

//     vector<int> a(n);
//     for(int &x : a) cin >> x;

//     cout << "a : " << a << '\n';

//     vector<ll> rsegs(n + 1); //rsegs OP
//     vector<ll> r(n);     //right side perms
//     vector<int> nms(n,n); //index of next min
//     stack<array<ll,3>> s; // {val, idx, score}

//     for(int i = n - 1; i >= 0; i--) {
//         while(s.size() && a[i] < s.top()[0]) {
//             s.pop();
//         }
//         if(s.size()) {
//             rsegs[i] = a[i] * (s.top()[1] - i) + s.top()[2];
//             nms[i] = s.top()[1];
//         } else {
//             rsegs[i] = a[i] * (n - i);
//         }
//         s.push({a[i], i, rsegs[i]});
//         r[i] = rsegs[i] + (i != n - 1 ? r[i+1] : 0);
//     }

//     cout << "rsegs : " << rsegs << '\n';
//     cout << "r : " << r << '\n';
//     cout << "nms : " << nms << '\n';

//     ll cnt = 0;
//     ll cntchange = 0;
//     vector<ll> cntcntchange(n+1); //at each index 
//     vector<ll> souls(n + 1,1); //David Goggins always taking souls
//     vector<ll> rchange(n+1);
//     vector<ll> crosses(n+1);

//     for(int i = 0; i < n; i++) {
//         int nmidx = nms[i];
//         //handle subsegments where min comes from a[i]. First happens at index i. Last happens when _ is directly before nm
//         rchange[nmidx - 1] -= rsegs[nmidx] * souls[i];
//         cnt += rchange[i] + rsegs[nmidx] * souls[i];


//         //handle subsegments where min comes from next min



//         souls[nmidx] += souls[i];


//     }

// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }