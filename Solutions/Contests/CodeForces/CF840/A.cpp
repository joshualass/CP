#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    cin >> T;
    while(T-->0) {
        int N;
        cin >> N;
        int min = 2047;
        int max = 0;
        for(int i = 0; i < N; i++) {
            int num;
            cin >> num;
            min = min & num;
            max = max | num;
        }
        cout << max - min << "\n";
    }
    
    
    return 0;
}