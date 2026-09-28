#include <bits/stdc++.h>
typedef long long ll;
typedef __int128_t lll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n, k; cin >> n >> k;
    string str; cin >> str;
    int onecount = 0;
    int zerocount = 0;
    int qcount = 0;
    for(int i = 0; i < n; i++) {
        switch(str[i]) {
            case '0' : zerocount++; break;
            case '1' : onecount++; break;
            case '?' : qcount++; break;
        }
    }
    int curr1 = 0, curr0 = 0, currq = 0;
    for(int i = 0; i < k; i++) {
        switch(str[i]) {
            case '0' : curr0++; break;
            case '1' : curr1++; break;
            case '?' : currq++; break;
        }
    }
    int cnt = curr1 == onecount && curr0 == 0;
    for(int i = k; i < n; i++) {
        switch(str[i]) {
            case '0' : curr0++; break;
            case '1' : curr1++; break;
            case '?' : currq++; break;
        }
        switch(str[i-k]) {
            case '0' : curr0--; break;
            case '1' : curr1--; break;
            case '?' : currq--; break;
        }      
        if(curr1 == onecount && curr0 == 0) cnt++;          
    }
    cout << ((cnt == 1 || (k == 0 && zerocount == n)) ? "Yes\n" : "No\n");
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}