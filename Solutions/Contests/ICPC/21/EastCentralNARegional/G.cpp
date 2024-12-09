#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

bool eval(string a, string b, string c, string op){
    ll cval = stoll(c);
    ll aval = stoll(a);
    ll bval = stoll(b);
    return ((op == "+")? aval + bval : aval * bval) == cval;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string op, tmp;
    string a, b, c;
    cin >> a >> op >> b >> tmp >> c;
    for(int i = 1; i <= a.size(); i++){
        for(int j = 1; j <= b.size(); j++){
            string na = b.substr(0, j) + a.substr(i);
            string nb = a.substr(0, i) + b.substr(j);
            if(eval(na, nb, c, op)) {
                cout << na << " " << op << " " << nb << " = " << c << "\n";
                return 0;
            }
        }
    }
    for(int i = 1; i <= a.size(); i++){
        for(int j = 1; j <= c.size(); j++){
            string na = c.substr(0, j) + a.substr(i);
            string nc = a.substr(0, i) + c.substr(j);
            if(eval(na, b, nc, op)) {
                cout << na << " " << op << " " << b << " = " << nc << "\n";
                return 0;
            }
        }
    }
    for(int i = 1; i <= b.size(); i++){
        for(int j = 1; j <= c.size(); j++){
            string nb = c.substr(0, j) + b.substr(i);
            string nc = b.substr(0, i) + c.substr(j);
            if(eval(a, nb, nc, op)) {
                cout << a << " " << op << " " << nb << " = " << nc << "\n";
                return 0;
            }
        }
    }

    return 0;
}