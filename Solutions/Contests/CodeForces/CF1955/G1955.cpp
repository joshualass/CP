#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template<typename T>
std::ostream& operator<<(std::ostream& os, unordered_set<T> s) {
    for(auto &x: s) os << x << " ";
    return os;
}

const int N = 1e6 + 1;

int nums[100][100];
unordered_map<int,int> lu[N];

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<unordered_set<int>>> matd(n,vector<unordered_set<int>>(m));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> nums[i][j];
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int num = nums[i][j];
            if(i == 0 && j == 0) {
                matd[i][j] = {num};
            } else {
                if(i != 0) {
                    if(nums[i][j] % nums[i-1][j] == 0) {
                        swap(matd[i][j],matd[i-1][j]);
                    } else {
                        for(int x : matd[i-1][j]) {
                            if(lu[min(x,num)].count(max(x,num)) == 0) {
                                lu[min(x,num)].insert({max(x,num),gcd(x,num)});
                            } 
                            int v = lu[min(x,num)][max(x,num)];
                            bool add = 1;
                            for(int y : matd[i][j]) {
                                if(y % v == 0) {
                                    add = 0;
                                    break;
                                }
                            }
                            if(add) {
                                matd[i][j].insert(lu[min(x,num)][max(x,num)]);
                            }
                        }
                    }
                }
                if(j != 0) {
                    if(nums[i][j] % nums[i][j-1] == 0) {
                        for(int x : matd[i][j-1]) {
                            matd[i][j].insert(x);
                        }
                    } else {
                        for(int x : matd[i][j-1]) {
                            if(lu[min(x,num)].count(max(x,num)) == 0) {
                                lu[min(x,num)].insert({max(x,num),gcd(x,num)});
                            } 
                            int v = lu[min(x,num)][max(x,num)];
                            bool add = 1;
                            for(int y : matd[i][j]) {
                                if(y % v == 0) {
                                    add = 0;
                                    break;
                                }
                            }
                            if(add) {
                                matd[i][j].insert(lu[min(x,num)][max(x,num)]);
                            }
                        }
                    }
                }
                
            }
            // cout << "i : " << i << " j : " << j << " matd[i][j] : " << matd[i][j] << '\n';
        }
    }
    int res = 0;
    for(int x : matd[n-1][m-1]) {
        res = max(res,x);
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