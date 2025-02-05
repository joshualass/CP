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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<vector<string>> as(n,vector<string>(m));
    vector<int> cl(n);
    vector<int> id(n);

    for(int i = 0; i < n; i++) {
        cin >> id[i];
        for(int j = 0; j < m; j++) {
            cin >> as[i][j];
        }
        cin >> cl[i];
    }

    for(int i = 0; i < m; i++) {
        map<string,array<int,2>> p;
        array<int,2> c{};
        for(int j = 0; j < n; j++) {
            string attr = as[j][i];
            int cc = cl[j];
            c[cc]++;
            p[attr][cc]++;
        }
        double s = 0;
        auto calc_entropy = [](array<int,2> a) -> double {
            double p0 = ((double) a[0]) / (a[0] + a[1]);
            double p1 = ((double) a[1]) / (a[0] + a[1]);
            return -(p0*(p0?log2(p0):0)+p1*(p1?log2(p1):0));
        };

        cout << "column i : " << i << '\n';

        for(auto [attr, cnts] : p) {
            cout << "attr : " << attr << " cnts : " << cnts << " entropy : " << calc_entropy(cnts) << '\n';
            s += ((double) cnts[0] + cnts[1]) / n * calc_entropy(cnts);
        }

        cout << fixed << setprecision(5);

        // cout << "c : " << c << '\n';

        cout << "Entropy(S) : " << calc_entropy(c) << " sum : " << s << '\n';
        cout << "Gain(S,A)= " << calc_entropy(c) - s << '\n';

        cout << "\n\n";
    }

    return 0;
}