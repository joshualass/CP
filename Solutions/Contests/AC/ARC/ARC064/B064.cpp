#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s; cin >> s;
    if(s.front() == s.back()) {
        if(s.size() % 2 == 0) {
            cout << "First\n";
        } else {
            cout << "Second\n";
        }
    }

    if(s.front() != s.back()) {
        if(s.size() % 2 == 1) {
            cout << "First\n";
        } else {
            cout << "Second\n";
        }
    }

    return 0;
}