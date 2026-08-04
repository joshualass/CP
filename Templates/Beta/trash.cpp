#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void test(int *x) {
    x = new int(7);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int *x = new int(5);
    cout << *x << endl;
    test(x);
    cout << *x << endl;

    return 0;
}
