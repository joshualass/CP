#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
 
void recur(int from, int to, int size) {
    if (size == 1) {
        cout << (from == 4 ? 3 : from) << " " << (to == 4 ? 3 : to) << '\n';
    } else {
        recur(from, (7 ^ (from | to)), size - 1);
        cout << (from == 4 ? 3 : from) << " " << (to == 4 ? 3 : to) << '\n';
        recur((7 ^ (from | to)), to, size - 1);
    }
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    int n; cin >> n;
    cout << (1 << n) - 1 << '\n';
    recur(1, 4, n);
    return 0;
}
