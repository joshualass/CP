#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

//implementation practice 2d prefix sum

ll getArea(ll r1, ll c1, ll r2, ll c2, vector<vector<ll>> &prefixes) { //r1, c2 exclusive, r2, c2 inclusive
    return prefixes[r2][c2] - prefixes[r2][c1] - prefixes[r1][c2] + prefixes[r1][c1];
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<vector<T>> adj) {
    for(auto &x : adj) {
        for(auto &y : x) os << y << " ";
        os << "\n";
    }
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q; cin >> n >> q;

    vector<vector<char>> board(n,vector<char>(n));

    for(auto &r : board) {
        for(auto &c : r) {
            cin >> c;
        } 
    }

    vector<vector<ll>> prefixes(n+1, vector<ll>(n + 1));

    for(int r = 1; r <= n; r++) {
        for(int c = 1; c <= n; c++) {
            prefixes[r][c] = prefixes[r-1][c] + prefixes[r][c-1] - prefixes[r-1][c-1] + (board[r-1][c-1] == 'B');
        }
    }

    for(int i = 0; i < q; i++) {
        ll a, b, c, d; cin >> a >> b >> c >> d;
        ll sum = 0;
        ll nextr1 = (a + n - 1) / n * n;
        ll nextc1 = (b + n - 1) / n * n;
        ll prevr2 = (c + 1) / n * n;
        ll prevc2 = (d + 1) / n * n;
        ll rowsegments = (prevr2 - nextr1) / n;
        ll colsegments = (prevc2 - nextc1) / n;
        sum += getArea((a + n - 1) % n + 1, (b + n - 1) % n + 1, n, n, prefixes); //upperleft corner
        // cout << "sum 1 : " << sum << '\n';
        sum += getArea(0, (b + n - 1) % n + 1, n, n, prefixes) * rowsegments; //leftside
        // cout << "sum 2 : " << sum << '\n';
        sum += getArea(0, (b + n - 1) % n + 1, (c + 1) % n, n, prefixes); //bottomleft corner
        // cout << "sum 3 : " << sum << '\n';
        sum += getArea((a + n - 1) % n + 1, 0, n, n, prefixes) * colsegments; //topside
        // cout << "sum 4 : " << sum << '\n';
        sum += getArea(0,0,n,n,prefixes) * rowsegments * colsegments; //center
        // cout << "sum 5 : " << sum << '\n';
        sum += getArea(0, 0, (c + 1)  % n, n, prefixes) * colsegments; //bottom side
        // cout << "sum 6 : " << sum << '\n';
        sum += getArea((a + n - 1) % n + 1, 0, n, (d + 1) % n, prefixes); //topright corner
        // cout << "sum 7 : " << sum << '\n';
        sum += getArea(0,0,n,(d + 1) %n, prefixes) * rowsegments; //rightside
        // cout << "sum 8 : " << sum << '\n';
        sum += getArea(0,0, (c + 1)  % n, (d + 1) % n, prefixes);
        // cout << "sum 9 : " << sum << '\n';
        cout << sum << '\n';
    }


    return 0;
}