#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;
const ll N = 1e6 + 1;

ll dp1[N]; //number of towers you can make with the top of the tower ending with 2 blocks (2 1 wide blocks)
ll dp2[N]; //number of towers you can make with the top of the tower being a rectangle block (1 2 wide block)

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //We precomputute the number of ways to make each height of the tower and makes queries easy.
    fill(begin(dp1),begin(dp1)+N,0);
    fill(begin(dp2),begin(dp2)+N,0);
    //initially 1 way to make each version of 1 height
    dp1[1]=1;
    dp2[1]=1;
    for(int i = 2; i < N; i++) {
        //the next tower height ending with a 2 1 wide blocks can have 4 variations of the previous 2 1 wide blocks 
        //as well as one variation of the 2 wide block ending
        dp1[i] = dp1[i-1]*4 + dp2[i-1]; 
        //the next tower height ending with a 2 wide block can be made from 1 variation of the 2 1 wide blocks 
        //as well as two variations of the 2 wide block ending
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