#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

set<string> S;

string rev(string s) {
    string a = "";
    for(int i = s.size() - 1; i >= 0; i--) {
        a += s[i];
    }
    return a;
}

void letkira(string s, string a, int splits) {
    if(s.empty()) {
        if(splits % 3 == 2) {
            // cout<< a << '\n';
            S.insert(S.begin(), a);
        }
        return;
    }
    for(int i = 0; i < s.size(); i++) {
        letkira(s.substr(i + 1), a + rev(s.substr(0,i+1)), splits + 1);
        cout << "s: " << s << " i: " << i << " first: " << s.substr(i + 1) << " second: " << a + rev(s.substr(0,i+1)) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string line;
    cin >> line;
    letkira(line, "", 0);
    cout << *(S.begin());


    return 0;
}