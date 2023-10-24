#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<pair<int,int>> wins(n);
    for(int i = 0; i < n; i++) {
        string str; cin >> str;
        int cnt = 0;
        for(int j = 0; j < n; j++) {
            if(str[j] == 'o') cnt++;
        }
        wins[i] = {cnt,-i};
    }
    sort(wins.rbegin(),wins.rend());
    
    for(auto &x: wins) cout << (-x.second) + 1 << " ";
    return 0;
}