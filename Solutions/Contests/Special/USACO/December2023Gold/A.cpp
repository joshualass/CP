#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<vector<T>> adj) {
    for(auto &x : adj) {
        for(auto &y : x) os << y << " ";
        os << "\n";
    }
    return os;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;

    vector paritys(n, vector<int>(n));

    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            char c; cin >> c;
            if(c == '1') {
                paritys[i][j] = 1;
            }
        }
    }
    int ans = 0;
    vector flights(n, vector<int>(n));

    for(int dist = 1;  dist < n; dist++) {
        for(int start = 0; start + dist < n; start++) {
            int parity = 0;
            int dest = start + dist;
            //iterate over all parity's with a smaller distance
            for(int inter = start + 1; inter < dest; inter++) {
                if(flights[start][inter]) {
                    parity ^= paritys[inter][dest];
                }
            }
            if(parity != paritys[start][dest]) {
                ans++;
                flights[start][dest] = 1;
            }
        }
    }

    // cout << "flights\n" << flights;

    cout << ans << '\n';
    return 0;
}