#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int dx[4]{1, -1, 0, 0}, dy[4]{0, 0, 1, -1}; //UP, DOWN, RIGHT, LEFT

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<vector<T>> adj) {
    for(auto &x : adj) {
        for(auto &y : x) os << y << " ";
        os << "\n";
    }
    return os;
}

void solve() {
    int r, c; cin >> r >> c;
    vector<string> v(r);
    for(auto &x : v) cin >> x;
    vector<vector<bool>> visited(r,vector<bool>(c));
    vector<vector<int>> counts(r,vector<int>(c));
    for(int i = 0 ; i < r; i++) {
        for(int j = 0; j < c; j++) {
            if(!visited[i][j] && v[i][j] == 'W') {
                int outs = 0;
                pair<int,int> coords = {-1,-1};
                int cnt = 0;
                queue<pair<int,int>> q;
                q.push({i,j});
                while(q.size()) {
                    pair<int,int> p = q.front();
                    q.pop();
                    if(p.first < 0 || p.first >= r || p.second < 0 || p.second >= c) continue;
                    if(v[p.first][p.second] == 'B') continue;
                    if(v[p.first][p.second] == 'W') {
                        if(visited[p.first][p.second]) continue;
                        cnt++;
                        visited[p.first][p.second] = true;
                        for(int i = 0; i < 4; i++) {
                            q.push({p.first + dx[i], p.second + dy[i]});
                        }
                    } else if(v[p.first][p.second] == '.' && (p.first != coords.first || p.second != coords.second)) {
                        outs++;
                        coords = {p.first,p.second};
                    }
                }
                if(outs == 1) {
                    counts[coords.first][coords.second] += cnt;
                }
            }
        }
    }

    // cout << counts << "\n";

    int most = 0;
    for(auto x : counts) {
        for(auto y : x) {
            most = max(most,y);
        }
    }
    cout << (most ? "YES" : "NO") << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);

    freopen("A1.in","r",stdin);
    freopen("A1.txt","w",stdout);
    
    int casi; cin >> casi;
    for(int i = 1; i <= casi; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}