#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const int MAXN = 2000;
const int MAXD = 11;

int sparseMin[MAXN][MAXD];
int sparseMax[MAXN][MAXD];
int rl[MAXN], rh[MAXN], cl[MAXN], ch[MAXN];

void buildMin() {
    for(int depth = 0; depth < MAXD; depth++) {
        for(int i = 0; i < MAXN; i++) {
            if(depth) {
                sparseMin[i][depth] = min(sparseMin[i][depth - 1], sparseMin[min(MAXN - 1, i + (1 << (depth - 1)))][depth - 1]);
            } else {
                sparseMin[i][depth] = rh[i];
            }
        }
    }
}
//[l,r) always. 
int queryMin(int l, int r) {
    int depth = 31 - __builtin_clz(r - l);
    return min(sparseMin[l][depth], sparseMin[max(l,r - (1 << depth))][depth]);
}

void buildMax() {
    for(int depth = 0; depth < MAXD; depth++) {
        for(int i = 0; i < MAXN; i++) {
            if(depth) {
                sparseMax[i][depth] = max(sparseMax[i][depth - 1], sparseMax[min(MAXN - 1, i + (1 << (depth - 1)))][depth - 1]);
            } else {
                sparseMax[i][depth] = rl[i];
            }
        }
    }
}

// [l, r) always.
int queryMax(int l, int r) {
    int depth = 31 - __builtin_clz(r - l);
    return max(sparseMax[l][depth], sparseMax[max(l, r - (1 << depth))][depth]);
}

const int N = 2e3;
int dsur[N][N];
array<int,2> br[N][N];
int dsuc[N][N];
array<int,2> bc[N][N];

void dsubuild() {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            dsur[i][j] = j;
            br[i][j] = {j,j};
            dsuc[i][j] = i;
            bc[i][j] = {i,i};
        }
    }
}

int findr(int x, int y) {
    if(dsur[x][y] == y) return y;
    dsur[x][y] = findr(x, dsur[x][y]);
    return dsur[x][y];
}

int findc(int x, int y) {
    if(dsuc[x][y] == x) return x;
    dsuc[x][y] = findc(dsuc[x][y], y);
    return dsuc[x][y];
}

void merger(int x, int y0, int y1) {
    y0 = findr(x,y0);
    y1 = findr(x,y1);
    if(y0 == y1) return;

    dsur[x][y1] = y0;
    br[x][y0][0] = min(br[x][y0][0], br[x][y1][0]);
    br[x][y0][1] = max(br[x][y0][1], br[x][y1][1]);
}

void mergec(int x0, int x1, int y) {
    x0 = findc(x0, y);
    x1 = findc(x1, y);
    if(x0 == x1) return;
    dsuc[x1][y] = x0;
    bc[x0][y][0] = min(bc[x0][y][0], bc[x1][y][0]);
    bc[x0][y][1] = max(bc[x0][y][1], bc[x1][y][1]);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    dsubuild();

    int n, m, k; cin >> n >> m >> k;
    vector<string> board(n);
    vector<vector<int>> p(n+1,vector<int>(m+1));

    for(int i = 0; i < n; i++) {
        cin >> board[i];
    }

    vector<array<int,2>> q(k);

    for(auto &x : q) {
        for(auto &y : x) {
            cin >> y;
            y--;
        }
        board[x[0]][x[1]] = 'X';
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            p[i+1][j+1] = p[i][j+1] + p[i+1][j] - p[i][j];
            if(board[i][j] == 'X') {
                p[i+1][j+1]++;
            }
        }
    }

    vector<int> res;

    //[l, r) inclusive exclusive query for each dim
    auto p_query = [&](int r0, int c0, int r1, int c1) -> int {
        return p[r1][c1] - p[r0][c1] - p[r1][c0] + p[r0][c0];
    };

    auto merge = [&](int i, int j) -> void {
        if(j + 1 < m && board[i][j] == '.' && board[i][j+1] == '.') {
            merger(i,j,j+1);
        }
        if(j > 0 && board[i][j] == '.' && board[i][j-1] == '.') {
            merger(i,j,j-1);
        }
        if(i + 1 < n && board[i][j] == '.' && board[i+1][j] == '.') {
            mergec(i,i+1,j);
        }
        if(i > 0 && board[i][j] == '.' && board[i-1][j] == '.') {
            mergec(i,i-1,j);
        }
    };

    int best = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            merge(i,j);
            while(1) {
                int mid = best + 1;
                if(i + mid <= n && j + mid <= m && p_query(i,j,i+mid,j+mid) == 0) {
                    best++;
                } else {
                    break;
                }
            }
        }
    }

    res.push_back(best);

    for(int i = k - 1; i >= 0; i--) {
        int x = q[i][0], y = q[i][1];
        board[x][y] = '.';
        merge(x,y);

        for(int j = 0; j < n; j++) {
            if(board[j][y] == 'X') {
                rh[j] = -1;
                rl[j] = m+1;
            } else {
                rh[j] = br[j][findr(j,y)][1];
                rl[j] = br[j][findr(j,y)][0];
            }
            rl[j]--;
            rh[j]++;
        }

        for(int j = 0; j < m; j++) {
            if(board[x][j] == 'X') {
                cl[j] = n+1;
            } else {
                cl[j] = bc[findc(x,j)][j][0];
            }
            cl[j]--;
        }

        buildMax();
        buildMin();

        while(1) {
            int mid = best + 1;
            int lc = y + 1,rc = y - 1;
            bool f = 0;

            for(int j = max(0, x - (mid - 1)); j <= x && j + mid <= n; j++) {
                while(lc - 1 >= 0 && cl[lc - 1] < j) lc--;
                while(rc + 1 < m && cl[rc + 1] < j) rc++;

                int qrl = max(queryMax(j, j + mid) + 1, lc);
                int qrh = min(queryMin(j, j + mid) - 1, rc);

                if(qrh - qrl + 1 >= mid) f = 1;
            }
            if(f) {
                best++;
            } else {
                break;
            }
        }
        res.push_back(best);
    }

    for(int i = k - 1; i >= 0; i--) {
        cout << res[i] << '\n';
    }

    return 0;
}   