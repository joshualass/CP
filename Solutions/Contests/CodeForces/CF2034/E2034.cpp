#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    int n, k; cin >> n >> k;
    ll nfac = 1;
    for(int i = 1; i <= n; i++) {
        nfac *= i;
        nfac = min(nfac,1000000000LL);
    }

    if(n == 1) { //case n = 1
        if(k == 1) {
            cout << "Yes\n1\n";
        } else {
            cout << "No\n";
        }
    } else if(k % 2 == 0) { //case k even 
        if(k <= nfac) {
            cout << "Yes\n";
            vector<int> perm(n);
            iota(perm.begin(), perm.end(), 1);
            for(int i = 0; i * 2 < k; i++) {
                for(int j = 0; j < n; j++) {
                    cout << perm[j] << " \n"[j == n - 1];
                }
                for(int j = 0; j < n; j++) {
                    cout << n + 1 - perm[i] << " \n"[j == n - 1];
                }
                next_permutation(perm.begin(), perm.end());
            }
        } else {
            cout << "No\n";
        }
    } else { //case k odd
        if(n % 2 == 1 && k >= 2 && k <= nfac - 2) {
            cout << "Yes\n";
            vector<int> a(n), b(n), c(n);
            iota(a.begin(), a.end(), 1);
            for(int i = 0; i < n; i++) {
                if(i <= n / 2) {
                    b[i] = n / 2 + i + 1;
                    c[i] = n - i * 2;
                } else {
                    b[i] = i - n / 2;
                    c[i] = n + 1 - (i - n / 2) * 2;
                }
            }
            cout << a << "\n" << b << '\n' << c << '\n';
            int needed = k - 3;
            vector<int> d = a;
            while(needed) {
                vector<int> e(n);
                for(int i = 0; i < n; i++) {
                    e[i] = n + 1 - d[i];
                }
                if(d != a && d != b && d != c && e != a && e != b && e != c) {
                    needed -= 2;
                    cout << d << '\n';
                    cout << e << '\n';
                }

                next_permutation(d.begin(),d.end());
            }


        } else {
            cout << "No\n";
        }
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}