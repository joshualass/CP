#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int k;
    cin >> k;
    while(k-->0) {
        int n;
        cin >> n;
        int counter = 1;
        int moves = 0;
        for(int i = 0; i < n; i++){
            int num;
            cin >> num;
            if(counter == num) {
                counter ++;
            } else {
                moves++;
            }
        }
        cout << moves << '\n';
    }

    return 0;
}