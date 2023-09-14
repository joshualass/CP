#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int num;
    cin >> num;
    int out = 0;
    while(num != 0) {
        out *= 2;
        if(num % 2 == 1) {
            out++;
        }
        num /= 2;
    }
    cout << out;
    return 0;
}