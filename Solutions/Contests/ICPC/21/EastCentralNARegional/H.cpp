#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<bool> vb;
typedef vector<vector<bool>> vvb;
const ll MOD = 1e9 + 7;
vi dr = {-1, 1, 0, 0};
vi dc = {0, 0, -1, 1};

int n, m;
vector<string> g;
bool is_dig(char c) {
    return '1' <= c && c <= '9';
}

bool check_valid(int r, int c, char d) {
    if(r != 0 && is_dig(g[r - 1][c]) && g[r - 1][c] > d) {
        return false;
    }
    if(c != 0 && is_dig(g[r][c - 1]) && g[r][c - 1] > d){

    }
}

int test_spos(int r, int c, vi& a, vector<vvi>& s) {
    if('1' <= g[r][c] && g[r][c] <= '9'){
        return 0;
    }
    int ans = 0;
    for(int i = 0; i < (1 << a.size()); i++){
        vi mv(0);
        for(int j = 0; j < a.size(); j++){
            if(i & (1 << j)) {
                mv.push_back(a[j]);
            }
        }
        //horizontal
        {
            int ptr = c;
            int score = 0;
            bool valid = true;
            for(int j = 0; j < mv.size(); j++){
                while(ptr != m && is_dig(g[r][ptr])) {
                    score += g[r][ptr] - '0';
                    ptr ++;
                }
                if(ptr == m){
                    valid = false;
                    break;
                }
                for(int k = 0; k < 4; k++){
                    int nr = r + dr[k];
                    int nc = ptr + dc[k];
                    if(nr < 0 || nc < 0 || nr >= n || nc >= m){
                        continue;
                    }

                }
            }
        }
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    g = vector<string>(n, string(m, ' '));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            string tmp;
            cin >> tmp;
            g[i][j] = tmp[0];
        }
    }
    int t;
    cin >> t;
    vector<int> a(t);
    for(int i = 0; i < t; i++){
        cin >> a[i];
    }
    //precompute for all 4 directions, the score of contiguous tiles
    //and whether it's the start of an increasing or decreasing sequence
    vector<vvi> s(2, vvi(n, vi(m, 0))); //{horiz, vert}
    vector<vvi> sok(2, vvi(n, vi(m, 0)));   //-1 is minimum, 1 is max. 2 is all same
    for(int i = 0; i < n; i++){
        int r = 0;
        for(int j = 0; j < m;){
            if(!is_dig(g[i][j])) {
                continue;
            }
            int sum = 0;
            while(r != n && is_dig(g[i][r])) {
                sum += g[i][r] - '0';
                r ++;
            }
            s[0][i][j] = sum;
            s[0][i][r - 1] = sum;
            if(g[i][j] > g[i][r - 1]){
                s[0][i][j] = -1;
            }
            else if(g[i][j] < g[i][r - 1]){

            }
            else {
                s[0][i][j] = 2;
                s[0][i][r - 1] = 2;
            }
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){

        }
    }

    return 0;
}