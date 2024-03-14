#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<vector<T>> adj) {
    for(auto x : adj) {
        for(auto y : x) os << y << " ";
        os << "\n";
    }
    return os;
}

int dx[4]{1, -1, 0, 0}, dy[4]{0, 0, 1, -1}; //UP, DOWN, RIGHT, LEFT

// int dx[8]{-1, -1, -1, 0, 0, 1, 1, 1}, dy[8]{-1, 0, 1, -1, 1, -1, 0, 1};


vector<vector<int>> cd(vector<string> &mat) {
    int n = mat.size();
    int m = mat[0].size();
    queue<array<int,3>> q;
    vector distances(n,vector(m,-1));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(mat[i][j] == 'v') {
                q.push({i,j,0});
            }
        }
    }
    while(q.size()) {
        array<int,3> arr = q.front();
        q.pop();
        if(distances[arr[0]][arr[1]] != -1) continue;
        distances[arr[0]][arr[1]] = arr[2];
        for(int i = 0; i < 4; i++) {
            if(arr[0] + dx[i] >= 0 && arr[0] + dx[i] < n && arr[1] + dy[i] >= 0 && arr[1] + dy[i] < m) {
                q.push({arr[0] + dx[i], arr[1] + dy[i],arr[2] + 1});
            }
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(mat[i][j] == '#') {
                distances[i][j] = 0;
            }
        }
    }
    return distances;
}

vector<vector<bool>> gm(vector<string> &mat) {
    vector<vector<bool>> marked(mat.size(),vector<bool>(mat[0].size()));
    for(int i = 0; i < mat.size(); i++) {
        for(int j = 0; j < mat[0].size(); j++) {
            if(mat[i][j] == '#') {
                for(int k = j; k >= 0; k--) {
                    marked[i][k] = 1;
                }
                return marked;
            }
        }
    }
    return {{}};
}

vector<vector<bool>> gm2(vector<string> &mat) {
    vector<vector<bool>> marked(mat.size(),vector<bool>(mat[0].size()));
    for(int i = 0; i < mat.size(); i++) {
        for(int j = mat[0].size() - 1; j >= 0; j--) {
            if(mat[i][j] == '#') {
                for(int k = j; k < mat[0].size(); k++) {
                    marked[i][k] = 1;
                }
                return marked;
            }
        }
    }
    return {{}};
}

vector<vector<int>> cmd(vector<vector<int>> &dist, vector<vector<bool>> &marked, int sn, int sm, int ok, int notok) {
    int n = dist.size();
    int m = dist[0].size();
    vector md(n,vector(m,-1));
    vector md2(n,vector(m,-1));
    priority_queue<array<int,3>> pq;
    priority_queue<array<int,3>> pq2;
    pq.push({dist[sn][sm],sn,sm});
    while(pq.size()) {
        array<int,3> a = pq.top();
        pq.pop();
        if(md[a[1]][a[2]] != -1) continue;
        md[a[1]][a[2]] = a[0];
        for(int i = 0; i < 4; i++) {
            if(a[1] + dx[i] >= 0 && a[1] + dx[i] < n && a[2] + dy[i] >= 0 && a[2] + dy[i] < m) {
                if((marked[a[1]][a[2]] == 0 || i != ok) && (marked[a[1] + dx[i]][a[2] + dy[i]] == 0 || i != notok) && md[a[1] + dx[i]][a[2] + dy[i]] == -1) {
                    pq.push({min(a[0],dist[a[1] + dx[i]][a[2] + dy[i]]), a[1] + dx[i], a[2] + dy[i]});
                }
                if(marked[a[1]][a[2]] == 1 && i == ok) {
                    pq2.push({min(a[0],dist[a[1] + dx[i]][a[2] + dy[i]]), a[1] + dx[i], a[2] + dy[i]});
                }
            }
        }
    }
    while(pq2.size()) {
        array<int,3> a = pq2.top();
        pq2.pop();
        if(md2[a[1]][a[2]] != -1) continue;
        md2[a[1]][a[2]] = a[0];
        for(int i = 0; i < 4; i++) {
            if(a[1] + dx[i] >= 0 && a[1] + dx[i] < n && a[2] + dy[i] >= 0 && a[2] + dy[i] < m  && md2[a[1] + dx[i]][a[2] + dy[i]] == -1) {
                pq2.push({min(a[0],dist[a[1] + dx[i]][a[2] + dy[i]]), a[1] + dx[i], a[2] + dy[i]});
            }
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            md[i][j] = max(md[i][j],md2[i][j]);
        }
    }

    return md;
}

int mm(vector<vector<int>> &dist1, vector<vector<int>> &dist2, vector<vector<bool>> &marked) {
    int ans = 0;
    for(int i = 0; i < dist1.size(); i++) {
        for(int j = 0; j < dist1[0].size(); j++) {
            if(marked[i][j]) {
                ans = max(ans, min(dist1[i][j],dist2[i][j]));
            }
        }
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, q; cin >> n >> m >> q;
    vector<string> mat(n);
    for(auto &x : mat) cin >> x;

    vector distances = cd(mat);  
    vector marked = gm(mat); 
    vector marked1 = gm2(mat); 

    // cout << "dist\n" << distances;
    // cout << "marked\n" << marked;
    // cout << "marked1\n" << marked1;

    for(int i = 0; i < q; i++) {
        int x, y; cin >> x >> y;
        x--; y--;
        vector dist1 = cmd(distances,marked,x,y,0,1);
        vector dist2 = cmd(distances,marked,x,y,1,0);
        // cout << "x : " << x << " y : " << y << '\n';
        // cout << "d1\n" << dist1;
        // cout << "d2\n" << dist2;
        int res = mm(dist1,dist2,marked);
        vector dist12 = cmd(distances,marked1,x,y,0,1);
        vector dist22 = cmd(distances,marked1,x,y,1,0);
        // cout << "x : " << x << " y : " << y << '\n';
        // cout << "d12\n" << dist12;
        // cout << "d22\n" << dist22;
        int res2 = mm(dist12,dist22,marked1);
        cout << min(res,res2) << '\n';
    }

    return 0;
}