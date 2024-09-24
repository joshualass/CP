#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

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

template <typename T>
void printS(stack<T> x) {
    cout << "stack: ";
    while(x.size()) {
        cout << x.top() << ' ';
        x.pop();
    }
    cout << "\n";
}

void solve() {
    int n; cin >> n;
    stack<array<ll,2>> s;

    for(int i = 0; i < n; i++) {
        ll cura; cin >> cura;
        ll extra = 0;
        ll size = 1;

        while(s.size() && cura < s.top()[0]) {

            array<ll,2> p = s.top();
            s.pop();
            ll totalsum = extra + cura * size + p[0] * p[1];
            size += p[1];
            // cout << "totalsum : " << totalsum << " size : " << size << '\n';
            ll newa = totalsum / size;
            extra = totalsum - newa * size;
            cura = newa;

        }

        // cout << "extra : " << extra << '\n';

        if(extra) {
            s.push({cura, size - extra});
            s.push({cura + 1, extra});
        } else {
            s.push({cura, size});
        }

        // cout << "after i : " << i << " stack : ";
        // printS(s);

    }

    ll hi = s.top()[0];
    ll lo = LLONG_MAX;
    while(s.size()) {
        lo = min(lo,s.top()[0]);
        // cout << "reverse stack : " << s.top() << '\n';
        s.pop();
    }

    cout << hi - lo << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}