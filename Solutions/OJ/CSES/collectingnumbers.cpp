#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<bool> v(n+1);

    int cnt = 0;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        if(!v[num-1]) {
            cnt++;
        }
        v[num] = true;
    }
    cout << cnt << "\n";

    return 0;
}
