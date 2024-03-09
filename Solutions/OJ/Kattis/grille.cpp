#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void rotate(vector<vector<char>> &v) {
    vector<vector<char>> rotated(v.size(),vector<char>(v.size()));
    for(int i = 0; i < v.size(); i++) {
        for(int j = 0; j < v.size(); j++) {
            rotated[j][v.size() - i - 1] = v[i][j];
        }
    }
    v = rotated;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x;
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<vector<char>> v(n,vector<char>(n));
    for(auto &x : v) for(auto &y : x) cin >> y;
    string s; cin >> s;
    int idx = 0;
    vector<char> ans(n * n, '\0');
    for(int i = 0; i < 4; i++) {
        for(int r = 0; r < n; r++) {
            for(int c = 0; c < n; c++) {
                if(v[r][c] == '.') {
                    ans[n * r + c] = s[idx++];
                }
            }
        }
        rotate(v);
    }
    if(count(ans.begin(), ans.end(), '\0')) {
        cout << "invalid grille\n";
    } else {
        cout << ans << '\n';
    }


    return 0;
}