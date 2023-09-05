#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll sum = 0;
    int n; cin >> n;
    while (--n>=0) {
        char x; cin >> x;
        if(x == 'O') {
            sum += pow((ll) 2, n);
        }
    }
    cout << sum;
    return 0;
}