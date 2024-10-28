#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int cr = 0, cc = 0;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<vector<T>> adj) {
    for(auto x : adj) {
        for(auto y : x) os << y << " ";
        os << "\n";
    }
    return os;
}

int worst_result(vector<vector<int>> &pos, int pr, int pc, int nr, int nc) {

    int lcnt = 0, scnt = 0, mcnt = 0;
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            if(pos[i][j]) {
                int d1 = (pr - i) * (pr - i) + (pc - j) * (pc - j);
                int d2 = (nr - i) * (nr - i) + (nc - j) * (nc - j);
                if(d1 < d2) {
                    lcnt++;
                } else if(d1 == d2) {
                    scnt++;
                } else {
                    mcnt++;
                }
            }
        }
    }

    return max({lcnt,scnt,mcnt});

}
//return worst row, col, max worst case
array<int,3> find_worst(vector<vector<int>> &pos, int pr, int pc) {
    int nr = 0, nc = 0, lomax = worst_result(pos, pr, pc, 0, 0);

    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            int t = worst_result(pos, pr, pc, i, j);
            if(t < lomax) {
                nr = i, nc = j, lomax = t;
            }
        }
    }
    return {nr, nc, lomax};
}

//-1 = Farther, 0, Closer, 1 gg
vector<vector<int>> updatepos(vector<vector<int>> pos, int pr, int pc, int nr, int nc, int verdict) {
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            int d1 = (pr - i) * (pr - i) + (pc - j) * (pc - j);
            int d2 = (nr - i) * (nr - i) + (nc - j) * (nc - j);
            if(d1 >= d2 && verdict == 1) {
                pos[i][j] = 0;
            } else if(d1 != d2 && verdict == 0) {
                pos[i][j] = 0;
            } else if(d1 <= d2 && verdict == -1) {
                pos[i][j] = 0;
            }
        }
    }
    return pos;
}

array<int,3> find_worst_n(vector<vector<int>> pos, int pr, int pc, int n) {

    if(n == 0) {
        int cnt = 0;
        for(int i = 0; i < 10; i++) {
            cnt += accumulate(pos[i].begin(), pos[i].end(), 0);
        }
        return {-1,-1,cnt};
    }
    
    int br = -1, bc = -1, brest = 99000;

    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            int a = find_worst_n(updatepos(pos, pr, pc, i, j, -1), i, j, n - 1)[2];
            int b = find_worst_n(updatepos(pos, pr, pc, i, j, 0), i, j, n - 1)[2];
            int c = find_worst_n(updatepos(pos, pr, pc, i, j, 1), i, j, n - 1)[2];

            int s = max({a,b,c});
            if(s < brest) {
                br = i, bc = j, brest = s;
            }
        }
    }
    return {br, bc, brest};
}


string get_result(vector<vector<int>> &pos, int pr, int pc, int nr, int nc) {
    int d1 = (pr-cr)*(pr-cr)+(pc-cc)*(pc-cc);
    int d2 = (nr-cr)*(nr-cr)+(nc-cc)*(nc-cc);
    if(d2 < d1) {
        return "Closer";
    } else if(d2 == d1) {
        return "Same";
    } else {
        return "Farther";
    }
}

void query_and_update(vector<vector<int>> &pos, int pr, int pc, int nr, int nc) {
    cout << nr << " " << nc << " ?" << endl;
    string res; cin >> res;
    // string res = get_result(pos, pr, pc, nr, nc);
    // cout << res << '\n';
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            int d1 = (pr - i) * (pr - i) + (pc - j) * (pc - j);
            int d2 = (nr - i) * (nr - i) + (nc - j) * (nc - j);
            if(d1 >= d2 && res == "Farther") {
                pos[i][j] = 0;
            } else if(d1 != d2 && res == "Same") {
                pos[i][j] = 0;
            } else if(d1 <= d2 && res == "Closer") {
                pos[i][j] = 0;
            }
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // cin >> cr >> cc;

    // int goodr = -1, goodc = -1;

    // for(int _pr = 0; _pr <= 5; _pr++) {
    //     for(int _pc = _pr; _pc <= 5; _pc++) {
    //         int ok = 1;
    //         for(cr = 0; cr < 10 && ok; cr++) {
    //             for(cc = 0; cc < 10 && ok; cc++) {

    //                 cout << "cr : " << cr << " cc : " << cc << endl;

    //                 vector<vector<int>> pos(10,vector<int>(10,1));
    //                 // cout << pr << " " << pc << " ." << endl;
    //                 int pr = _pr, pc = _pc;
    //                 // cout << "starting pos\n" << pos;

    //                 for(int i = 0; i < 6; i++) {
    //                     auto [nr, nc, banana] = find_worst_n(pos, pr, pc, 1);
    //                     query_and_update(pos, pr, pc, nr, nc);
    //                     pr = nr, pc = nc;
    //                     // cout << "after query pos\n" << pos;
    //                 }
    //                 int res = 0;
    //                 for(int i = 0; i < 10; i++) {
    //                     for(int j = 0; j < 10; j++) {
    //                         res += pos[i][j];
    //                     }
    //                 }

    //                 if(res != 1) {
    //                     ok = 0;
    //                     goto bad;
    //                 }

    //                 // for(int i = 0; i < 10; i++) {
    //                 //     for(int j = 0; j < 10; j++) {
    //                 //         if(pos[i][j]) {
    //                 //             cout << i << " " << j << " !" << endl;
    //                 //         }
    //                 //     }
    //                 // }

    //             }
    //         }
    //         bad:{}
    //         if(ok) {
    //             goodr = _pr, goodc = _pc;
    //             cout << goodr << " " << goodc << '\n';
    //             return 0;   
    //         }
    //         cout << "pr : " << _pr << " pc : " << _pc << endl;
    //     }
    // }


            // cout << "cr : " << cr << " cc : " << cc << endl;

    int pr = 1, pc = 3;
    vector<vector<int>> pos(10,vector<int>(10,1));
    cout << pr << " " << pc << " ." << endl;
    // cout << "starting pos\n" << pos;

    for(int i = 0; i < 6; i++) {
        auto [nr, nc, banana] = find_worst_n(pos, pr, pc, 1);
        query_and_update(pos, pr, pc, nr, nc);
        pr = nr, pc = nc;
        // cout << "after query pos\n" << pos;
    }
    int res = 0;
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            res += pos[i][j];
        }
    }

    // cerr << res << endl;


    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            if(pos[i][j]) {
                cout << i << " " << j << " !" << endl;
            }
        }
    }

    return 0;
}