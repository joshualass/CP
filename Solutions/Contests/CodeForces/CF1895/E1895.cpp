#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template<typename T, typename D>
std::ostream& operator<<(std::ostream& os, map<T,D> m) {
    for(auto &x: m) os << x.first << " " << x.second << " | ";
    return os;
}

void solve() {
    
    int n; cin >> n;
    vector<array<int,2>> a(n); //{attack, defense}
    for(int i = 0; i < n; i++) {
        cin >> a[i][0];
    }
    for(int i = 0; i < n; i++) {
        cin >> a[i][1];
    }
    int m; cin >> m;
    vector<array<int,2>> b(m);
    for(int i = 0; i < m; i++) {
        cin >> b[i][0];
    }
    for(int i = 0; i < m; i++) {
        cin >> b[i][1];
    }
    
    map<int,int> ac; //for a given health of monster b, what is the max health a can return with
    map<int,int> bc; //for a given health of monster a, what is the max health b can return with
    
    auto work = [&](vector<array<int,2>> attackers, vector<array<int,2>> defenders, map<int,int> &c) {
        
        sort(attackers.begin(), attackers.end());
        sort(defenders.begin(), defenders.end(), [](const auto &lhs, const auto &rhs) {
            return lhs[1] < rhs[1];
        });
        
        int ap = attackers.size();
        int maxhp = -1;
        for(int i = defenders.size() - 1; i >= 0; i--) {
            while(ap > 0 && attackers[ap-1][0] > defenders[i][1]) {
                ap--;
                maxhp = max(maxhp, attackers[ap][1]);
            }
            c[defenders[i][1]] = maxhp;
        }
    };
    
    work(a,b,ac);
    work(b,a,bc);
    
    // cout << "ac : " << ac << '\n';
    // cout << "bc : " << bc << '\n';
    
    sort(a.begin(), a.end(), [](const auto &lhs, const auto &rhs) {
        return lhs[1] < rhs[1]; 
    });
    
    map<int,int> dp; //-1 bicarp wins, 0 draw, 1 monocarp wins
        
    for(int i = n - 1; i >= 0; i--) {
        
        set<int> vis;
        int mono = 0;
        int currhp = a[i][1];
        
        // cout << "start hp : " << currhp << '\n';
        
        while(1) {
            // cout << "mono : " << mono << " hp : " << currhp << '\n';
            if(mono) {//mono turn, bi has monster out
                if(vis.count(currhp)) {
                    dp[a[i][1]] = 0;
                    break;
                }
                vis.insert(currhp);
                if(currhp == -1) {
                    dp[a[i][1]] = 1;
                    break;
                }
                currhp = ac[currhp];
            } else {
                if(dp.count(currhp)) {
                    dp[a[i][1]] = dp[currhp];
                    break;
                }
                if(currhp == -1) {
                    dp[a[i][1]] = -1;
                    break;
                }
                currhp = bc[currhp];
            }
            mono ^= 1;
        }
    }
    
    // cout << "dp : " << dp << '\n';
    
    int win = 0, draw = 0, lose = 0;
    for(int i = 0; i < n; i++) {
        if(dp[a[i][1]] == -1) {
            lose++;
        }
        if(dp[a[i][1]] == 0) {
            draw++;
        }
        if(dp[a[i][1]] == 1) {
            win++;
        }
    }

    cout << win << " " << draw << " " << lose << '\n';
    
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}