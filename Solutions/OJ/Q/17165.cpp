/*
E. Four Sages Around an Oak Tree
*/

#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

/*
@@.@.....
@@.@.....
@@.@.....
..@...@.@
..@...@.@
..@...@.@
....@@.@.
....@@.@.
....@@.@.

@@.@..@@@
@@.@..@@@
@@.@@@...
..@@@@@.@
@@@...@.@
..@@@@@.@
....@@@@@
@@@.@@.@.
@@@.@@.@.

no good.


*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    os << '{';
    for(auto x : v) os << x << " ";
    os << '}';
    return os;
}

vector<vector<int>> sages = {
    {0, 1, 2, 2, 0, 1, 1, 2, 0},
    {2, 0, 1, 0, 1, 2, 1, 2, 0},
    {2, 1, 0, 0, 2, 1, 1, 0, 2},
    {2, 1, 0, 1, 0, 2, 0, 2, 1}
};

map<string, int> m = {
    {"red", 0},
    {"green", 1},
    {"blue", 2}
};

map<int, string> rm = {
    {0, "red"},
    {1, "green"},
    {2, "blue"}
};

string get_answer(int sage, string cl, string cr) {

    int l = m[cl], r = m[cr];
    int res = 0;

    if(sage == 1) {
        res = sages[0][r * 3 + l];
    }
    if(sage == 2) {
        res = sages[2][l * 3 + r];
    }
    if(sage == 3) {
        res = sages[1][l * 3 + r];
    }
    if(sage == 4) {
        res = sages[3][r * 3 + l];
    }

    return rm[res];
}

void solve_first() {
    string a, b, c, d; cin >> a >> b >> c >> d;
    int res;
    if(a == get_answer(1, d, b)) {
        res = 1;
    } else if(b == get_answer(2, a, c)) {
        res = 2;
    } else if(c == get_answer(3, b, d)) {
        res = 3;
    } else if(d == get_answer(4, c, a)) {
        res = 4;
    } else {
        assert(0);
    }
    cout << res << endl;
}

void solve_second() {
    int sage; cin >> sage;
    string cl, cr; cin >> cl >> cr;
    cout << get_answer(sage, cl, cr) << endl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t, s; cin >> t >> s;
    while(t-->0) {
        if(s == 1) solve_first();
        if(s == 2) solve_second();
    }

    // vector<vector<int>> sages(4, vector<int>(9, -1));

    // auto print = [&]() -> void {
    //     vector<vector<char>> grid(9, vector<char>(9, '.'));
    //     for(int i = 0; i < 9; i++) {
    //         for(int j = 0; j < 3; j++) {
    //             if(sages[0][i] != -1) {
    //                 grid[sages[0][i] * 3 + j][i] = '@';
    //             }
    //             if(sages[1][i] != -1) {
    //                 grid[sages[1][i] + j * 3][i] = '@';
    //             }
    //             if(sages[2][i] != -1) {
    //                 grid[i][sages[2][i] * 3 + j] = '@';
    //             }
    //             if(sages[3][i] != -1) {
    //                 grid[i][sages[3][i] + j * 3] = '@';
    //             }
    //         }
    //     }
    //     for(auto x : grid) {
    //         for(auto y : x) cout << y;
    //         cout << endl;
    //     }
    // };

    // print();

    // while(1) {
    //     int sage, i, j; cin >> sage >> i >> j;
    //     sages[sage][i] = j;
    //     cout << "sages : " << sages << '\n';
    //     print();
    // }



    return 0;
}
