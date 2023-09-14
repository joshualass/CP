#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    vector<string> v(3);
    for(auto &x: v) cin >> x;
    for(int i = 0; i < 3; i++) {
        char test = v[i][0];
        for(int c = 1; c < 3; c++) {
            if(v[i][c] != test) {
                test = '!';
                break;
            }
        }
        if(test != '!' && test != '.') {
            cout << test << "\n";
            return;
        }
    }
    for(int i = 0; i < 3; i++) {
        char test = v[0][i];
        for(int c = 1; c < 3; c++) {
            if(v[c][i] != test) {
                test = '!';
                break;
            }
        }
        if(test != '!' && test != '.') {
            cout << test << "\n";
            return;
        }
    }
    char test = v[0][0];
    for(int i = 1; i < 3; i++) {
        if(v[i][i] != test) {
            test = '!';
            break;
        }
    }
    if(test != '!' && test != '.') {
        cout << test << "\n";
        return;
    }    

    test = v[2][0];
    for(int i = 1; i < 3; i++) {
        if(v[2-i][i] != test) {
                        test = '!';
            break;
        }
    }
    if(test != '!' && test != '.') {
        cout << test << "\n";
        return;
    }   
    cout << "DRAW\n";
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int casi; cin >> casi;
    while(casi-->0) solve();
    return 0;
}