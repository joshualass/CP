#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
   ios_base::sync_with_stdio(false);
   cin.tie(NULL);

   int casi; cin >> casi;
   while(casi-->0) {
      int n, k; cin >> n >> k;
      vector<vector<ll>> dp (k+1,vector<ll>(33)); // a eggs and b drops
      int least = INT_MAX;
      bool found = false;
      for(int c = 1; c < dp[0].size(); c++) {
         for(int r = 1; r < dp.size(); r++) {
            dp[r][c] = dp[r][c-1] + dp[r-1][c-1] + 1;
            if(dp[r][c] >= n) {
               least = min(least,c);
               found = true;
            }
         }
      }
      if(found) {
         cout << least << "\n";
      } else {
         cout << "Impossible\n";
      }
   }
    

   return 0;
}