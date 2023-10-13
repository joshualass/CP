//https://open.kattis.com/problems/zigzag
//Mark's goofy ACPC problem
#include <bits/stdc++.h>
typedef long long ll;
typedef __int128_t lll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    int size = (n + 24) / 25;
    int extra = size * 25 - n;
    string str = "";
    for(int i = 0; i < size; i++) {
        if(i & 1) {
            str.push_back('z');
        } else {
            str.push_back('a');
        }
    }
    if(size & 1) {
        str.push_back('z' - extra);
        while(str.size() != 2 && str.back() + 2 <= 'z') {
            str[str.size()-1] = str[str.size()-1] + 2;
            str[1] = str[1] - 1;
        }
    } else {
        str.push_back('a' + extra);
        while(str.back() - 2 >= 'a') {
            str[str.size()-1] = str[str.size()-1] - 2;
            str[1] = str[1] - 1;
        }
    }

    cout << str << "\n";

    return 0;
}   