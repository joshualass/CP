#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int getguard(int state, int guard) {
    while(guard) {
        state /= 3;
        guard--;
    }
    return state % 3;
}

int giveguard(int guard, int pos) {
    while(guard) {
        pos *= 3;
        guard--;
    }
    return pos;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int g, p; cin >> g >> p;
    string s; cin >> s;

    int st = 0;
    for(int i = 0; i < g; i++) {
        int p = -1;
        if(s[i] == 'L') {
            p = 0;
        } else if(s[i] == 'F') {
            p = 1;
        } else if(s[i] == 'R') {
            p = 2;
        }
        st += giveguard(i, p);
    }

    vector<int> dp(1 << 20, -1);

    auto dfs = [&](auto self, int st) -> void {
        int latest = 0;
        for(int i = 1; i < g; i++) {
            if(getguard(st, i-1) != 2 && getguard(st,i) != 0) {
                int t = st;
                t -= giveguard(i-1, getguard(st,i-1));
                t -= giveguard(i, getguard(st,i));
                t += giveguard(i-1,2);
                t += giveguard(i,0);
                if(dp[t] == -1) {
                    self(self, t);
                }
                latest = max(latest, dp[t] + 1);
            }
        }        
        dp[st] = latest;
    };

    dfs(dfs, st);

    cout << (*max_element(dp.begin(),dp.end()) >= p) << '\n';

    return 0;
}