#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

/*
this problem sort of uses a new bm technique i've never used before.

This problem kind of boils down to given a group of sets (can have a lot of these) whose elements are all from one set S, where |S| is small like 18-20,
What is the minimum number of elements selected from S such that each of the sets from the group of sets has at least one selected element?

We solve this with kind of an inductive approach. Also given that the all the sets from the group are not the empty set. 
Base case, we say it is always possible if we select every element from S. 
Inductive step, we say that if some bitmask bm is possible, then all the bitmasks where we add 1 unset bit is possible AND there is no set from group which is the opposite of the bm, then this bm is possible.

This takes 2^n * n to do. When we see if a bm is possible, we have to check all the bms that have exactly 1 more set bit that was previously unset are possible. 
*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    
    int n, c, k; cin >> n >> c >> k;

    string s; cin >> s;
    for(int i = 0; i < k - 1; i++) {
        s.push_back(s.back());
    }

    vector<int> cnts(c);
    vector<int> poss(1 << c);

    for(int i = 0; i < s.size(); i++) {
        cnts[s[i] - 'A']++;
        if(i - k >= 0) {
            cnts[s[i - k] - 'A']--;
        }
        int bm = 0;
        for(int j = 0; j < c; j++) {
            if(cnts[j]) {
                bm += 1 << j;
            }
        }
        if(i >= k - 1) {
            poss[bm] = 1;
        }
    }

    vector<int> ok(1 << c);
    ok[(1 << c) - 1] = 1;
    int res = c;

    for(int bm = (1 << c) - 2; bm >= 0; bm--) {

        int f = 1;
        for(int bit = 0; bit < c; bit++) {
            if((bm & (1 << bit)) == 0) {
                f &= ok[bm + (1 << bit)];
            }
        }

        f &= poss[((1 << c) - 1) ^ bm] ^ 1;
        ok[bm] = f;
        if(f) {
            res = min(res, (int) __builtin_popcount(bm));
        }

    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 998244353;

// //bitset too slow :( ?

// const int MAXN = 18;
// bitset<(1 << MAXN)> bs[MAXN];
// bitset<(1 << MAXN)> use[MAXN + 1];

// void dfs(int mask, vector<bool> &vis, int &res, int n, int c) {

//     vis[mask] = 1;
//     int sb = __builtin_popcount(mask);
//     if(use[sb].count() == n) {
//         res = min(res, sb);
//         return;
//     }

//     for(int i = 0; i < c; i++) {
//         if((mask & (1 << i)) == 0 && vis[mask | (1 << i)] == 0) {
//             use[sb + 1] = bs[i] | use[sb];
//             dfs(mask + (1 << i), vis, res, n, c);
//         }
//     }


// }

// void solve() {
//     int n, c, k; cin >> n >> c >> k;
//     string s; cin >> s;

//     for(int i = 0; i < c; i++) {
//         bs[i].reset();
//     }

//     for(int i = 0; i < n; i++) {
//         int c = s[i] - 'A';
//         for(int j = 0; j < k && i - j >= 0 && bs[c][i-j] == 0; j++) {
//             bs[c][i-j] = 1;
//         }
//     }

//     int mustusebit = s.back() - 'A';
//     int res = INT_MAX;
//     vector<bool> vis(1 << c);

//     use[1] = bs[mustusebit];
//     dfs(1 << mustusebit, vis, res, n, c);

//     cout << res << '\n';

// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }