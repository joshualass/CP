//https://usaco.guide/gold/dp-bitmasks
//https://atcoder.jp/contests/dp/tasks/dp_o?lang=en

#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

unordered_map<int,int> dp[22]; 
bool match[21][21];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    //compute all valid states
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> match[i][j];
        }
    }


    for(int i = 0; i < (1 << n); i++) {
        dp[__builtin_popcount(i)][i] = 0; 
    }
    dp[0][0] = 1; //1 way to get 0 matches
    for(int i = 0; i < n; i++) { //starting with i matches
        for(int j = 0; j < n; j++) { //going to match this person
            for(auto x : dp[i]) { //iterate over all pairs of i matches
                if(x.second == 0 || (x.first & (1 << j))) continue; //either impossible to reach this state or have already matched this person in this state
                for(bool &y : match[x]) {
                    if()
                }
            }

        }
    }


    return 0;
}