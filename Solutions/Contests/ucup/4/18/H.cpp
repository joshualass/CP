/*
The 4th Universal Cup. Stage 18: Grand Prix of Hongō
H. Heyawake-like Problem
*/
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

/*
For a fixed N, there are (3N + 1) * N + 2 black cells needed - N in each row + 2 extra somewhere!

N = 2
#..#..#
.#...#.
..#.#..
#.....#
..#.#..
.#...#.
#..#..#

.#..#..#..
...#..#..#
#...#...#.
..#..#.#..
.#.#.....#
#.....#.#.
..#.#..#..
.#...#...#
#..#..#...
..#..#..#.

.#..#..#..
.........#
#.........
..........
.........#
#.........
..........
.........#
#.........
..#..#..#.

*/

typedef pair<int, int> pii;
bool is_valid(int n, vector<string>& res) {
    if(res.size() != 3 * n + 1) return false;
    for(int i = 0; i < res.size(); i++) {
        if(res[i].size() != 3 * n + 1) return false;
    }
    int on = n;
    n = 3 * n + 1;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(res[i][j] != '#' && res[i][j] != '.') return false;
        }
    }

    // cout << "PRELIMINARY CHECKS GOOD" << endl;

    {
        int rncnt = 0, rn1cnt = 0;
        int cncnt = 0, cn1cnt = 0;
        for(int i = 0; i < n; i++) {
            int rcnt = 0, ccnt = 0;
            for(int j = 0; j < n; j++) {
                if(res[i][j] == '#') rcnt ++;
                if(res[j][i] == '#') ccnt ++;
            }
            
            if(rcnt == on) rncnt ++;
            else if(rcnt == on + 1) rn1cnt ++;
            else {
                // cout << "BAD COUNT ROW : " << i << " " << rcnt << " " << on << "\n";
            }

            if(ccnt == on) cncnt ++;
            else if(ccnt == on + 1) cn1cnt ++;
            else {
                // cout << "BAD COUNT COL : " << i << " " << ccnt << " " << on << "\n";
            }
        }   
        if(rncnt != n - 2) return 0;
        if(cncnt != n - 2) return 0;
        if(rn1cnt != 2) return 0;
        if(cn1cnt != 2) return 0;
    }
    // cout << "COUNTS GOOD" << endl;

    {
        vector<int> dr = {-1, 1, 0, 0};
        vector<int> dc = {0, 0, -1, 1};
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(res[i][j] != '#') continue;
                for(int k = 0; k < 4; k++) {
                    int nr = i + dr[k];
                    int nc = j + dc[k];
                    if(nr < 0 || nc < 0 || nr >= n || nc >= n) continue;
                    if(res[nr][nc] == '#') return 0;
                }
            }
        }
    }
    // cout << "BLACK SIDE DISCONNECTED" << endl;

    {
        vector<int> dr = {-1, 1, 0, 0};
        vector<int> dc = {0, 0, -1, 1};
        vector<vector<int>> v(n, vector<int>(n, 0));
        queue<pii> q;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(res[i][j] != '.') continue;  
                if(!q.size()) {
                    q.push({i, j});
                    v[i][j] = 1;
                }
            }
        }
        while(q.size()) {
            int r = q.front().first;
            int c = q.front().second;
            q.pop();
            for(int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                if(nr < 0 || nc < 0 || nr >= n || nc >= n) continue;
                if(v[nr][nc]) continue;
                if(res[nr][nc] != '.') continue;
                v[nr][nc] = 1;
                q.push({nr, nc});
            }
        }
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(res[i][j] != '.') continue;
                if(!v[i][j]) return 0;
            }
        }
    }
    // cout << "WHITE CONNECTED" << endl;

    {
        vector<int> dr = {-1, -1, 1, 1};
        vector<int> dc = {-1, 1, -1, 1};
        vector<vector<int>> v(n, vector<int>(n, 0));
        queue<pii> q;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(res[i][j] != '#') continue;  
                if(i != 0 && j != 0 && i != n - 1 && j != n - 1) continue;
                q.push({i, j});
                v[i][j] = 1;
            }
        }
        while(q.size()) {
            int r = q.front().first;
            int c = q.front().second;
            q.pop();
            for(int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                if(nr < 0 || nc < 0 || nr >= n || nc >= n) continue;
                if(v[nr][nc]) continue;
                if(res[nr][nc] != '#') continue;
                v[nr][nc] = 1;
                q.push({nr, nc});
            }
        }
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(res[i][j] != '#') continue;
                if(!v[i][j]) return 0;
            }
        }
    }
    // cout << "BLACK CONNECTED" << endl;

    return 1;
}

vector<string> solve(int n, vector<int> even, vector<int> odd) {

    if(n == 1) {
        // cout << "No\n";
        return {};
    }

    int len = n * 3 + 1;

    vector<string> res(len, string(len, '.'));

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 3; j++) {
            res[j][j] = '#';
        }   
        res[0][len - 4] = '#';
        for(int sc = 3; sc < len - 4; sc += 3) {
            int c = sc;
            for(int row = 0; ; row++) {
                res[row][c] = '#';
                if(i % 2 == 0) {
                    if(row >= sz(even)) break;
                    c += even[row] * 2 - 1;
                } else {
                    if(row >= sz(odd)) break;
                    c += odd[row] * 2 - 1;
                }
                int gt = row + 1, lt = len - 2 - row;
                if(!(c > gt && c < lt)) break;
            }
        }

        vector<string> nr(len, string(len, '.'));
        for(int j = 0; j < len; j++) {
            for(int k = 0; k < len; k++) {
                nr[j][k] = res[len - k - 1][j];
            }
        }
        res = nr;
    }

    // cout << "Yes\n";
    // cout << "n : " << n << endl;
    // for(int i = 0; i < len; i++) cout << res[i] << '\n';
    return res;

}

/*
1 1 -1 1 1 1 -1 -1 -1 -1 -1 
1 1 -1 -1 -1 -1 1 1 1 1 1 
*/

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<int> even = {
        1, 1, 0, 1, 1, 1, 0, 0, 0, 0
    }, odd = {
        1, 1, 0, 0, 0, 0, 1, 1, 1, 1
    };

    for(int i = 0; i < 1500; i++) {
        even.push_back(0);
        odd.push_back(1);
    }

    int n; cin >> n;

    if(n == 1) {
        cout << "No\n";
        return 0;
    }

    auto res = solve(n, even, odd);
    cout << "Yes\n";
    for(int i = 0; i < sz(res); i++) cout << res[i] << '\n';


    // int len = n * 3 + 1;

    // vector<string> res(len, string(len, '.'));

    // for(int i = 0; i < 4; i++) {
    //     for(int j = 0; j < 3; j++) {
    //         res[j][j] = '#';
    //     }   
    //     res[0][len - 4] = '#';
    //     for(int sc = 3; sc < len - 4; sc += 3) {
    //         int c = sc;
    //         for(int row = 0; ; row++) {
    //             res[row][c] = '#';
    //             if(i % 2 == 0) {
    //                 if(row >= sz(even)) break;
    //                 c += even[row];
    //             } else {
    //                 if(row >= sz(odd)) break;
    //                 c += odd[row];
    //             }
    //             int gt = row + 1, lt = len - 2 - row;
    //             if(!(c > gt && c < lt)) break;
    //         }
    //     }

    //     vector<string> nr(len, string(len, '.'));
    //     for(int j = 0; j < len; j++) {
    //         for(int k = 0; k < len; k++) {
    //             nr[j][k] = res[len - k - 1][j];
    //         }
    //     }
    //     res = nr;
    // }

    // cout << "Yes\n";
    // for(int i = 0; i < len; i++) cout << res[i] << '\n';

    // for(int n = 1; n <= 100; n++) {
    //     auto res = solve(n, even, odd);
    //     // for(int i = 0; i < sz(res); i++) cout << res[i] << '\n';
    //     if(n == 1) {
    //         assert(res.empty());
    //     } else {
    //         int len = n * 3 + 1;
    //         if(is_valid(n, res)) {
    //             cout << "even odd works for n : " << n << endl;
    //         } else {
    //             cout << "bad n : " << n << endl;
    //         }
    //     }
    // }

    // int add_len = 7;

    // for(int n = 9; n <= 9; n++) {
    //     for(int j = 0; j < 1 << add_len; j++) {
    //         for(int k = 0; k < 1 << add_len; k++) {
    //             auto ce = even, co = odd;
    //             for(int l = 0; l < add_len; l++) ce.push_back((j >> l) & 1);
    //             for(int l = 0; l < add_len; l++) co.push_back((k >> l) & 1);
                
    //             vector<int> e1(n * 3 + 1), e2(n * 3 + 1), o1(n * 3 + 1), o2(n * 3 + 1);

    //             int upe = 0, downe = 0, upo = 0, downo = 0;
    //             int ok = 1;
    //             for(int i = 0; i < sz(ce); i++) {
    //                 if(ce[i] == 1) upe++;
    //                 if(ce[i] == -1) downe++;
    //                 if(co[i] == 1) upo++;
    //                 if(co[i] == -1) downo++;
    //                 if(upe % 3 == 1 && upe >= 4) e1[i] = 1;
    //                 if(downe % 3 == 1) e2[i] = 1;
    //                 if(upo % 3 == 1 && upo >= 4) o1[i] = 1;
    //                 if(downo % 3 == 1) o2[i] = 1; 
    //                 if(e1[i] && o2[i]) ok = 0;
    //                 if(e2[i] && o1[i]) ok = 0;
    //             }   

    //             if(!ok) continue;

    //             auto res = solve(n, ce, co);
    //             // for(int i = 0; i < sz(res); i++) cout << res[i] << '\n';
    //             if(n == 1) {
    //                 assert(res.empty());
    //             } else {
    //                 map<int,int> rc, cc;
    //                 for(int j = 0; j < sz(res); j++) {
    //                     int cnt = 0;
    //                     for(int k = 0; k < sz(res[j]); k++) {
    //                         cnt += res[j][k] == '#';
    //                     }
    //                     // cout << "row i : " << j << " has cnt : " << cnt << endl;
    //                     rc[cnt]++;
    //                 }
    //                 for(int j = 0; j < sz(res); j++) {
    //                     int cnt = 0;
    //                     for(int k = 0; k < sz(res[j]); k++) {
    //                         cnt += res[k][j] == '#';
    //                     }
    //                     // cout << "col i : " << j << " has cnt : " << cnt << endl;
    //                     cc[cnt]++;
    //                 }
    //                 int len = n * 3 + 1;

    //                 // if(rc[n] == len - 2 && rc[n+1] == 2 && cc[n] == len - 2 && cc[n+1] == 2) {
    //                 if(is_valid(n, res)) {
    //                     cout << "good even : " << ce << endl;
    //                     cout << "good odd : " << co << endl;
    //                     cout << "e1 : " << e1 << endl;
    //                     cout << "e2 : " << e2 << endl;
    //                     cout << "o1 : " << o1 << endl;
    //                     cout << "o2 : " << o2 << endl;
    //                     for(int i = 0; i < sz(res); i++) cout << res[i] << '\n';
    //                     return 0;
    //                 }
    //                 // assert(rc[n] == len - 2 && rc[n+1] == 2);
    //                 // assert(cc[n] == len - 2 && cc[n+1] == 2);
    //                 // cout << "n : " << n << " ok!" << endl;

    //         }
    //     }

    //     }
    // }
    
    return 0;
}
