#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, a, b; cin >> n >> a >> b;
    if(a == 1 && b == 1 || a + b > n + 1) {
        cout << "no\n";
        return 0;
    }

    int rev = 0;

    if(b == 1) {
        rev = 1;
        swap(a, b);
    }

    int p = 1;
    vector<int> res;
    while(p < a) {
        res.push_back(p++);
    }

    res.push_back(n);
    int z = n - 1;
    while(b - 2 > 0) {
        res.push_back(z--);
        b--;
    }
    while(p < z) {
        res.push_back(p++);
    }
    res.push_back(z);

    if(rev) reverse(res.begin(), res.end());

    cout << "yes\n";
    cout << res << '\n';

    return 0;
}
