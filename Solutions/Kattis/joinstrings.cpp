#include <bits/stdc++.h>
#define I int
using namespace std;
I i = 0, l = 1, n;
const I N = 1e6;
vector<I> v[N];
string d[N];
void f(I y) {
    cout << d[y];
    for (I x : v[y]) f(x);
}
I main() {
    cin >> n;
    for (; ++i <= n;) cin >> d[i];
    for (; --i > 1;) {
        cin >> l >> n;
        v[l].push_back(n);
    }
    f(l);
}