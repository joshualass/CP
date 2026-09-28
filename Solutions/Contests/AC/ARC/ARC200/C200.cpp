#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n; cin >> n;
    vector<int> l(n), r(n);
    for(int i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
    }

    //dep means that all elements of dep[i] must be after the index of p_i. rdep is same but must be before. 
    vector<vector<int>> dep(n), rdep(n);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(l[i] < l[j] && r[j] < r[i]) {
                dep[j].push_back(i);
                rdep[i].push_back(j);
            }
        }
    }

    vector<int> res(n);

    auto dfs = [&](auto self, vector<int> a, int l, int r) -> void {
        if(l == r) return;

        while(count(a.begin(), a.end(), 1)) {

            int lo = -1;
            for(int i = 0; i < n; i++) {
                if(a[i]) {
                    lo = i;
                    break;
                }
            }

            vector<int> vis(n);
            queue<int> q;
            auto add_q = [&](int x) -> void {
                if(vis[x]) return;
                vis[x] = 1;
                q.push(x);
            };

            add_q(lo);

            vector<int> nxa(n);
            int nxsz = 0;

            while(q.size()) {
                int x = q.front();
                q.pop();
                if(a[x]) {
                    nxa[x] = 1;
                    a[x] = 0;
                    nxsz++;
                }
                for(int p : rdep[x]) add_q(p);
            }

            nxa[lo] = 0;

            res[lo] = l + nxsz - 1;
            self(self, nxa, l, l + nxsz - 1);

            l += nxsz;

        }

    };

    vector<int> a(n, 1);
    dfs(dfs, a, 0, n);

    for(int i = 0; i < n; i++) cout << res[i] + 1 << " \n"[i == n - 1];

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

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

// void solve() {
    
//     int n; cin >> n;
//     vector<int> l(n), r(n);
//     for(int i = 0; i < n; i++) {
//         cin >> l[i] >> r[i];
//     }

//     vector<vector<int>> deps(n);
//     vector<int> in(n);
//     for(int i = 0; i < n; i++) {
//         for(int j = 0; j < n; j++) {
//             if(l[i] < l[j] && l[j] < r[i] && r[i] < r[j]) {
//                 cout << "add dep from : " << j << " to : " << i << '\n';
//                 deps[j].push_back(i);
//                 in[i]++;
//             }
//         }
//     }

//     priority_queue<int, vector<int>, greater<int>> pq;
//     for(int i = 0; i < n; i++) {
//         if(in[i] == 0) {
//             pq.push(i);
//         }
//     }

//     vector<int> res(n);

//     int p = 0;
//     while(pq.size()) {
//         int i = pq.top();
//         pq.pop();
//         res[i] = p++;
//         cout << "i : " << i << '\n';
//         for(int x : deps[i]) {
//             cout << "dec x : " << x << '\n';
//             in[x]--;
//             cout << "pushing this x\n";
//             if(in[x] == 0) pq.push(x);
//         }
//     }

//     cout << "res : " << res << '\n';

//     // for(int i = 0; i < n; i++) {
//     //     cout << res[i] << " \n"[i == n - 1];
//     // }
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }