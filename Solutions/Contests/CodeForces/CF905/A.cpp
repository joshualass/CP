#include <bits/stdc++.h>
typedef long long ll;
typedef __int128_t lll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n, k; cin >> n >> k;
    string str; cin >> str;
    vector<int> cnts(26);
    for(int i = 0; i < str.size(); i++) {
        cnts[str[i] - 'a']++;
    }
    for(int i = 0; i < cnts.size(); i++) {
        if(cnts[i] & 1) k--;
    }
    cout << (k >= -1 ? "YES" : "NO") << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}