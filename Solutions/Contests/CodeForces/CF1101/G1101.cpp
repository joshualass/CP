#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

//conditions to end a segment - currently not in the basis, xor of remaining numbers does not equal current segment
//insert if not currently in basis
bool insertToBasis(vector<int> &basis, int x) {
    // cout << "try inserting : " << x << '\n';
    for(int bit = basis.size() - 1; bit >= 0; bit--) {
        if(x & (1 << bit)) {
            if(basis[bit]) {
                x ^= basis[bit];
            } else {
                basis[bit] = x;
                // cout << "ok\n";
                return 1;
            }
        }
    }
    // cout << "notok\n";
    return 0;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<int> a(n);
    int globalxor = 0;
    for(int &x : a) {
        cin >> x;
        globalxor ^= x;
    }

    if(globalxor == 0) {
        cout << "-1\n";
        return 0;
    }

    vector<int> ends;
    int currxor = 0;
    vector<int> basis(30);
    for(int i = 0; i < n; i++) {
        currxor ^= a[i];
        globalxor ^= a[i];
        // cout << "i : " << i << " curr : " << currxor << " global : " << globalxor << '\n';
        if((currxor != globalxor && globalxor || i == n - 1) && insertToBasis(basis, currxor)) {
            ends.push_back(i);
            currxor = 0;
        }
    }

    // cout << "ends ? " << ends << '\n';
    cout << ends.size() << '\n';

    return 0;
}