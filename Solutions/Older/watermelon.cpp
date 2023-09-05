#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int w; cin >> w;
    cout << (w % 2 == 0 && w >= 4 ? "YES" : "NO");

    return 0;
}