#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n, k; cin >> n >> k;
    string str; cin >> str;
    if(k % 2 == 0) {
        sort(str.begin(), str.end());
        cout << str << "\n";
    } else {
        string str1 = "";
        string str2 = "";
        for(int i = 0; i < n; i++) {
            if(i % 2 == 0) {
                str1.push_back(str[i]);
            } else {
                str2.push_back(str[i]);
            }
        }
        sort(str1.begin(), str1.end());
        sort(str2.begin(), str2.end());
        for(int i = 0; i < n; i++) {
            if(i % 2 == 0) {
                cout << str1[i/2];
            } else {
                cout << str2[i/2];
            }
        }
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int casi; cin >> casi;
    while(casi-->0) solve();
    return 0;
}