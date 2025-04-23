#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*

somehow taking 5ever to implement
we see that if we have 2 elements that sum to k, we can easily move any value to one of these 2 indices
use this to sort the array ... 

goal
0 1 2 2 3 3 4 5 7 8

2 5 3 2 7 3 1 8 4 0
    |   |
2 5 8 2 2 3 1 8 4 0
8 5 2 2 2 3 1 8 4 0

5 4 3 2 1 95
ideal
0 1 2 3 4 100

5 4 3 2 1 95
96 4 3 2 1 4
4 96 3 2 1 4
4 99 3 2 1 1
4 1 3 2 99 1
4 1 3 2 96 4
96 1 3 2 4 4
97 1 3 2 4 3
3 1 97 2 4 3
3 1 98 2 4 2
3 1 2 98 4 2
3 1 2 97 4 3
97 1 2 3 4 3
0 1 2 3 4 100


2 5 3 2 7 3 1 8 4 0 
      |       |

0 0 1 2 3 3 4 5 7 10

1 2 3 5 4

1 4 3 5 2



*/

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

void solve() {
    
    int n, k; cin >> n >> k;
    map<int,int> m;
    vector<array<int,2>> a(n);
    array<int,2> b = {-1,-1};
    for(int i = 0; i < n; i++) {
        cin >> a[i][0];
        if(m.count(k - a[i][0])) {
            b = {m[k-a[i][0]], i};
        }
        m[a[i][0]] = i;
        a[i][1] = i;
    }

    // cout << "starting b : " << b << '\n';

    if(b == array<int,2>{-1,-1}) { //unable to do operations
        cout << (is_sorted(a.begin(), a.end()) ? 0 : -1) << '\n';
    } else {
        sort(a.begin(), a.end());
        int p = 1;
        vector<int> c(n); //what og idx should end here
        vector<int> d(n); //index of each og idx
        for(int i = 0; i < n; i++) {
            d[i] = i;
            if(a[i][1] != b[0] && a[i][1] != b[1]) {
                c[p++] = a[i][1];
            }
        }

        // cout << "targ : " << a << '\n';

        sort(a.begin(), a.end(), [](const auto &lhs, const auto &rhs) {
            return lhs[1] < rhs[1];
        });

        // cout << "a : " << a << '\n';
        // cout << "c : " << c << '\n';
        // cout << "d : " << d << '\n';

        vector<array<int,3>> res;

        auto mv = [&](int x, int y, int tx) -> void {
            assert(a[x][0] + a[y][0] == k);
            int ox = a[x][0] - tx;
            // cout << "mv x : " << x << " y : " << y << " tx : " << tx << " ox : " << ox << '\n';
            a[x][0] -= ox;
            a[y][0] += ox;
            res.push_back({x, y, ox});
            // cout << "nx a : " << a << '\n';
        };

        auto movehere = [&](int z) -> void { //moves a[z] to position x, must have that a[x] + a[y] = k;
            // cout << "move here z : " << z << '\n';
            auto [x, y] = b;
            int tx = k - a[z][0];
            mv(x, y, tx);
            mv(x, z, a[z][0]);

            int xi = a[x][1], zi = a[z][1];
            swap(d[xi], d[zi]);
            swap(a[x][1], a[z][1]);
            b[0] = z;
            // cout << "nx a : " << a << '\n';
            // cout << "nx d : " << d << '\n';
            // cout << "nx b : " << b << '\n';
        };

        //anchor b[1] to the back
        if(b[1] != n - 1) {
            movehere(n - 1);
            swap(b[0], b[1]);
        }

        // cout << "init movehere\n";
        // cout << "a : " << a << '\n';
        // cout << "b : " << b << '\n';

        for(int i = 1; i < n - 1; i++) {
            while(b[0]) {
                // cout << "while move\n";
                // cout << "d : " << d << '\n';
                movehere(d[c[b[0]]]);
            }
            if(a[i][1] != c[i]) {
                // cout << "if move\n";
                // cout << "d : " << d << '\n';
                movehere(i);
                movehere(d[c[i]]);
            }
        }

        mv(0, n - 1, 0);

        cout << res.size() << '\n';
        for(auto op : res) {
            // for(int i = 0; i < 3; i++) cout << op[i] + 1 << " \n"[i == 2];
            cout << op[0] + 1 << " " << op[1] + 1 << " " << op[2] << "\n";
        }

        // cout << "a res ? \n";
        // for(int i = 0; i < n; i++) {
        //     cout << a[i][0] << " \n"[i == n - 1];
        // }

    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}