#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

//guessforces ...
int pattern [5][5] {
    {0,3,1,4,2},
    {1,4,2,0,3},
    {2,0,3,1,4},
    {3,1,4,2,0},
    {4,2,0,3,1}
};

vector<vector<int>> perms;

int dx [5]{0,0,1,0,-1}, dy [5]{0,1,0,-1,0};

void solve() {
    int n, m; cin >> n >> m;
    vector<string> grid(n);
    for(auto &x : grid) cin >> x;
    vector<vector<int>> needcolor(n,vector<int>(m));


    int minops = 1e9, bestperm = 0;

    for(int i = 0; i < perms.size(); i++) {
        vector<int> perm = perms[i];
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < m; k++) {
                needcolor[j][k] = grid[j][k] == '#';
            }
        }
        int cops = 0;
        for(int p = 0; p < 5; p++) {
            for(int j = 0; j < n; j++) {
                for(int k = pattern[perm[p]][j % 5]; k < m; k += 5) {
                    if(needcolor[j][k]) {
                        cops++;
                        for(int l = 0; l < 5; l++) {
                            int nx = j + dx[l], ny = k + dy[l];
                            if(nx >= 0 && nx < n && ny >= 0 && ny < m) {
                                needcolor[nx][ny] = 0;
                            }
                        }
                    }
                }
            }
        }
        if(cops < minops) {
            minops = cops;
            bestperm = i;
        }
    }

    for(int j = 0; j < n; j++) {
        for(int k = 0; k < m; k++) {
            needcolor[j][k] = grid[j][k] == '#';
        }
    }

    for(int p = 0; p < 5; p++) {
        for(int j = 0; j < n; j++) {
            for(int k = pattern[perms[bestperm][p]][j % 5]; k < m; k += 5) {
                if(needcolor[j][k]) {
                    grid[j][k] = 'S';
                    for(int l = 0; l < 5; l++) {
                        int nx = j + dx[l], ny = k + dy[l];
                        if(nx >= 0 && nx < n && ny >= 0 && ny < m) {
                            needcolor[nx][ny] = 0;
                        }
                    }
                }
            }
        }
    }

    for(auto x : grid) {
        cout << x << '\n';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // vector<int> perm = {0,1,2,3,4};
    // set<vector<int>> vp;
    // for(int i = 0; i < 120; i++) {
    //     if(vp.count({perm[0], perm[1], perm[2], perm[4], perm[3]}) == 0) {
    //         vp.insert(perm);
    //         perms.push_back(perm);
    //     }
    //     next_permutation(perm.begin(), perm.end());
    // }

    vector<int> perm = {0,1,2,3,4};
    for(int i = 0; i < 5; i++) {
        perms.push_back(perm);
        rotate(perm.begin(), perm.begin() + 1, perm.begin() + 5);
    }

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}