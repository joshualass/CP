#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;
const ll N = 1e6 + 1;

ll dp1[N]; //ways you can get for one half/side of the tower
ll dp2[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    fill(begin(dp1),begin(dp1)+N,0);
    fill(begin(dp2),begin(dp2)+N,0);
    dp1[1]=1;
    dp2[1]=1;
    for(int i = 2; i < N; i++) {
        dp1[i] = dp1[i-1]*4 + dp2[i-1];
        dp2[i] = dp1[i-1] + dp2[i-1] * 2;
        dp1[i] %= MOD;
        dp2[i] %= MOD;
    }
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        cout << (dp1[num] + dp2[num]) % MOD << "\n";
    }


    return 0;
}