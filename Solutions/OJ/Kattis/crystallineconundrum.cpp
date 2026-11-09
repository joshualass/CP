#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int r, c; cin >> r >> c;
    vector<string> a(r);
    for(auto &x : a) cin >> x;

    // vector<vector<int>> skip(r, vector<int>(c));
    // for(int i = 0; i < r; i++) {
    //     int start = 0;
    //     for(int j = 0; j < c; j++) {
    //         if(a[i][j] == '*') {
    //             if(start == 0) {
    //                 start = 1;
    //             } else {
    //                 skip[i][j-1] = 1;
    //             }
    //         } else {
    //             if(start) break;
    //         }
    //     }
    // }

    // for(int j = 0; j < c; j++) {
    //     int start = 0;
    //     for(int i = 0; i < r; i++) {
    //         if(a[i][j] == '*') {
    //             if(start == 0) {
    //                 start = 1;
    //             } else {
    //                 skip[i-1][j] = 1;
    //             }
    //         } else {
    //             if(start) break;
    //         }
    //     }
    // }

    vector<int> startc(c);

    for(int i = 0; i < r; i++) {
        int start = 0;
        for(int j = 0; j < c; j++) {
            if(a[i][j] == '*') {
                int removable = 0;
                if(i + 1 < r && a[i+1][j] == '*' && startc[j] == 0) {
                    removable = 1;
                }
                if(j + 1 < c && a[i][j+1] == '*' && start == 0) {
                    removable = 1;
                }
                if(removable) {
                    a[i][j] = '.';
                } else {
                    start = 1;
                    startc[j] = 1;
                }
            }
        }
    }

    int res = 0;
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            if(a[i][j] == '*') res ++;
        }
    }

    cout << res << '\n';

    return 0;
}
