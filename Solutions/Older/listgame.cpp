#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    int cnt = 0;
    while(n != 1) {
        bool found = false;
        for(int i = 2; i <= sqrt(n); i++) {
            // cout << "i: " << i << "\n";
            if(n % i == 0) {
                n /= i;
                cnt++;
                found = true;
                break;
            }
        }
        if(!found) {
            cnt++;
            break;
        }
    }   
    cout << cnt << "\n";
    return 0;
}