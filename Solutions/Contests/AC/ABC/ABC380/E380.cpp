// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int n, q; cin >> n >> q;
//     vector<int> a(n), c(n);
//     set<int> s;
//     for(int i = 0; i < n; i++) {
//         a[i] = i;
//         c[i] = 1;
//         if(i != n - 1) {
//             s.insert(i);
//         }
//     }

//     auto color = [&](int idx, int color) -> void {
//         c[a[idx]]--;
//         a[idx] = color;
//         c[a[idx]]++;
//         if(idx && a[idx-1] == a[idx]) {
//             s.erase(idx - 1);
//         } else {
//             s.insert(idx - 1);
//         }
//         if(idx != n - 1 && a[idx] == a[idx+1]) {
//             s.erase(idx);
//         } else {
//             s.insert(idx);
//         }
//     };

//     for(int i = 0; i < q; i++) {
//         int type; cin >> type;
//         if(type == 1) {
//             int x, c; cin >> x >> c;
//             x--; c--;
//             set<int>::iterator rhs = s.lower_bound(x);
//             if(rhs != s.end()) {
//                 int idx = *rhs + 1;
//                 color(idx, a[x]);
//             }
//             set<int>::iterator lhs = s.lower_bound(x);
//             if(lhs != s.begin()) {
//                 int idx = *--lhs;
//                 color(idx, a[x]);
//             }
//         } else {
//             int C; cin >> C;
//             C--;
//             cout << c[C] << '\n';
//         }
//     }

//     return 0;
// }

#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const int N = 5e5;
int dsu[N];
int sizes[N];
int colors[N];
array<int,2> intervals[N];

int find(int x) {
    if(dsu[x] == x) {
        return x;
    }
    dsu[x] = find(dsu[x]);
    return dsu[x];
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if(x == y) {
        return;
    }
    dsu[y] = x;
    sizes[x] += sizes[y];
    intervals[x][0] = min(intervals[x][0], intervals[y][0]);
    intervals[x][1] = max(intervals[x][1], intervals[y][1]);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q; cin >> n >> q;
    vector<int> cnts(n);
    for(int i = 0; i < n; i++) {
        dsu[i] = i;
        sizes[i] = 1;
        colors[i] = i;
        intervals[i][0] = i;
        intervals[i][1] = i;
        cnts[i] = 1;
    }

    for(int i = 0; i < q; i++) {
        int type; cin >> type;
        if(type == 1) {
            int x, c; cin >> x >> c;
            x--; c--;
            x = find(x);
            int l = intervals[x][0], r = intervals[x][1];
            cnts[colors[x]] -= r - l + 1;
            colors[x] = c;
            cnts[colors[x]] += r - l + 1;
            if(l != 0 && colors[find(l - 1)] == c) {
                merge(find(l - 1), x);
            }
            if(r != n - 1 && colors[find(r + 1)] == c) {
                merge(find(r + 1), x);
            }
        } else {
            int c; cin >> c;
            c--;
            cout << cnts[c] << '\n';
        }
    }



    return 0;
}