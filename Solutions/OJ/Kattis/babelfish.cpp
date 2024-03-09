#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string line = "lol";
    getline(cin,line);
    map<string,string> m;
    while(line != "") {
        stringstream ss(line);
        string s1, s2; ss >> s1 >> s2;
        m[s2] = s1;
        getline(cin,line);
    }

    cin >> line;
    while(!cin.eof()) {
        if(m.count(line)) {
            cout << m[line] << '\n';
        } else {
            cout << "eh\n";
        }
        cin >> line;
    }

    return 0;
}