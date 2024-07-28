#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

vector<int> dr = {0, 0, -1, 1};
vector<int> dc = {-1, 1, 0, 0};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<string> ig(n), fg(n);
    for(int i = 0; i < n; i++){
        cin >> ig[i];
    }
    for(int i = 0; i < n; i++){
        cin >> fg[i];
    }
    //for each cell, compute the min distance to a final cell. 
    vector<vector<int>> d(n, vector<int>(m, 1e9));
    {
        queue<pair<int, int>> q;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(fg[i][j] == '*') {
                    q.push({i, j});
                    d[i][j] = 0;
                }
            }
        }
        while(q.size() != 0){
            int r = q.front().first;
            int c = q.front().second;
            q.pop();
            for(int i = 0; i < 4; i++){
                int nr = r + dr[i];
                int nc = c + dc[i];
                if(nr < 0 || nc < 0 || nr >= n || nc >= m){
                    continue;
                }
                if(ig[nr][nc] == 'X') {
                    continue;
                }
                if(d[r][c] + 1 < d[nr][nc]) {
                    d[nr][nc] = d[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }
    }
    //some cell in the initial position should be visitable. 
    bool is_valid = false;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(ig[i][j] == '*' && d[i][j] != 1e9) {
                is_valid = true;
            }
        }
    }
    if(!is_valid){
        cout << "NO\n";
        return 0;
    }
    //otherwise, it should always be valid. 
    bool done = false;
    vector<vector<int>> ans(0);
    while(!done){
        //find cell closest to final, which also has a neighboring free cell
        pair<int, int> npos;
        {
            int min_dist = 1e9;
            for(int i = 0; i < n; i++){
                for(int j = 0; j < m; j++){
                    if(ig[i][j] != '*') {
                        continue;
                    }
                    if(d[i][j] >= min_dist){
                        continue;
                    }
                    //check adj
                    bool has_adj = false;
                    for(int k = 0; k < 4; k++){
                        int nr = i + dr[k];
                        int nc = j + dc[k];
                        if(nr < 0 || nc < 0 || nr >= n || nc >= m){
                            continue;
                        }
                        if(d[nr][nc] < d[i][j]) {
                            has_adj = true;
                        }
                    }
                    if(has_adj || d[i][j] == 0){
                        min_dist = d[i][j];
                        npos = {i, j};
                    }
                }
            }
        }
        // cout << "NPOS : " << npos.first << " " << npos.second << "\n";
        vector<vector<bool>> nv(n, vector<bool>(m, false));
        nv[npos.first][npos.second] = true;
        //mark 0 cells that are connected to npos as nv visited
        {
            queue<pair<int, int>> q;
            q.push(npos);
            while(q.size() != 0){
                int r = q.front().first;
                int c = q.front().second;
                q.pop();
                for(int i = 0; i < 4; i++){
                    int nr = r + dr[i];
                    int nc = c + dc[i];
                    if(nr < 0 || nc < 0 || nr >= n || nc >= m){
                        continue;
                    }
                    if(d[nr][nc] != 0){
                        continue;
                    }
                    if(ig[nr][nc] != '*') {
                        continue;
                    }
                    if(nv[nr][nc]) {
                        continue;
                    }
                    nv[nr][nc] = true;
                    q.push({nr, nc});
                }
            }
        }
        // cout << "NV : " << "\n";
        // for(int i = 0; i < n; i++){
        //     for(int j = 0; j < m; j++){
        //         cout << nv[i][j] << " ";
        //     }
        //     cout << "\n";
        // }
        //index all the other cells
        priority_queue<pair<int, pair<int, int>>> nq;
        {
            vector<vector<int>> n_ind(n, vector<int>(m, 1e9));
            n_ind[npos.first][npos.second] = 0;
            queue<pair<int, int>> q;
            q.push(npos);
            while(q.size() != 0){
                int r = q.front().first;
                int c = q.front().second;
                q.pop();
                for(int i = 0; i < 4; i++){
                    int nr = r + dr[i];
                    int nc = c + dc[i];
                    if(nr < 0 || nc < 0 || nr >= n || nc >= m){
                        continue;
                    }
                    if(ig[nr][nc] != '*') {
                        continue;
                    }
                    if(n_ind[nr][nc] != 1e9) {
                        continue;
                    }
                    n_ind[nr][nc] = n_ind[r][c] + 1;
                    q.push({nr, nc});
                }
            }
            for(int i = 0; i < n; i++){
                for(int j = 0; j < m; j++){
                    if(n_ind[i][j] > 0 && n_ind[i][j] != 1e9 && !nv[i][j]) {
                        nq.push({n_ind[i][j], {i, j}});
                    }
                }
            }
        }
        //transfer cells from queue
        done = true;
        while(nq.size() != 0){
            int r = nq.top().second.first;
            int c = nq.top().second.second;
            nq.pop();
            done = false;
            ig[r][c] = '.';
            //find location to put this cell. Should be adjacent to a nv cell
            pair<int, int> mpos;
            int min_dist = 1e9;
            for(int i = 0; i < n; i++){
                for(int j = 0; j < m; j++){
                    if(ig[i][j] == '*') {
                        continue;
                    }
                    bool is_adj = false;
                    for(int k = 0; k < 4; k++){
                        int nr = i + dr[k];
                        int nc = j + dc[k];
                        if(nr < 0 || nc < 0 || nr >= n || nc >= m){
                            continue;
                        }
                        if(nv[nr][nc]) {
                            is_adj = true;
                        }
                    }
                    if(is_adj) {
                        if(d[i][j] < min_dist) {
                            min_dist = d[i][j];
                            mpos = {i, j};
                        }
                    }
                }
            }
            //assume we've found mpos
            ig[mpos.first][mpos.second] = '*';
            nv[mpos.first][mpos.second] = true;
            ans.push_back({r, c, mpos.first, mpos.second});
        }
    }
    cout << "YES\n";
    cout << ans.size() << "\n";
    for(int i = 0; i < ans.size(); i++){
        for(int j = 0; j < 4; j++){
            cout << ans[i][j] + 1 << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
