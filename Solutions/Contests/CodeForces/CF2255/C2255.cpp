#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

vector<vector<int>> mat(vector<string> a) {
    
    int black = 0, white = 0;
    for(string s : a) {
        for(char c : s) {
            if(c == '#') {
                black++;
            } else {
                white++;
            }
        }
    }

    vector<vector<int>> res;

    for(string s : a) {
        res.push_back({});
        for(char c : s) {
            res.back().push_back(c == '#');
            if(black > white) res.back().back() ^= 1;
        }
    }

    return res;
}

//special calculated as (sum row pos / w) mod n
// {cur special row, cur special col, w, w^{-1}}}
array<int,4> get(int n, vector<vector<int>> mat) {
    int cnt = 0;

    array<int,4> cur = {};

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(mat[i][j]) {
                cnt++;
                cur[0] += i;
                cur[1] += j;
            }
        }
    }

    cur[0] %= n;
    cur[1] %= n;

    cur[2] = cnt % n;

    for(int i = 1; i < n; i++) {
        if(cnt * i % n == 1) {
            cur[3] = i;
        }
    }

    for(int i = 0; i < 2; i++) {
        cur[i] = (cur[i] * cur[3]) % n;
    }

    return cur;

}

void solve_first() {

    int n; cin >> n;
    vector<string> a(n);
    for(auto &x : a) cin >> x;
    auto b = mat(a);

    int r, c; cin >> r >> c;
    r--; c--;

    auto cur = get(n, b);

    array<int,2> shift = {(cur[0] - r + n) % n, (cur[1] - c + n) % n};
    for(int i = 0; i < 2; i++) shift[i] = (shift[i] * cur[2]) % n;

    array<int,2> first = {}, second = {};
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int ni = (i + shift[0]) % n;
            int nj = (j + shift[1]) % n;
            if(b[i][j] == 0 && b[ni][nj]) {
                first = {i, j};
                second = {ni, nj};
            }
        }
    }

    for(int x : first) cout << x + 1 << " ";
    for(int x : second) cout << x + 1 << " ";
    cout << '\n';

}

void solve_second() {

    int n; cin >> n;
    vector<string> a(n);
    for(auto &x : a) cin >> x;
    auto b = mat(a);
    auto cur = get(n, b);

    cout << cur[0] + 1 << " " << cur[1] + 1 << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string type; cin >> type;

    int casi; cin >> casi;
    while(casi-->0) {
        if(type == "first") solve_first();
        if(type == "second") solve_second();
    }

    return 0;
}

/*


first
1
5
#....
.#...
.....
.....
.....
3 4

second
1
5
.....
.#...
.....
.....
..#..

*/