#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s1, s2; 
    getline(cin, s1);
    getline(cin, s2);

    int s1ptr = 0, s2ptr = 0;

    set<char> doubles;

    while(s1ptr != s1.size()) {
        int cnt = 1;
        while(s1ptr + cnt < s1.size() && s1[s1ptr] == s1[s1ptr+cnt]) {
            cnt++;
        }
        s1ptr += cnt;
        if(s2ptr + cnt < s2.size() && s2[s2ptr + cnt] == s2[s2ptr]) {
            doubles.insert(s2[s2ptr]);
            s2ptr += cnt * 2;
        } else {
            s2ptr += cnt;
        }

    }

    for(char c : doubles) {
        cout << c;
    }
    cout << '\n';
    return 0;
}