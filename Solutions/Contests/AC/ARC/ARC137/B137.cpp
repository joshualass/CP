#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

int solve(vector<int> &v) {

    int sum = 0;
    int n = v.size();
    for(int i = 0; i < n; i++) {
        sum += v[i];
    }

    int curr = 0;
    int most = 0;
    
    for(int i = 0; i < n; i++) {
        if(v[i] == 0) {
            curr++;
        } else {
            curr--;
        }
        curr = max(curr,0);
        most = max(curr, most);
    }
    // cout << "v\n";
    // cout << v << '\n';
    // cout << "most: " << most << " sum: " << sum << '\n';
    return most + sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<int> v(n);
    for(auto &x: v) cin >> x;

    int most_ones = solve(v);
    
    for(int i = 0; i < n; i++) {
        v[i] ^= 1;
    }
    int least_ones = n - solve(v) ;
    // cout << "mostones: " << most_ones << " least_ones: " << least_ones << '\n';
    cout << most_ones - least_ones + 1 << "\n";

    return 0;
}