#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    bitset<1000001> dp{};
    dp[0] = 1;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        dp |= dp << num;
    }   
    cout << dp.count() - 1 << "\n";
    for(int i = 1; i <= 1e6; i++) {
        if(dp[i]) cout << i << " ";
    }
    cout << endl;
    return 0;
}