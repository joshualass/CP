#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << "/";
        }
    }
    return os;
}

array<ll,2> add(array<ll,2> a, array<ll,2> b) {
    array<ll,2> res = {a[0] * b[1] + a[1] * b[0], a[1] * b[1]};
    ll g = gcd(res[0], res[1]);
    res[0] /= g;
    res[1] /= g;
    return res;
}

array<ll,2> sub(array<ll,2> a, array<ll,2> b) {
    array<ll,2> res = {a[0] * b[1] - a[1] * b[0], a[1] * b[1]};
    ll g = gcd(res[0], res[1]);
    res[0] /= g;
    res[1] /= g;
    return res;
}

array<ll,2> mul(array<ll,2> a, array<ll,2> b) {
    array<ll,2> res = {a[0] * b[0], a[1] * b[1]};
    ll g = gcd(res[0], res[1]);
    res[0] /= g;
    res[1] /= g;
    return res; 
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;

    int make_odd = 0;
    while(n % 2 == 0) {
        n /= 2;
        make_odd++;
    }

    int flips = ceil(log2(n));
    int a = 1 << flips;



    array<ll,2> lhs = {1,1};
    array<ll,2> rhs = mul(array<ll,2>{flips,1}, array<ll,2>{n, a});

    // cout << "flips : " << flips << " a : " << a << '\n';
    // cout << "lhs : " << lhs << " rhs : " << rhs << '\n';

    int left = a - n;

    // cout << "left : " << left << '\n';

    for(int i = 0; i < flips; i++) {
        if((left >> (flips - 1 - i)) & 1) {
            array<ll,2> f = {1, 1 << (i + 1)};
            int fc = i + 1;
            lhs = sub(lhs, f);
            rhs = add(rhs, mul(f, array<ll,2>{fc, 1}));
        }
    }

    array<ll,2> res = mul(rhs, array<ll,2>{lhs[1], lhs[0]});
    res = add(res, array<ll,2>{make_odd, 1});
    cout << res[0] << "/" << res[1] << '\n';

    return 0;
}