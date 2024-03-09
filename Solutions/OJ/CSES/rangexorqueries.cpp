#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q; cin >> n >> q;
    vector<int> Xor(n+1);
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        Xor[i+1] = Xor[i] ^ x;
    }
    for(int i = 0; i < q; i++) {
        int a, b; cin >> a >> b;
        cout << (Xor[b] ^ Xor[a-1]) << "\n";
    }

    return 0;
}