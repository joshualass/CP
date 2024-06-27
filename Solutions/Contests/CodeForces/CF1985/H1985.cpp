#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

/*
First idea which was correctly implemented TLEs because doing all the enterlefts/enterrights is N * M times and each time is upward of O(N). 
Overall Complexity is not N*M as prepared.

Try analyzing specifically all the points where the components double count. This will be a rectangle/box. 
To handle double counting, we can create a range doublecount prefix sum or similar.

Overall, bad idea to analyze adding and removing components. 
*/

void solve() {
    
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 998244353;

// int dx[4]{1, -1, 0, 0}, dy[4]{0, 0, 1, -1}; //UP, DOWN, RIGHT, LEFT

// void addcnt(int i, vector<vector<pair<int,int>>> &enter, map<int,int> &m, int &curr, vector<int> &sizes) {
//     for(pair<int,int> p : enter[i]) {
//         m[p.first] += p.second;
//         if(m[p.first] == 0 || m[p.first] == 1 && p.second == 1) {
//             // cout << "curr is changing /!\\" << endl;
//             curr += sizes[p.first] * p.second;
//         }
//     }
// }

// void solve() {
//     int n, m; cin >> n >> m;
//     vector<string> mat(n);
//     for(auto &x : mat) cin >> x;
//     vector<string> matcopy = mat;
//     vector<int> r(n); //how many # in row 
//     vector<int> c(m); //how many # in col
//     vector<int> sizes; //size of all the components
//     vector<vector<pair<int,int>>> enterdown(n+3), enterright(m+3), enterleft(m+3); // {id of component, +-1 whether included/excluded}
//     for(int i = 0; i < n; i++) {
//         for(int j = 0; j < m; j++) {
//             if(mat[i][j] == '#') {
//                 int sz = 0; //size of this component
//                 int id = sizes.size(); //id of this component
//                 int mini = INT_MAX, maxi = INT_MIN;
//                 int minj = INT_MAX, maxj = INT_MIN;
//                 queue<pair<int,int>> q;
//                 q.push({i,j});
//                 while(q.size()) {
//                     pair<int,int> p = q.front();
//                     q.pop();
//                     int x = p.first, y = p.second;
//                     if(mat[x][y] == '.') continue;
//                     r[x]++;
//                     c[y]++;
//                     mat[x][y] = '.';
//                     sz++;
//                     mini = min(mini,x);
//                     maxi = max(maxi,x);
//                     minj = min(minj,y);
//                     maxj = max(maxj,y);
//                     for(int k = 0; k < 4; k++) {
//                         int newx = x + dx[k], newy = y + dy[k];
//                         if(newx >= 0 && newx < n && newy >= 0 && newy < m) {
//                             q.push({newx,newy});
//                         }
//                     }
//                 }
//                 // cout << "stats id : " << id << " mini : " << mini << " maxi : " << maxi << " minj : " << minj << " maxj : " << maxj << endl;
//                 enterdown[max(0,mini-1)].push_back({id,1}); //what happens when I go down to current cell
//                 enterdown[maxi+2].push_back({id,-1});

//                 enterright[max(0,minj-1)].push_back({id,1}); //what happens when I go right to current cell
//                 enterright[maxj+2].push_back({id,-1});
                
//                 enterleft[maxj+1].push_back({id,1}); //what happens when I go left to current cell
//                 if(minj - 2 >= 0) {
//                     enterleft[minj-2].push_back({id,-1});
//                 }
//                 sizes.push_back(sz);
//             }
//         }
//     }

//     // cout << "enterdown : " << enterdown << endl;
//     // cout << "enterright : " << enterright << endl;
//     // cout << "enterleft : " << enterleft << endl;

//     int curr = 0;
//     int currx = -1, curry = 0;
//     map<int,int> cnts;
//     addcnt(0,enterright,cnts,curr,sizes);
//     int res = curr;
//     while(1) {
//         bool godown = 0, goleft = 0, goright = 0;
//         int nextx = -1, nexty = -1;
//         if(currx % 2 == 0) {
//             if(curry == m - 1) {
//                 godown = 1;
//                 nextx = currx + 1, nexty = curry;
//             } else {
//                 nextx = currx, nexty = curry + 1;
//                 goright = 1;
//             }
//         } else {
//             if(curry == 0) {
//                 godown = 1;
//                 nextx = currx + 1, nexty = curry;
//             } else {
//                 nextx = currx, nexty = curry - 1;
//                 goleft = 1;
//             }
//         }
//         // cout << "currx : " << currx << " curry : " << curry << " nextx : " << nextx << " nexty : " << nexty << endl;
//         if(nextx == n) break;
//         if(godown) {
//             addcnt(nextx, enterdown, cnts, curr, sizes);
//         }
//         if(goleft) {
//             addcnt(nexty, enterleft, cnts, curr, sizes);
//         }
//         if(goright) {
//             addcnt(nexty, enterright, cnts, curr, sizes);
//         }
//         currx = nextx, curry = nexty;
//         res = max(res,curr + n - r[currx] + m - c[curry] - 1 + (matcopy[currx][curry] == '#'));
//         // cout << "r : " << currx << " c : " << curry << " curr : " << curr << " total : " << curr + n - r[currx] + m - c[curry] - 1 + (matcopy[currx][curry] == '#') << '\n';
//     }

//     cout << res << '\n';
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }