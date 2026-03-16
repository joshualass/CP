#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef pair<int, int> pii;
typedef long double ld;

const int N = 12;
const int M = 30;
const int MAXP = 531441;
const int shift = 20;
const int MOD = (1 << 20) - 1;
const int bad = 676;

vi pow3(N + 1);

int gdpc[MAXP][N];
int sdpc[MAXP][N][3];


int get_dig(int val, int ind) {
    return (val / pow3[ind]) % 3;
}

int set_dig(int val, int ind, int dig) {
    return val + (dig - get_dig(val, ind)) * pow3[ind];
}

int dp[N][M + 1][MAXP];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    pow3[0] = 1;
    for(int i = 1; i < N + 1; i++) pow3[i] = (pow3[i - 1] * 3);

    for(int i = 0; i < MAXP; i++) {
        for(int j = 0; j < N; j++) {
            gdpc[i][j] = get_dig(i, j);
            for(int k = 0; k < 3; k++) {
                sdpc[i][j][k] = set_dig(i, j, k);
            }
        }
    }


    int n, m;
    cin >> n >> m;
    vector<string> g(n);
    // for(int i = 0; i < n; i++) g[i] = string(m, '.');
    for(int i = 0; i < n; i++) cin >> g[i];

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m + 1; j++) {
            for(int k = 0; k < pow3[n]; k++) {
                dp[i][j][k] = bad << shift;
            }
        }
    }

    dp[0][0][0] = 0;

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            int cr = j, cc = i;
            int nr = (j + 1) % n, nc = i + (j == n - 1);
            for(int k = 0; k < pow3[n]; k++) {
                int cur = dp[cr][cc][k] >> shift;
                if(cur == bad) continue;
                if(g[j][i] == '#') {
                    if(gdpc[k][j] != 2) {
                        int nx = sdpc[k][j][0];
                        if(((dp[nr][nc][nx] >> shift) == bad) || (dp[nr][nc][nx] >> shift) < cur) {
                            dp[nr][nc][nx] = (cur << shift) + k;
                        }
                    }
                } else {
                    //transition place a cooler
                    {
                        int nx = sdpc[k][j][1];
                        if(j && gdpc[k][j-1] == 2) {
                            nx = sdpc[nx][j-1][0];
                        }
                        if(((dp[nr][nc][nx] >> shift) == bad) || (dp[nr][nc][nx] >> shift) < cur) {
                            dp[nr][nc][nx] = (cur << shift) + k;
                        }
                    }
                    //transition place a reactor
                    {
                        int state = 2;
                        if(gdpc[k][j] == 1) state = 0;
                        if(j && gdpc[k][j-1] == 1) state = 0;
                        if(gdpc[k][j] != 2) {
                            int nx = sdpc[k][j][state];
                            cur++;
                            if(((dp[nr][nc][nx] >> shift) == bad) || (dp[nr][nc][nx] >> shift) < cur) {
                                dp[nr][nc][nx] = (cur << shift) + k;
                            }
                        }
                    }
                }
            }
        }
    }

    // cout << "mih 0" << endl;

    int res = -1, state = -1;
    for(int i = 0; i < pow3[n]; i++) {
        int ok = 1;
        for(int j = 0; j < n; j++) {
            if(gdpc[i][j] == 2) ok = 0;
        }
        int val = dp[0][m][i] >> shift;
        if(ok && val != bad && val > res) {
            res = val;
            state = i;
        }
    }

    // cout << "mih 1" << endl;
    // cout << "res : " << res << " state : " << state << endl;

    vector<string> board(n, string(m, '0'));
    int cr = 0, cc = m;
    while(cr || cc) {
        int nr = (cr - 1 + n) % n;
        int nc = (cr == 0 ? cc - 1 : nc);
        assert(state != -1);
        // cout << "cr : " << cr << " cc : " << cc << " nr : " << nr << " nc : " << nc << " state : " << state << endl;
        // board[nr][nc] = (g[nr][nc] == '#' ? '#' : gdpc[state][nr] + '0');
        char c = '\0';
        if(g[nr][nc] == '#') {
            c = '#';
        } else if(gdpc[state][nr] == 1) {
            c = '1';
        } else {
            c = '0';
        }
        board[nr][nc] = c;
        state = dp[cr][cc][state] & MOD;
        cr = nr;
        cc = nc;
    }

    // cout << "mih 2" << endl;

    for(auto x : board) cout << x << '\n';

    return 0;
}