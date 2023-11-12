// https://open.kattis.com/problems/catandmice
#include <bits/stdc++.h>
typedef long long ll;
typedef __int128_t lll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;
const ld INF = 1e18;

const int MAXN = 15;

vector<ld> mults(16);
vector<vector<int>> bitcnts;
ld dp[1 << MAXN][MAXN];

ld dist(int x1, int y1, int x2, int y2) {
    return hypot((ld)abs(x1-x2) ,(ld)abs(y1-y2));
}

bool poss(ld velocity, vector<array<int, 3>> &mice) {
    // memset(dp, 1e18, sizeof(dp));
    for(int i = 0; i < (1 << MAXN); i++) {
        // memset(dp[i], INF, sizeof(dp[i]));
        fill(begin(dp[i]), begin(dp[i]) + MAXN, INF);
    }
    dp[0][0] = 0;

    for(int i = 0; i < mice.size(); i++) {
        for(int x : bitcnts[i]) {
            if(i == 0) {
                for(int end = 0; end < mice.size(); end++) {
                    ld speed = velocity * mults[i];
                    ld endtime = dist(0,0,mice[end][0],mice[end][1]) / speed;
                    // cout << "speed: " << mults[i] * velocity << " endtime: " << endtime << '\n';
                    if(endtime <= mice[end][2]) {
                        dp[1 << end][end] = endtime;
                    }
                }
            }
            for(int start = 0; start < mice.size(); start++) {
                if(((x >> start) & 1) && dp[x][start] != INF) {
                    for(int end = 0; end < mice.size(); end++) {
                        if(((x >> end) & 1) == 0) {
                            ld speed = velocity * mults[i];
                            ld starttime = dp[x][start];
                            ld endtime = starttime + dist(mice[start][0], mice[start][1], mice[end][0], mice[end][1]) / speed;
                            if(endtime <= mice[end][2]) {
                                dp[x | (1 << end)][end] = min(dp[x | (1 << end)][end], endtime);
                            }
                        }
                    }
                }
            }
        }
    }
    for(int i = 0; i < mice.size(); i++) {
        if(dp[(1 << mice.size()) - 1][i] != INF) {
            // cout << "possible velocity: " << velocity << " i: " << i << " time: " << dp[(1 << mice.size()) - 1][i] << " num: " << '\n';
            return true;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<array<int,3>> mice(n);
    bitcnts.assign(n + 1, {});

    for(int i = 0; i < (1 << n); i++) {
        bitcnts[__builtin_popcount(i)].push_back(i);
    }

    for(auto &x: mice) for(auto &y : x) cin >> y;

    ld mult; cin >> mult;
    mults[0] = 1;
    for(int i = 1; i <= 15; i++) {
        mults[i] = mults[i-1] * mult;
    }

    ld l = 1e-6, r = 1e12;
    while(r - l > 1e-4) {
        ld m = (l + r) / 2;
        if(poss(m,mice)) {
            r = m;
        } else {
            l = m;
        }
    }
    cout << fixed << setprecision(5) << l << "\n";
    return 0;
}