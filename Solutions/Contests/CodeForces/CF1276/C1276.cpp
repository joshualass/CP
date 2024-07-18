#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    map<int,int> cnts;

    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        cnts[num]++;
    }
    vector<array<int,2>> a; //cnt, value
    for(auto [u, v] : cnts) {
        a.push_back({v,u});
    }
    sort(a.begin(), a.end());

    // cout << "a : " << a << '\n';

    int p = 0;
    int pc = 0;
    array<int,2> res = {0,0};
    for(int i = 1; i <= a.size(); i++) {
        while(p != a.size() && a[p][0] < i) {
            pc += a[p][0];
            p++;
        }
        int maxnums = pc + (a.size() - p) * i;
        
        int l = maxnums / i;
        // cout << "i : " << i << " pc : " << pc << " p : " << p << " n : " << n << " maxnums : " << maxnums << " l : " << l << '\n';
        if(l < i) break;
        if(i * l > res[0] * res[1]) {
            res = {i, l};
        }
    }

    // cout << "Res : " << res << '\n';

    for(auto &x : a) {
        x[0] = min(x[0], res[0]);
    }
    p = a.size() - 1;
    vector<vector<int>> mat(res[0], vector<int>(res[1]));
    for(int i = 0; i < res[0] * res[1]; i++) {
        int row = i % res[0];
        int col = (row + i / res[0]) % res[1];
        if(a[p][0] == 0) {
            p--;
        }
        a[p][0]--;
        mat[row][col] = a[p][1];
    }

    cout << res[0] * res[1] << '\n';
    cout << res[0] << " " << res[1] << '\n';

    for(int i = 0; i < res[0]; i++) {
        for(int j = 0; j < res[1]; j++) {
            cout << mat[i][j] << " \n"[j == res[1] - 1];
        }
    }

    return 0;
}