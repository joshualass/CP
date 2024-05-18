#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<int> v(n);
    set<int> guessed;
    vector<int> idxs(n);

    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        num--;
        if(i == 0) {
            v[i] = 1;
        } else {
            int lo = -1, hi = -1;
            if(guessed.lower_bound(num) != guessed.end()) {
                lo = idxs[*guessed.lower_bound(num)];
            }
            if(guessed.lower_bound(num) != guessed.begin()) {
                hi = idxs[*--guessed.lower_bound(num)];
            }
            v[i] = v[max(lo,hi)] + 1;
        }
        guessed.insert(num);
        idxs[num] = i;
    }
    // cout << v << '\n';
    cout << *max_element(v.begin(), v.end()) << '\n';
    return 0;
}