#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    while(t-->0) {
        int n, d; cin >> n >> d;
        string num; cin >> num;
        char c = d + '0';
        int index = n;
        for(int i = 0; i < n; i++) {
            if(num[i] < c) {
                index = i;
                break;
            }
        }
        cout << num.substr(0,index) << c << num.substr(index,n-index) << "\n";
    }

    return 0;
}