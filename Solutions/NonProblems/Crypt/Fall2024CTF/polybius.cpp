#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    string s = "2532252335111241254415141314313213321314312325442323331423342325441542315424341525";
    string a = "";
    for(int i = 0; i < s.size(); i += 2){
        int x = 5 * (s[i] - '1') + (s[i+1] - '1');
        // if(x >= 9) x++;
        cout << "X : " << x << "\n";
        a.push_back(x + 'A');
    }
    cout << a << "\n";
    
    return 0;
}

/*

GIGEMCONGRATSTHISISTHEGREEKTELEGRAPHYFLAG
*/