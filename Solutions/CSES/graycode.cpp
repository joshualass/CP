#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void flip(string &s, int i) {
    if(s[i] == '0') {
        s[i] = '1';
    } else {
        s[i] = '0';
    }
}

void recur(string &s, int i) {
    if(i == 0) {
        flip(s,i);
        cout << s << '\n';
    } else {
        recur(s, i - 1);
        flip(s,i);
        cout << s << '\n';
        recur(s, i - 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    string line = "";
    for(int i = 0; i < n; i++) {
        line += '0';
    }
    cout << line << '\n';
    recur(line, n - 1);
    

    return 0;
}
