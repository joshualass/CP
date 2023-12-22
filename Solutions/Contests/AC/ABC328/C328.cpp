#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q; cin >> n >> q;

    string str; cin >> str;

    vector<int> prefix(n + 1);

    for(int i = 0; i < n - 1; i++) {
        if(str[i] == str[i+1]) {
            prefix[i+1]++;
        }
        prefix[i+1] += prefix[i];
    }

    for(int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        cout << max(0, prefix[r - 1] - prefix[l - 1]) << '\n';
    }

    return 0;
}