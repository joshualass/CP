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

    int n; cin >> n;

    string vowels = "aeiou";
    string consonants = "qwrtypsdfghjklzxcvbnm";

    for(int i = 0; i < n; i++) {
        vector<int> res(20);
        int it = i;
        for(int j = 0; j < 10; j+= 2) {
            res[j] += it % 21;
            it /= 21;
        }
        // cout << res << '\n';
        for(int j = 0; j < 20; j++) {
            if(j & 1) {
                cout << vowels[res[j]];
            } else {
                cout << consonants[res[j]];
            }
        }
        cout << '\n';
    }


    return 0;
}