#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<bool> v(n);
    for(int i = 0; i < n; i++) {
        char c; cin >> c;
        if(c == 'T') {
            v[i] = 1;
        }
    }
    stack<bool> s;
    char c; cin >> c;
    while(!cin.eof()) {
        if(c == '0') break;
        switch(c) {
            case '*' : 
                {
                    bool b1 = s.top();
                    s.pop();
                    bool b2 = s.top();
                    s.pop();
                    s.push(b1 && b2);
                    break;
                }
            case '+':
                {                
                    bool b1 = s.top();
                    s.pop();
                    bool b2 = s.top();
                    s.pop();
                    s.push(b1 || b2);
                    break;
                }
            case '-':
                { 
                    bool b1 = s.top();
                    s.pop();
                    s.push(!b1);
                    break;
                }
            default:
                if(c < 'A' || c > 'Z') break;
                s.push(v[c - 'A']);
        }
        cin >> c;
    }

    cout << (s.top() ? "T\n" : "F\n");

    return 0;
}