#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string line;
    getline(cin,line);

    string ans = "";

    for(int i = 1; i < line.length(); i++) {
        if(line[i-1] != line[i]) {
            ans += line[i];
        }
    }
    cout << line[0] << ans;
    return 0;
}