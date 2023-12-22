#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, x; cin >> n >> x;
    int sum = 0;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        if(num <= x) sum += num;
    }   
    cout << sum << '\n';
    return 0;
}