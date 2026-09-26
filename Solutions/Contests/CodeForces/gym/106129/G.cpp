#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;

    auto get = [&](int x) -> string {
        string res = "";
        for(int i = 0; i < 6; i++) {
            char c;
            if(i == 0) {
                c = '0';
            } else if(i == 1) {
                c = 'A';
            } else if(i == 2) {
                c = 'a';
            } else {
                c = '!';
            }
            int add = x % 10;
            c += add;
            x /= 10;
            res.push_back(c);
            res.push_back(c);
        }
        return res;
    };

    for(int i = 0; i < n; i++) cout << get(i) << '\n';

    return 0;
}
