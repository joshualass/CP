#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int SIZE = 2e5 + 1;
ll arr[SIZE];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q; cin >> n >> q;
    for(int i = 1; i <= n; i++) {
        ll num; cin >> num;
        arr[i] = arr[i-1] + num;
    }
    for(int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        cout << arr[r] - arr[l-1] << '\n';
    }


    return 0;
}