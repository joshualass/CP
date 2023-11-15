#include <bits/stdc++.h>
typedef long long ll;
typedef __int128_t lll;
typedef long double ld;
using namespace std;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q; cin >> q;

    while(q-->0) {
        ll read; cin >> read;
        lll num = read;
        num--;
        lll length = 1;
        lll cnt = 9;
        while(num >= length * cnt) {
            num -= length * cnt;
            length++;
            cnt *= 10;
        }
        lll add = num / length;
        lll start = cnt / 9;
        lll ansnum = start + add;
        lll leftdigit = length - num % length;
        for(int i = 1; i < leftdigit; i++) {
            ansnum /= 10;
        }
        cout << (int) (ansnum % 10) << '\n';
    }
 
    return 0;
}
