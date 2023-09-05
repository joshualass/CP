#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    while(t-->0) {
        int n; cin >> n;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < i+1; j++) {
                if(j == 0) {
                    cout << "1";
                } else if(j == i) {
                    cout << " 1";
                } else {
                    cout << " 0";
                }
            }
            cout << '\n';
        }
    }

    return 0;
}