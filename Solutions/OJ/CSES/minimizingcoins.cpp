#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int dp [1000001];
int c[100];

int main()
{
    
    int n, x; std::cin >> n >> x;
    for(int i = 0; i < n; i++) {
        std::cin >> c[i];
        dp[c[i]] = 1;
    }
    
    /*
    dp[i] is storing the minimum number of coins needed to make sum i
    
    if it's not possible to make a sum, store 0
    
    The transitions to compute dp[i] are considering all coin values 
    with value c_i and taking the minimum of 
    dp[i-c_i] + 1
    */
    
    for(int i = 1; i <= x; i++) {
        for(int j = 0; j < n; j++) {
            int coin_val = c[j];
            if(coin_val <= i && dp[i - coin_val] != 0) {
                if(dp[i] == 0) {
                    dp[i] = dp[i-coin_val] + 1;
                } else {
                    dp[i] = min(dp[i], dp[i-coin_val] + 1);
                }
            }
        }
    }
    
    std::cout << (dp[x] ? dp[x] : -1) << '\n';

    return 0;
}