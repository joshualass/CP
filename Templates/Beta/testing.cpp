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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<ll> fib(2,1);
    for(int i = 0; i < 50; i++) {
        fib.push_back(fib[fib.size() - 2 ] + fib[fib.size() - 1]);
    }
    cout << "fib : " << fib << '\n';

    for(int i = 0; i < fib.size(); i++) {
        if(fib[i] % 5 == 0) {
            cout << "5 div i : " << i << " fib[i] << " << fib[i] << '\n';
        }
    }

    return 0;
}