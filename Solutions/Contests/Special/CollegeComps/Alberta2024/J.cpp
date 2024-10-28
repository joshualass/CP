#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

#pragma GCC optimize("Ofast,fast-math,unroll-loops,no-stack-protector") 
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,avx,mmx,avx2,fma,tune=native") 

// more pragmas from apgpsoop
// #pragma GCC optimize("-funsafe-loop-optimizations")
// #pragma GCC optimize("-funroll-loops")
// #pragma GCC optimize("-fwhole-program")
// #pragma GCC optimize("Ofast,no-stack-protector")
// #pragma GCC optimize("-fthread-jumps")
// #pragma GCC optimize("-falign-functions")
// #pragma GCC optimize("-falign-jumps")
// #pragma GCC optimize("-falign-loops")
// #pragma GCC optimize("-falign-labels")
// #pragma GCC optimize("-fcaller-saves")
// #pragma GCC optimize("-fcrossjumping")
// #pragma GCC optimize("-fcse-follow-jumps")
// #pragma GCC optimize("-fcse-skip-blocks")
// #pragma GCC optimize("-fdelete-null-pointer-checks")
// #pragma GCC optimize("-fdevirtualize")
// #pragma GCC optimize("-fexpensive-optimizations")
// #pragma GCC optimize("-fgcse")
// #pragma GCC optimize("-fgcse-lm")
// #pragma GCC optimize("-fhoist-adjacent-loads")
// #pragma GCC optimize("-finline-small-functions")
// #pragma GCC optimize("-findirect-inlining")
// #pragma GCC optimize("-fipa-sra")
// #pragma GCC optimize("-foptimize-sibling-calls")
// #pragma GCC optimize("-fpartial-inlining")
// #pragma GCC optimize("-fpeephole2")
// #pragma GCC optimize("-freorder-blocks")
// #pragma GCC optimize("-freorder-functions")
// #pragma GCC optimize("-frerun-cse-after-loop")
// #pragma GCC optimize("-fsched-interblock")
// #pragma GCC optimize("-fsched-spec")
// #pragma GCC optimize("-fschedule-insns")
// #pragma GCC optimize("-fschedule-insns2")
// #pragma GCC optimize("-fstrict-aliasing")
// #pragma GCC optimize("-fstrict-overflow")
// #pragma GCC optimize("-ftree-switch-conversion")
// #pragma GCC optimize("-ftree-tail-merge")
// #pragma GCC optimize("-ftree-pre")
// #pragma GCC optimize("-ftree-vrp")


double ep = 1e-10;
int dx[8]{-1, -1, -1, 0, 0, 1, 1, 1}, dy[8]{-1, 0, 1, -1, 1, -1, 0, 1};
double dp[20010000];
int hv[100][100];
bitset<100000000> boosts{};

array<int,3> decrypt(int z) {
    return {z / 200100 % 100, z / 2001 % 100, z % 2001};
}

int encrypt(array<int,3> a) {
    return a[0] * 200100 + a[1] * 2001 + a[2];
}

int encryptboost(array<int,4> a) {
    return a[0] * 1000000 + a[1] * 10000 + a[2] * 100 + a[3];
}

array<int,4> decryptboost(int z) {
    return {z / 1000000 % 100, z / 10000 % 100, z / 100 % 100, z % 100};
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for(int i = 0; i < 20010000; i++) {
        dp[i] = -1;
    }

    for(int i = 0; i < 100; i++) {
        for(int j = 0; j < 100; j++) {
            hv[i][j] = -1;
        }
    }

    int n, m; cin >> n >> m;
    vector<vector<int>> h(n,vector<int>(m));

    for(auto &x : h) for(auto &y : x) cin >> y;
    int bb; cin >> bb;
    for(int i = 0; i < bb; i++) {
        int r1, c1, r2, c2; cin >> r1 >> c1 >> r2 >> c2;
        boosts[encryptboost({r1,c1,r2,c2})] = 1;
    }

    // priority_queue<pair<pair<double,int>, array<int,2>>, vector<pair<pair<double,int>, array<int,2>>>, greater<pair<pair<double,int>, array<int,2>>>> pq;
    priority_queue<pair<double,int>, vector<pair<double,int>>, greater<pair<double,int>>> pq;
    dp[0] = 0;
    pq.push({0,0});
    while(pq.size()) {
        auto [time, aa] = pq.top();
        pq.pop();

        auto [r,c,v] = decrypt(aa);

        if(hv[r][c] >= v) continue;
        // cout << "time : " << time << " v : " << v << " r : " << r << " c : " << c << '\n';

        hv[r][c] = v;

        for(int i = 0; i < 8; i++) {
            int nr = r + dx[i], nc = c + dy[i];
            // cout << "nr : " << nr << " nc : " << nc << '\n';
            if(nr >= 0 && nr < n && nc >= 0 && nc < m) {
                int newv = v + (h[r][c] - h[nr][nc]);
                if(boosts[encryptboost({r,c,nr,nc})]) {
                    newv *= 2;
                }
                newv = min(newv, 2000);
                double dist = min(150,(abs(r-nr) + abs(c-nc))*100);
                int nextz = encrypt({nr,nc,newv});
                // cout << "push\n";
                if(newv > 0 && hv[nr][nc] < newv) {
                    if(dp[nextz] == -1 || dp[nextz] > time + dist/newv) {
                        dp[nextz] = time + dist/newv;
                        pq.push({time + dist / newv, nextz});
                    }
                }
            }
        }
    }

    double time = 129837412;

    for(int i = 0; i <= 2000; i++) {
        time = min(time, (dp[encrypt({n-1,m-1,i})] == -1 ? time : dp[encrypt({n-1,m-1,i})]));
    }

    cout << fixed << setprecision(10) << time << '\n';

    return 0;
}