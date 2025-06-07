#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
p_reach[i][j] - for i + j rounds, probability of doing i no shines and j shines
win[i][j] - given total of i rounds and j health left, stores the probability of winnning, assume that minhp = floor(sum hp / n)
*/

/*
1
2 2 10
2 2
*/

ld choose[4001][4001];
ld pnoshine[4001], pshine[4001];
ld win[4001][20 * 400 + 1];

void solve() {
 
    int n, m, p; cin >> n >> m >> p;
    
    pnoshine[0] = 1;
    for(int i = 1; i <= m; i++) pnoshine[i] = pnoshine[i-1] * (100 - p) / 100;
    pshine[0] = 1;
    for(int i = 1; i <= m; i++) pshine[i] = pshine[i-1] * p / 100;
    
    auto p_reach = [&](int i, int j) -> ld {
        return choose[i + j][i] *  pnoshine[i] * pshine[j]; 
    };
    
    win[0][0] = 1;
    
    for(int i = 1; i <= m; i++) {
        for(int j = 0; j <= n * 400; j++) {
            ld ps = pshine[1];
            if(j) {
                ps *= (j >= n ? max(win[i-1][j - n], win[i-1][j]) : win[i-1][j]);
            } 
            ld pns = pnoshine[1] * max(j ? win[i-1][j-1] : 0, win[i-1][j]);
            win[i][j] = ps + pns;
        }
    }
    
    vector<int> a(n);
    for(int &x : a) {
        cin >> x;
        x--;
    }

    int lo = *min_element(a.begin(), a.end());
    int s = accumulate(a.begin(), a.end(), 0);
    
    ld res = 0;
    
    int need_noshine = s - lo * n;

    if(need_noshine == 0) {
        // cout << "case 1\n";
        res = win[m][s];
    } else {
        // cout << "case 2\n";
        for(int i = 0; i + need_noshine <= m; i++) {
            res += p_reach(need_noshine - 1, i) * pnoshine[1] * win[m - (i + need_noshine)][max(0, s - need_noshine - i * n)];
        }
        // for(int i = 0; i + need_noshine <= m; i++) {
        //     res += p_reach(need_noshine, i) * win[m - (i + need_noshine)][max(0, s - need_noshine - i * n)];
        // }
    }
    
    cout << fixed << setprecision(15) << res << '\n';

    // cout << "print win\n";
    // for(int i = 0; i <= 2; i++) {
    //     for(int j = 0; j <= 2; j++) {
    //         cout << win[i][j] << " ";
    //     }
    //     cout << '\n';
    // }
    
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    choose[0][0] = 1;
    for(int i = 1; i <= 4000; i++) {
        for(int j = 0; j <= 4000; j++) {
            choose[i][j] = choose[i-1][j] + (j ? choose[i-1][j-1] : 0);
        }
    }

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}