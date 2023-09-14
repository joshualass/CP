#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<int> v(1000001,-1);

    v[0] = 0;
    int n, x;
    cin >> n >> x;
    vector<int> coins(n);
    for(int i = 0; i < n; i++) {
        cin >> coins[i];
    }
    sort(coins.begin(),coins.end());

    for(int i = 0; i < v.size(); i++) {
        for(int c = 0; c < coins.size(); c++) {
            if(i-coins[c] >= 0 && v[i-coins[c]] != -1) {
                if(v[i] == -1) {
                    v[i] = v[i-coins[c]] + 1;
                }
                v[i] = min(v[i],v[i-coins[c]] + 1);
            }
        }
    }
    for(int i = 0; i < x+1; i++) {
//        cout << v[i] << " ";
    }
    cout << v[x];

    return 0;
}