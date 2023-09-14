#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    string cf = "codeforces";
    while(t-->0) {
        string s; cin >> s;
        cout << (cf.find(s) == string::npos ? "NO" : "YES") << '\n';
    }

    return 0;
}