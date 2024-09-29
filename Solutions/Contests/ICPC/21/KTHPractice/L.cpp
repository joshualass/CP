#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

int dx[4]{1, -1, 0, 0}, dy[4]{0, 0, 1, -1}; //UP, DOWN, RIGHT, LEFT

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<string> mat(n);
    for(auto &s : mat) cin >> s;

    int sr = -1, sc = -1;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(mat[i][j] != '#' && (i == 0 || i == n - 1 || j == 0 || j == m - 1)) {
                sr = i;
                sc = j; 
            }
        }
    }

    // cout << "mat\n";
    // for(auto m : mat) cout << m << '\n';

    // cout << "sr : " << sr << " sc : " << sc << '\n';

    vector<vector<int>> gotodir(n, vector<int>(m,-1));
    vector<vector<int>> times(n, vector<int>(m,-1));
    vector<vector<array<int,2>>> attime(10000);
    
    queue<array<int,4>> q;
    int p = -1;
    if(sr == 0) {
        p = 1;
    } else if(sr == n - 1) {
        p = 0;
    } else if(sc == 0) {
        p = 3;
    } else {
        p = 2;
    }

    q.push({sr,sc,p ^ 1,0});

    while(q.size()) {
        auto [r,c, pd, time] = q.front();
        q.pop();
        if(gotodir[r][c] != -1) continue;
        gotodir[r][c] = pd ^ 1;
        times[r][c] = time;
        attime[time].push_back({r,c});

        for(int i = 0; i < 4; i++) {
            int dr = r + dx[i], dc = c + dy[i];
            if(dr >= 0 && dr < n && dc >= 0 && dc < m && mat[dr][dc] != '#') {
                q.push({dr,dc,i, time + 1});
            }
        }
    }

    // cout << "starting dir\n";
    // for(auto d : gotodir) cout << d << '\n';
    // cout << "times\n";
    // for(auto t : times) cout << t << '\n';
    
    //check not possible here
    vector<vector<int>> people(n,vector<int>(m,-1));
    int cnt = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(mat[i][j] == 'P') {
                if(gotodir[i][j] == -1) {
                    cout << "-1\n";
                    return 0;
                }
                people[i][j] = cnt++;
            }
        }
    }

    // cout << "starting ppl\n";
    // for(auto p : people) cout << p << '\n';
    vector<vector<int>> res(cnt);

    while(cnt) {
        for(int time = 0; time < 10000; time++) {
            for(auto [r, c] : attime[time]) {
                if(people[r][c] != -1) {
                    if(r == sr && c == sc) {
                        res[people[r][c]].push_back(gotodir[r][c]);
                        people[r][c] = -1;
                        cnt--;
                    } else {
                        int nr = r + dx[gotodir[r][c]], nc = c + dy[gotodir[r][c]];
                        if(people[nr][nc] == -1) {
                            res[people[r][c]].push_back(gotodir[r][c]);
                            swap(people[r][c], people[nr][nc]);
                        } else {
                            res[people[r][c]].push_back(4);
                        }

                    }
                }
            }
        }
    }

    int maxt = 0;

    for(auto s : res) {
        maxt = max(maxt, (int) s.size());
    }

    cout << maxt << '\n';
    for(int i = 0; i < res.size(); i++) {
        for(int j = 0; j < maxt; j++) {
            int val = 4;
            if(j < res[i].size()) {
                val = res[i][j];
            }
            if(val == 0) {
                cout << 'D';
            } else if(val == 1) {
                cout << 'U';
            } else if(val == 2) {
                cout << 'R';
            } else if(val == 3) {
                cout << 'L';
            } else {
                cout << '.';
            }
        }
        cout << '\n';
    }
    

    return 0;
}