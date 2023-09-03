#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    int n; cin >> n;
    while(n-->0) {
        int cnt = 0;
        int num; cin >> num;
        for(int i = 1; i * i <= num; i++) {
            if(num % i == 0) {
                if(i * i != num) {
                    cnt += 2;
                } else {
                    cnt += 1;
                }
            }
        }
        cout << cnt << "\n";
    }
    return 0;
}