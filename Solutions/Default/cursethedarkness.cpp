// https://open.kattis.com/problems/cursethedarkness
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

ld epsilon = 1E-10;

void solve() {
    pair<ld,ld> book;
    cin >> book.first;
    cin >> book.second;    

    bool found =false;
    int c; cin >> c;
    for(int i = 0; i < c; i++) {
        ld x, y; cin >> x >> y;
        if(sqrt(abs(book.first - x) * abs(book.first - x) + abs(book.second - y) * abs(book.second - y)) - epsilon < 8) {
            found = true;
        }
    }
    cout << (found ? "light a candle" : "curse the darkness") << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}