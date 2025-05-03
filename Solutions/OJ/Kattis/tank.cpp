#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

// L geo
ld eps = 1e-8;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, d, L; cin >> n >> d >> L;

    auto get_area = [&](vector<array<ld,2>> a) -> ld {
        a.push_back(a.front());
        ld res = 0;
        for(int i = 1; i < a.size(); i++) {
            res += a[i-1][0] * a[i][1] - a[i][0] * a[i-1][1];
        }
        res /= 2;
        cout << "res : " << res << '\n';
        return abs(res);
    };

    vector<array<ld,2>> a(n);
    for(auto &x : a) for(auto &y : x) cin >> y;

    ld l = 0, r = 0;
    for(int i = 0; i < n; i++) r = max(r, a[i][1]);

    if(get_area(a) / d - eps > L) {
        cout << "no bs" << endl;
        l = r;
    }

    while(a[0][1] == 0) {
        a.push_back(a.front());
        a.erase(a.begin());
    }

    cout << "a : " << a << endl;

    int z = -1;
    for(int i = 0; i < n; i++) if(a[i][1] == 0) z = i;

    vector<array<ld,2>> lhs, rhs;

    cout << "make it here 0" << endl;

    for(int j = z; ; j++) {
        lhs.push_back(a[j % n]);
        if(a[j%n][1] == r) break;
    }

    for(int j = z - 1 + n; ; j--) {
        rhs.push_back(a[j % n]);
        if(a[j % n][1] == r) break;
    }

    cout << "make it here" << endl;

    while(r - l > eps) {
        ld m = (l + r) / 2;

        r = m;

    }

    cout << fixed << setprecision(2) << l << '\n';

    return 0;
}
