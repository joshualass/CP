#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<vector<char>> v(n,vector<char>(n));
    for(int r = 0; r < n; r++) {
        string word; cin >> word;
        for(int c = 0; c < n; c++) {
            if(word[c] == '?') {
                cout << ((r + c) % 2 == 0 ? "\\" : "/");
            } else {
                cout << word[c];
            }
        }
        cout << "\n";
    }


    return 0;
}