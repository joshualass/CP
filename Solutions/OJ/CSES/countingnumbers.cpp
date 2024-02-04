#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

vector<ll> dp[20][10];

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

ll shift(int i) {
    ll num = 1;
    for(int j = 0; j < i; j++) num *= 10;
    return num;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    for(int i = 0; i < 20; i++) for(int j = 0; j < 10; j++) dp[i][j] = {0,0,0};
    ll a, b; cin >> a >> b;
    bool start = false;
    bool same = true;
    bool lbz = true;
    for(int i = 19; i >= 0; i--) {
        int digitA = a / shift(i) % 10;
        int digitB = b / shift(i) % 10;
        if(digitA != digitB) {
            if(start && same) {
                start = false;
            }
            same = false;
        }
        if(digitA) lbz = false;
        if(start) {
            if(same) {
                if(dp[i+1][digitA][1] == 1) { //0 numbers match here
                    cout << "0\n";
                    return 0;
                }
                dp[i][digitA] = {0,1,1};
            } else { //different at this point
                for(int j = 0; j < 10; j++) { //case between
                    for(int k = 0; k < 10; k++) {
                        if(j != k) {
                            dp[i][j][0] += dp[i+1][k][0];
                        }
                    }
                }
                for(int j = 0; j < 10; j++) { //case lb
                    for(int k = 0; k < 10; k++) {
                        if(j == k && !lbz) continue;
                        if(j == digitA) {
                            dp[i][j][1] += dp[i+1][k][1];;
                        } else if(j > digitA) {
                            dp[i][j][0] += dp[i+1][k][1];
                        }
                    }
                }
                for(int j = 0; j < 10; j++) { //case ub
                    for(int k = 0; k < 10;k ++) {
                        if(j == k) continue;
                        if(j == digitB && dp[i+1][j][2] != 1) {
                            dp[i][j][2] = 1;
                        } else if(j < digitB) {
                            dp[i][j][0] += dp[i+1][k][2];
                        }
                    }
                }
            }
        } else if(digitB != 0) {//setup here
            start = true;
            for(int j = 0; j < 10; j++) {
                if(j > digitA && j < digitB) {
                    dp[i][j][0] = 1; //in between
                }
                if(j == digitA && dp[i+1][j][1] != 1) {
                    dp[i][j][1] = 1; //lb
                }
                if(j == digitB && dp[i+1][j][2] != 1) {
                    dp[i][j][2] = 1; //ub
                }
            }
        }
    }
    ll sum = 0;
    for(int i = 0; i < 10; i++) {
        sum += accumulate(dp[0][i].begin(),dp[0][i].end(),0LL);
    }
    cout << (same ? 1LL : sum) << "\n";
    // if(same) cout << 1 << "\n";
    // else cout << sum << "\n";
    for(int i = 4; i >= 0; i--) {
        cout << "i: " << i << "\n";
        for(int j = 0; j < 10; j++) {
            cout << dp[i][j] << "\n";
        }
    }
    return 0;
}