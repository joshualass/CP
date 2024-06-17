#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

int dx[4]{1, -1, 0, 0}, dy[4]{0, 0, 1, -1}; //UP, DOWN, RIGHT, LEFT

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << '(' << p.first << ", " << p.second << ") ";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void addcnt(int i, vector<vector<pair<int,int>>> &enter, map<int,int> &m, int &curr, vector<int> &sizes) {
    for(pair<int,int> p : enter[i]) {
        m[p.first] += p.second;
        if(m[p.first] == 0 || m[p.first] == 1 && p.second == 1) {
            cout << "curr is changing /!\\" << endl;
            curr += sizes[p.first] * p.second;
        }
    }
}

void solve() {
    int n, m; cin >> n >> m;
    vector<string> mat(n);
    for(auto &x : mat) cin >> x;
    vector<int> r(n);
    vector<int> c(m);
    vector<int> sizes;
    vector<vector<pair<int,int>>> enterdown(n+3), enterright(m+3), enterleft(m+3); // {id, +-1}
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(mat[i][j] == '#') {
                int sz = 0;
                int mini = INT_MAX, maxi = INT_MIN;
                int minj = INT_MAX, maxj = INT_MIN;
                queue<pair<int,int>> q;
                q.push({i,j});
                while(q.size()) {
                    pair<int,int> p = q.front();
                    q.pop();
                    int x = p.first, y = p.second;
                    if(mat[x][y] == '.') continue;
                    r[x]++;
                    c[y]++;
                    mat[x][y] = '.';
                    sz++;
                    mini = min(mini,x);
                    maxi = max(maxi,x);
                    minj = min(minj,y);
                    maxj = max(maxj,y);
                    for(int k = 0; k < 4; k++) {
                        int newx = x + dx[k], newy = y + dx[k];
                        if(newx >= 0 && newx < n && newy >= 0 && newy < m) {
                            q.push({newx,newy});
                        }
                    }
                }
                int id = sizes.size();
                cout << "stats id : " << id << " mini : " << mini << " maxi : " << maxi << " minj : " << minj << " maxj : " << maxj << endl;
                enterdown[max(0,mini-1)].push_back({id,1});
                enterdown[mini+2].push_back({id,-1});

                enterright[max(0,minj-1)].push_back({id,1});
                enterright[minj+2].push_back({id,-1});
                
                enterleft[min(m - 1, minj+1)].push_back({id,1});
                if(maxj < m - 1) {
                    enterleft[maxj+1].push_back({id,-1});
                }
                sizes.push_back(sz);
            }
        }
    }

    cout << "enterdown : " << enterdown << endl;
    cout << "enterright : " << enterright << endl;
    cout << "enterleft : " << enterleft << endl;

    int curr = 0;
    int currx = -1, curry = 0;
    int res = 0;
    map<int,int> cnts;
    addcnt(0,enterright,cnts,curr,sizes);
    while(1) {
        bool godown = 0, goleft = 0, goright = 0;
        int nextx = -1, nexty = -1;
        if(currx % 2 == 0) {
            if(curry == m - 1) {
                godown = 1;
                nextx = currx + 1, nexty = curry;
            } else {
                nextx = currx, nexty = curry + 1;
                goright = 1;
            }
        } else {
            if(curry == 0) {
                godown = 1;
                nextx = currx + 1, nexty = curry;
            } else {
                nextx = currx, nexty = curry - 1;
                goleft = 1;
            }
        }
        cout << "currx : " << currx << " curry : " << curry << " nextx : " << nextx << " nexty : " << nexty << endl;
        if(nextx == n) break;
        if(godown) {
            addcnt(nextx, enterdown, cnts, curr, sizes);
        }
        if(goleft) {
            addcnt(nexty, enterleft, cnts, curr, sizes);
        }
        if(goright) {
            addcnt(nexty, enterright, cnts, curr, sizes);
        }
        currx = nextx, curry = nexty;
    }

    cout << res << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}