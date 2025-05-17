#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
did not consider a case like 

n = 199 
199200
001299
n = 901
901902
001299

909 fails assert 

gg

*/

int bf (int n) {
    set<string> s;
    for(int i = 1; i <= n; i++) {
        string t = to_string(i) + to_string(i + 1);
        sort(t.begin(),t.end());
        s.insert(t);
    }
    return s.size();
}

void solve() {
    ll n; cin >> n;
    string ns = to_string(n);
    int nd = ns.size(); //num digits

    vector<int> p10(10);
    p10[0] = 1;
    for(int i = 1; i < 10; i++) p10[i] = p10[i-1] * 10;

    int res = 0;

    for(int len = 1; len <= nd; len++) {
        cout << "len : " << len << '\n';
        vector dp(len, vector(10, vector<ll>(2))); //{len of pref, max digit used, 0 / 1 if tight on n}

        //handle all but the first digit 9
        for(int l = 1; l < 10; l++) {
            int num = (l + 1) * p10[len - 1] - 1;
            if(num <= n) {
                // cout << "add full l : " << l << '\n';
                res++;
            }
        }

        //initialize first number + some amt of zeroes 
        for(int i = 1; i <= 9; i++) { //first digit in num
            for(int j = 1; j < len; j++) { //zc + 1
                int num = i * p10[j - 1];
                int tn = n / p10[len - j];
                if(num <= tn) {
                    // cout << "i : " << i << " j : " << j << " num : " << num << " tn : " << tn << '\n';
                    dp[j][i][num == tn] = 1;
                }
            }   
        }

        for(int i = 1; i < len; i++) { //current digit
            for(int j = 1; j < 10; j++) { //current max digit
                for(int k = 0; k < 2; k++) { //tight 0 / 1
                    if(dp[i][j][k]) {
                        if(k) { //tight here
                            assert(dp[i][j][k] == 1);
                            // cout << "reach tight i : " << i << " j : " << j << " k : " << k << '\n';
                            for(int l = 0; l < 10; l++) { //try all possible next digits X9999 combos 
                                int num = (l + 1) * p10[len - i - 1] - 1;
                                int tn = n % p10[len - i];
                                // cout << "i : " << i << " j : " << j << " l : " << l << " num : " << num << " tn : " << tn << '\n';

                                if(num <= tn) res++;
                            }
                            if(i + 1 < len) { //push
                                int nxd = n / p10[len - i - 2] % 10; //next digit 
                                for(int l = j; l <= nxd; l++) {
                                    dp[i+1][l][l == nxd] += dp[i][j][k];
                                }
                            }
                        } else {
                            // cout << "add i : " << i << " j : " << j << " k : " << k << '\n';
                            res += dp[i][j][k] * 9; //last digit can be 0 - 8. 
                            if(i + 1 < len) {
                                for(int l = j; l <= 9; l++) {
                                    dp[i+1][l][0] += dp[i][j][k];
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    cout << "solve ";
    cout << res << '\n';
    cout << "bf " << bf(n) << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    set<string> s;
    for(int i = 1; i <= 10000; i++) {
        string t = to_string(i) + to_string(i+1);
        sort(t.begin(), t.end());
        if(s.count(t) == 0) {
            s.insert(t);
        } else {
            cout << i << '\n';
        }
    }

    // int casi; cin >> casi;
    // while(casi-->0) solve();

    return 0;
}