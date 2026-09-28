#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string str; cin >> str;
    bool flag = true;
    for(int i = 1; i < 16; i+= 2) {
        if(str[i] != '0') flag = false;
    }
    cout << (flag ? "Yes" : "No") << "\n";
    return 0;
}